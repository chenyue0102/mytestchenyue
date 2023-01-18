#ifndef _LED_H_
#define _LED_H_
#include "stm32f10x.h"

#define LED_ON 1
#define LED_OFF 0

void LedInit(void);
void SetLed(int flag);
#endif