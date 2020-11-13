#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

//window_size must pow of 2
struct _equalizer_t* create_equalizer(double sample_rate, size_t window_size, float *Hz, size_t count);

void delete_equalizer(struct _equalizer_t* p);

#ifdef __cplusplus
}
#endif
