//
// Created by EDZ on 2020/11/11.
//
#include "sox_i.h"
#include <stdlib.h>
void *lsx_realloc(void *ptr, size_t newsize)
{
    if (ptr && newsize == 0) {
        free(ptr);
        return NULL;
    }

    if ((ptr = realloc(ptr, newsize)) == NULL) {
        //lsx_fail("out of memory");
        exit(2);
    }

    return ptr;
}
