#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif


//window_size must pow of 2
struct _equalizer_t* create_equalizer(double sample_rate, size_t window_size, double *hz, size_t count);

void set_equalizer_eq(struct _equalizer_t* p, double *eq, size_t count);

void process_equalizer(struct _equalizer_t* p, float *buffer, size_t len);

void delete_equalizer(struct _equalizer_t* p);


#ifdef __cplusplus
}
#endif
