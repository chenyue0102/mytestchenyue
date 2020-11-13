#include "equalizer.h"
#include <assert.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include "fft_param.h"

typedef float fft_type;
// Low frequency of the FFT.  20Hz is the
 // low range of human hearing
#define loFreqI 20

void init_equalizer() {
	init_fft_param();
}

void destroy_equalizer() {
	destroy_fft_param();
}

typedef struct _equalizer_t {
	size_t windowSize;
	double mLoFreq;
	double mHiFreq;
	float *mFilterFuncR, *mFilterFuncI;
}equalizer_t;

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
	assert((window_size & (window_size - 1)) == 0);
	equalizer_t *p = malloc(sizeof(equalizer_t));
	memset(p, 0, sizeof(equalizer_t));
	p->windowSize = window_size;
	p->mHiFreq = sample_rate / 2.;
	p->mLoFreq = loFreqI;
	p->mFilterFuncR = malloc(window_size * sizeof(float));
	p->mFilterFuncI = malloc(window_size * sizeof(float));


	return p;
}

void delete_equalizer(struct _equalizer_t* p) {
	if (NULL != p) {
		free(p->mFilterFuncR);
		free(p->mFilterFuncI);
		free(p);
	}
}