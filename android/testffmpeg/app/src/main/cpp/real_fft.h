#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void RealFFT(size_t NumSamples, const float *RealIn, float *RealOut, float *ImagOut, float *tmpBuffer);
void InverseRealFFT(size_t NumSamples, const float *RealIn, const float *ImagIn, float *RealOut, float *tmpBuffer);

#ifdef __cplusplus
}
#endif