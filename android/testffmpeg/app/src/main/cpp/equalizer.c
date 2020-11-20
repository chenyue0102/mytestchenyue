#include "equalizer.h"
#include <assert.h>
#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include "my_envelope.h"
#include "real_fft.h"

inline void* mymalloc(size_t size) {
	void *data = malloc(size);
	if (NULL != data) {
		memset(data, 0, size);
	}
	return data;
}

// Low frequency of the FFT.  20Hz is the
 // low range of human hearing
#define loFreqI 20
#define NUM_PTS 180
// dB - linear amplitude conversions
#define DB_TO_LINEAR(x) (pow(10.0, (x) / 20.0))

typedef struct _equalizer_t {
	size_t mWindowSize;
	double mLoFreq;
	double mHiFreq;
	float *mFilterFuncR, *mFilterFuncI, *mFFTBuffer;
	double mWhens[NUM_PTS];//0~1之间，分割成180分，每份step位置
	double *mWhenSliders;//eq均衡频率，log10形式，长度为NUMBER_OF_BANDS+1
	double *mEQVals;//eq均衡器db值，-20~20，长度为NUMBER_OF_BANDS+1
	size_t NUMBER_OF_BANDS;
	struct _my_envelope_t *mLogEnvelope;
	size_t mM;
	FFTParam *hFFT;
}equalizer_t;

equalizer_t* create_equalizer(double sample_rate, size_t window_size, double *hz, size_t count) {
	assert((window_size & (window_size - 1)) == 0);
	equalizer_t *p = mymalloc(sizeof(equalizer_t));
	p->mWindowSize = window_size;
	p->mHiFreq = sample_rate / 2.;
	p->mLoFreq = loFreqI;
	p->NUMBER_OF_BANDS = count;
	p->mLogEnvelope = my_envelope_alloc(-120.0, 60.0, 0.0);
	p->mM = window_size / 2 - 1;
	p->hFFT = fftparam_alloc(window_size);

	for (int i = 0; i < NUM_PTS - 1; i++) {
		p->mWhens[i] = (double)i / (NUM_PTS - 1);
	}
	p->mWhens[NUM_PTS - 1] = 1.;

	p->mWhenSliders = mymalloc(sizeof(double) * (p->NUMBER_OF_BANDS + 1));
	p->mEQVals = mymalloc(sizeof(double) * (p->NUMBER_OF_BANDS + 1));

	{
		double loLog = log10(p->mLoFreq);
		double hiLog = log10(p->mHiFreq);
		double denom = hiLog - loLog;

		for (size_t i = 0; i < count; i++) {
			if (hz[i] < p->mLoFreq) {
				p->mWhenSliders[i] = 0.;
			}
			else {
				p->mWhenSliders[i] = (log10(hz[i]) - loLog) / denom;
			}
		}
	}


	p->mFilterFuncR = mymalloc(window_size * sizeof(float));
	p->mFilterFuncI = mymalloc(window_size * sizeof(float));
	p->mFFTBuffer = mymalloc(window_size * sizeof(float));

	return p;
}

