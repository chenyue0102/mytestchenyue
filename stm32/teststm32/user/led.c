#include "led.h"

#define LED_PORT GPIOA
#define LED_PIN GPIO_Pin_1

void LedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void SetLed(int flag)
{
	if (flag == LED_ON)
	{
		GPIO_SetBits(LED_PORT, LED_PIN);
	}
	else
	{
		GPIO_ResetBits(LED_PORT, LED_PIN);
	}
}