#ifndef SOX_REVERB_H_
#define SOX_REVERB_H_
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

struct _my_reverb_t* create_reverb(
	size_t channels,
	double sample_rate_Hz,
	double wet_gain_dB,
	double room_scale,     /* % */
	double reverberance,   /* % */
	double hf_damping,     /* % */
	double pre_delay_ms,
	double stereo_depth,
	size_t buffer_size);

void delete_reverb(struct _my_reverb_t *reverb);

void process_reverb(struct _my_reverb_t *reverb, float* in[], float *out[], size_t len);

#ifdef __cplusplus
}
#endif
#endif