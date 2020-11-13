#pragma once
#include <stdint.h>

typedef float fft_type;

typedef struct {
	size_t Points;
	int *BitReversed;
	fft_type *SinTable;
}FFTParam;

void init_fft_param();

void destroy_fft_param();

FFTParam* get_fft_param(size_t fftlen);

void release_fft_param(FFTParam*);