static void GraphicEQ(struct _equalizer_t* p, struct _my_envelope_t *env) {
	double *mWhenSliders = p->mWhenSliders;
	double *mWhens = p->mWhens;
	double *mEQVals = p->mEQVals;
	size_t mBandsInUse = p->NUMBER_OF_BANDS;

	double value = 0.0;
	double dist, span, s;

	my_envelope_flatten(env, 0.);
	my_envelope_set_track_len(env, 1.0, 0.0);

	int minF = 0;
	for (size_t i = 0; i < NUM_PTS; i++)
	{
		while ((mWhenSliders[minF] <= mWhens[i]) & (minF < (int)mBandsInUse))
			minF++;
		minF--;
		if (minF < 0) //before first slider
		{
			dist = mWhens[i] - mWhenSliders[0];
			span = mWhenSliders[1] - mWhenSliders[0];
			s = dist / span;
			if (s < -1.5)
				value = 0.;
			else if (s < -.5)
				value = mEQVals[0] * (s + 1.5)*(s + 1.5) / 2.;
			else
				value = mEQVals[0] * (.75 - s * s) + mEQVals[1] * (s + .5)*(s + .5) / 2.;
		}
		else
		{
			if (mWhens[i] > mWhenSliders[mBandsInUse - 1])   //after last fader
			{
				dist = mWhens[i] - mWhenSliders[mBandsInUse - 1];
				span = mWhenSliders[mBandsInUse - 1] - mWhenSliders[mBandsInUse - 2];
				s = dist / span;
				if (s > 1.5)
					value = 0.;
				else if (s > .5)
					value = mEQVals[mBandsInUse - 1] * (s - 1.5)*(s - 1.5) / 2.;
				else
					value = mEQVals[mBandsInUse - 1] * (.75 - s * s) +
					mEQVals[mBandsInUse - 2] * (s - .5)*(s - .5) / 2.;
			}
			else  //normal case
			{
				dist = mWhens[i] - mWhenSliders[minF];
				span = mWhenSliders[minF + 1] - mWhenSliders[minF];
				s = dist / span;
				if (s < .5)
				{
					value = mEQVals[minF] * (0.75 - s * s);
					if (minF + 1 < (int)mBandsInUse)
						value += mEQVals[minF + 1] * (s + .5)*(s + .5) / 2.;
					if (minF - 1 >= 0)
						value += mEQVals[minF - 1] * (s - .5)*(s - .5) / 2.;
				}
				else
				{
					value = mEQVals[minF] * (s - 1.5)*(s - 1.5) / 2.;
					if (minF + 1 < (int)mBandsInUse)
						value += mEQVals[minF + 1] * (.75 - (1. - s)*(1. - s));
					if (minF + 2 < (int)mBandsInUse)
						value += mEQVals[minF + 2] * (s - .5)*(s - .5) / 2.;
				}
			}
		}
		if (mWhens[i] <= 0.)
			my_envelope_reassign(p->mLogEnvelope, 0., value);
		my_envelope_insert(p->mLogEnvelope, mWhens[i], value);
	}
	my_envelope_reassign(p->mLogEnvelope, 1., value);
}

void CalcFilter(struct _equalizer_t* p){
	const double mLoFreq = p->mLoFreq;
	const double mHiFreq = p->mHiFreq;
	const size_t mWindowSize = p->mWindowSize;
	float *const mFilterFuncR = p->mFilterFuncR;
	float *const mFilterFuncI = p->mFilterFuncI;
	const size_t mM = p->mM;
	FFTParam *hFFT = p->hFFT;


	double loLog = log10(mLoFreq);
	double hiLog = log10(mHiFreq);
	double denom = hiLog - loLog;

	double delta = mHiFreq / ((double)(mWindowSize / 2.));
	double val0;
	double val1;

	
	val0 = my_envelope_get_value(p->mLogEnvelope, 0.0, 0.0);   //no scaling required - saved as dB
	val1 = my_envelope_get_value(p->mLogEnvelope, 1.0, 0.0);

	mFilterFuncR[0] = val0;
	double freq = delta;

	for (size_t i = 1; i <= mWindowSize / 2; i++)
	{
		double when = (log10(freq) - loLog) / denom;
		if (when < 0.)
		{
			mFilterFuncR[i] = val0;
		}
		else  if (when > 1.0)
		{
			mFilterFuncR[i] = val1;
		}
		else
		{
			mFilterFuncR[i] = my_envelope_get_value(p->mLogEnvelope, when, 0.0);
		}
		freq += delta;
	}
	mFilterFuncR[mWindowSize / 2] = val1;

	mFilterFuncR[0] = DB_TO_LINEAR(mFilterFuncR[0]);

	{
		size_t i = 1;
		for (; i < mWindowSize / 2; i++)
		{
			mFilterFuncR[i] = DB_TO_LINEAR(mFilterFuncR[i]);
			mFilterFuncR[mWindowSize - i] = mFilterFuncR[i];   //Fill entire array
		}
		mFilterFuncR[i] = DB_TO_LINEAR(mFilterFuncR[i]);   //do last one
	}

	//transfer to time domain to do the padding and windowing
	float *outr = mymalloc(mWindowSize * sizeof(float));
	float *outi = mymalloc(mWindowSize * sizeof(float));
	float *tmpBuffer = mymalloc(mWindowSize * sizeof(float));
	InverseRealFFT(mWindowSize, hFFT, mFilterFuncR, NULL, outr, tmpBuffer); // To time domain

	{
		size_t i = 0;
		for (; i <= (mM - 1) / 2; i++)
		{  //Windowing - could give a choice, fixed for now - MJS
		   //      double mult=0.54-0.46*cos(2*M_PI*(i+(mM-1)/2.0)/(mM-1));   //Hamming
		   //Blackman
			double mult =
				0.42 -
				0.5 * cos(2 * M_PI * (i + (mM - 1) / 2.0) / (mM - 1)) +
				.08 * cos(4 * M_PI * (i + (mM - 1) / 2.0) / (mM - 1));
			outr[i] *= mult;
			if (i != 0) {
				outr[mWindowSize - i] *= mult;
			}
		}
		for (; i <= mWindowSize / 2; i++)
		{   //Padding
			outr[i] = 0;
			outr[mWindowSize - i] = 0;
		}
	}
	float *tempr = mymalloc(mM * sizeof(float));
	{
		size_t i = 0;
		for (; i < (mM - 1) / 2; i++)
		{   //shift so that padding on right
			tempr[(mM - 1) / 2 + i] = outr[i];
			tempr[i] = outr[mWindowSize - (mM - 1) / 2 + i];
		}
		tempr[(mM - 1) / 2 + i] = outr[i];
	}

	for (size_t i = 0; i < mM; i++)
	{   //and copy useful values back
		outr[i] = tempr[i];
	}
	for (size_t i = mM; i < mWindowSize; i++)
	{   //rest is padding
		outr[i] = 0.;
	}

	//Back to the frequency domain so we can use it
	RealFFT(mWindowSize, hFFT, outr, mFilterFuncR, mFilterFuncI, tmpBuffer);

	free(outr);
	free(outi);
	free(tmpBuffer);
	free(tempr);
}

