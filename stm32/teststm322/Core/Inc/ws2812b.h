#ifndef _WS2812B_H_
#define _WS2812B_H_
#include "stm32f1xx_hal.h"


void initWS2812b(GPIO_TypeDef *port, uint16_t pin, TIM_HandleTypeDef *timer, uint32_t channel);

void startOutput(uint16_t *data, uint16_t len);

#endif
