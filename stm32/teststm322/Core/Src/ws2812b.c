#include "ws2812b.h"

static GPIO_TypeDef *gPort = NULL;
static uint16_t gPin = 0;
static TIM_HandleTypeDef *gTimer = NULL;
static uint32_t gChannel = 0;

void initWS2812b(GPIO_TypeDef *port, uint16_t pin, TIM_HandleTypeDef *timer, uint32_t channel)
{
	gPort = port;
	gPin = pin;

	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = gPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(gPort, &GPIO_InitStruct);
    HAL_GPIO_WritePin(gPort, gPin, GPIO_PIN_RESET);

    gTimer = timer;
    gChannel = channel;
}

void startOutput(uint16_t *data, uint16_t len)
{
	HAL_TIM_PWM_Start_DMA(gTimer, gChannel, (const uint32_t*)data, len);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (gTimer != htim){
		return;
	}
	HAL_GPIO_WritePin(gPort, gPin, GPIO_PIN_RESET);
}
