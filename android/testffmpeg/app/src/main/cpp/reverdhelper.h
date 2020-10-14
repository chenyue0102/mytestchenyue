#ifndef REVERD_HELPER_H
#define REVERD_HELPER_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __sf_reverb_state_st* reverb_state_st;
reverb_state_st alloc_reverb_state();
int set_reverb(reverb_state_st rv, const char *preset, int rate);
void reverb_float(reverb_state_st rv, float left, float right, float *outleft, float *outright);
void reverb_uint16(reverb_state_st rv, uint16_t left, uint16_t right, uint16_t *outleft, uint16_t *outright);
void free_reverb_state(reverb_state_st rv);

#ifdef __cplusplus
}
#endif

#endif
