#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float fft_type;
typedef struct {
	size_t Points;
	int *BitReversed;
	fft_type *SinTable;
}FFTParam;
FFTParam* fftparam_alloc(size_t fftlen);
void fftparam_free(FFTParam* p);
void RealFFTf(fft_type *buffer, const FFTParam *h);
void RealFFT(size_t NumSamples, FFTParam *hFFT, const float *RealIn, float *RealOut, float *ImagOut, float *tmpBuffer);
void InverseRealFFTf(fft_type *buffer, const FFTParam *h);
void InverseRealFFT(size_t NumSamples, FFTParam *hFFT, const float *RealIn, const float *ImagIn, float *RealOut, float *tmpBuffer);
void ReorderToTime(const FFTParam *hFFT, const fft_type *buffer, fft_type *TimeOut);

#ifdef __cplusplus
}
#endif