void set_equalizer_eq(struct _equalizer_t* p, double *eq, size_t count) {
	assert(count == p->NUMBER_OF_BANDS);
	memcpy(p->mEQVals, eq, count * sizeof(double));

	GraphicEQ(p, p->mLogEnvelope);
	CalcFilter(p);
}

void process_equalizer(struct _equalizer_t* p, float *buffer, size_t len) {
	if (len != p->mWindowSize) {
		assert(0);
		return;
	}
	float *mFilterFuncR = p->mFilterFuncR;
	float *mFilterFuncI = p->mFilterFuncI;
	float *mFFTBuffer = p->mFFTBuffer;
	FFTParam *hFFT = p->hFFT;
	float re, im;
	// Apply FFT
	RealFFTf(buffer, hFFT);
	//FFT(len, false, inr, NULL, outr, outi);

	// Apply filter
	// DC component is purely real
	mFFTBuffer[0] = buffer[0] * mFilterFuncR[0];
	for (size_t i = 1; i < (len / 2); i++)
	{
		re = buffer[hFFT->BitReversed[i]];
		im = buffer[hFFT->BitReversed[i] + 1];
		mFFTBuffer[2 * i] = re * mFilterFuncR[i] - im * mFilterFuncI[i];
		mFFTBuffer[2 * i + 1] = re * mFilterFuncI[i] + im * mFilterFuncR[i];
	}
	// Fs/2 component is purely real
	mFFTBuffer[1] = buffer[1] * mFilterFuncR[len / 2];

	// Inverse FFT and normalization
	InverseRealFFTf(mFFTBuffer, hFFT);
	ReorderToTime(hFFT, mFFTBuffer, buffer);
}

void delete_equalizer(struct _equalizer_t* p) {
	if (NULL != p) {
		my_envelope_free(p->mLogEnvelope);
		fftparam_free(p->hFFT);
		free(p->mFilterFuncR);
		free(p->mFilterFuncI);
		free(p->mFFTBuffer);
		free(p->mWhenSliders);
		free(p->mEQVals);
		free(p);
	}
}