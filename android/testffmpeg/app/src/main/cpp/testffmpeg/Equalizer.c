#include "Equalizer.h"
#include <assert.h>
#include <math.h>

typedef float fft_type;
// Low frequency of the FFT.  20Hz is the
 // low range of human hearing
#define loFreqI 20

typedef struct  {
	size_t Points;
	int *BitReversed;
	fft_type *SinTable;
}FFTParam;


/*
*  Forward FFT routine.  Must call GetFFT(fftlen) first!
*
*  Note: Output is BIT-REVERSED! so you must use the BitReversed to
*        get legible output, (i.e. Real_i = buffer[ h->BitReversed[i] ]
*                                  Imag_i = buffer[ h->BitReversed[i]+1 ] )
*        Input is in normal order.
*
* Output buffer[0] is the DC bin, and output buffer[1] is the Fs/2 bin
* - this can be done because both values will always be real only
* - this allows us to not have to allocate an extra complex value for the Fs/2 bin
*
*  Note: The scaling on this is done according to the standard FFT definition,
*        so a unit amplitude DC signal will output an amplitude of (N)
*        (Older revisions would progressively scale the input, so the output
*        values would be similar in amplitude to the input values, which is
*        good when using fixed point arithmetic)
*/
void RealFFTf(fft_type *buffer, const FFTParam *h)
{
	fft_type *A, *B;
	const fft_type *sptr;
	const fft_type *endptr1, *endptr2;
	const int *br1, *br2;
	fft_type HRplus, HRminus, HIplus, HIminus;
	fft_type v1, v2, sin, cos;

	auto ButterfliesPerGroup = h->Points / 2;

	/*
	*  Butterfly:
	*     Ain-----Aout
	*         \ /
	*         / \
	*     Bin-----Bout
	*/

	endptr1 = buffer + h->Points * 2;

	while (ButterfliesPerGroup > 0)
	{
		A = buffer;
		B = buffer + ButterfliesPerGroup * 2;
		sptr = h->SinTable;

		while (A < endptr1)
		{
			sin = *sptr;
			cos = *(sptr + 1);
			endptr2 = B;
			while (A < endptr2)
			{
				v1 = *B * cos + *(B + 1) * sin;
				v2 = *B * sin - *(B + 1) * cos;
				*B = (*A + v1);
				*(A++) = *(B++) - 2 * v1;
				*B = (*A - v2);
				*(A++) = *(B++) + 2 * v2;
			}
			A = B;
			B += ButterfliesPerGroup * 2;
			sptr += 2;
		}
		ButterfliesPerGroup >>= 1;
	}
	/* Massage output to get the output for a real input sequence. */
	br1 = h->BitReversed + 1;
	br2 = h->BitReversed + h->Points - 1;

	while (br1 < br2)
	{
		sin = h->SinTable[*br1];
		cos = h->SinTable[*br1 + 1];
		A = buffer + *br1;
		B = buffer + *br2;
		HRplus = (HRminus = *A - *B) + (*B * 2);
		HIplus = (HIminus = *(A + 1) - *(B + 1)) + (*(B + 1) * 2);
		v1 = (sin*HRminus - cos * HIplus);
		v2 = (cos*HRminus + sin * HIplus);
		*A = (HRplus + v1) * (fft_type)0.5;
		*B = *A - v1;
		*(A + 1) = (HIminus + v2) * (fft_type)0.5;
		*(B + 1) = *(A + 1) - HIminus;

		br1++;
		br2--;
	}
	/* Handle the center bin (just need a conjugate) */
	A = buffer + *br1 + 1;
	*A = -*A;
	/* Handle DC bin separately - and ignore the Fs/2 bin
	buffer[0]+=buffer[1];
	buffer[1]=(fft_type)0;*/
	/* Handle DC and Fs/2 bins separately */
	/* Put the Fs/2 value into the imaginary part of the DC bin */
	v1 = buffer[0] - buffer[1];
	buffer[0] += buffer[1];
	buffer[1] = v1;
}

typedef struct _equalizer_t {
	size_t windowSize;
	double mLoFreq;
	double mHiFreq;
	FFTParam hFFT;
	float *mFilterFuncR, *mFilterFuncI;
}equalizer_t;

void init_fft(size_t fftlen, FFTParam *h) {
	int temp;
	h->Points = fftlen / 2;
	h->SinTable = malloc(2 * h->Points * sizeof(fft_type));
	h->BitReversed = malloc(h->Points * sizeof(int));
	
	for (size_t i = 0; i < h->Points; i++) {
		temp = 0;
		for (size_t mask = h->Points / 2; mask > 0; mask >>= 1) {
			temp = (temp >> 1) + (i & mask ? h->Points : 0);
		}
		h->BitReversed[i] = temp;
	}

	for (size_t i = 0; i < h->Points; i++) {
		h->SinTable[h->BitReversed[i]] = (fft_type)-sin(2 * M_PI * i / (2 * h->Points));
		h->SinTable[h->BitReversed[i + 1]] = (fft_type)-cos(2 * M_PI * i / (2 * h->Points));
	}
}

void calc_filter(equalizer_t *p) {
	double mLoFreq = p->mLoFreq;
	double mHiFreq = p->mHiFreq;
	size_t mWindowSize = p->windowSize;


	double loLog = log10(mLoFreq);
	double hiLog = log10(mHiFreq);
	double denom = hiLog - loLog;

	double delta = mHiFreq / ((double)(mWindowSize / 2.));
	double val0;
	double val1;
}

equalizer_t* create_equalizer(double sample_rate, size_t window_size, float *Hz, size_t count) {
	assert(window_size & (window_size - 1) == 0);
	equalizer_t *p = malloc(sizeof(equalizer_t));
	memset(p, 0, sizeof(equalizer_t));
	p->windowSize = window_size;
	init_fft(window_size, &p->hFFT);
	p->mHiFreq = sample_rate / 2.;
	p->mLoFreq = loFreqI;
	p->mFilterFuncR = malloc(window_size * sizeof(float));
	p->mFilterFuncI = malloc(window_size * sizeof(float));


	return p;
}

void delete_equalizer(struct _equalizer_t* p) {
	if (NULL != p) {
		free(p->hFFT.BitReversed);
		free(p->hFFT.SinTable);
		free(p->mFilterFuncR);
		free(p->mFilterFuncI);
		free(p);
	}
}