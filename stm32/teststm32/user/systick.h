#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include <stdint.h>

void SysTickInit(void);
void DelayMs(uint32_t ms);
#endif