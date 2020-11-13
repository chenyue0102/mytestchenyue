#ifndef SOX_I_H_
#define SOX_I_H_
#include <malloc.h>
#include <stddef.h>
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif

#define UNUSED
#define array_length(a) (sizeof(a)/sizeof(a[0]))

#define lsx_malloc(size) lsx_realloc(NULL, (size))
#define lsx_calloc(n,s) (((n)*(s))? memset(lsx_malloc((n)*(s)),0,(n)*(s)) : NULL)
#ifndef M_LN10
#define M_LN10  2.30258509299404568402  /* natural log of 10 */
#endif
#define dB_to_linear(x) exp((x) * M_LN10 * 0.05)
#define midi_to_freq(n) (440 * pow(2,((n)-69)/12.))

void *lsx_realloc(void *ptr, size_t newsize);

#ifdef __cplusplus
}
#endif
#endif