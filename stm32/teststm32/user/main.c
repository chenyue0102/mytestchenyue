/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include "stm32_eval.h"
#include <stdbool.h>

#define LED_PIN GPIO_Pin_0
#define BUZZER_PIN GPIO_Pin_2
#define KEY_PIN GPIO_Pin_1				//轮询形式按键
#define KEY_EXTI_PIN GPIO_Pin_1		//中断形式按键


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void BuzzerInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

#define CPU_FREQUENCY (72 * 1000 * 1000)	//cpu主频
#define STCLK_FREQUENCY_DIVISION 8				//STCLK 分频
#define STCLK_MS_UNIT (CPU_FREQUENCY / STCLK_FREQUENCY_DIVISION / 1000)
#define STCLK_US_UNIT (CPU_FREQUENCY / STCLK_FREQUENCY_DIVISION / 1000 / 1000)

static void delayUnit(uint32_t i, uint32_t unit)
{
	uint32_t tmp;
	SysTick->LOAD = i * unit;			//计数器归零后，重新装载的值
	SysTick->CTRL = 0x01;					//启动定时器，归零后无动作
	SysTick->VAL = 0;							//清零计数器
	
	do
	{
		tmp = SysTick->CTRL;
	}while((tmp & 0x01) && !(tmp & (1 << 16)));
	SysTick->CTRL = 0;	//关闭计数器
	SysTick->VAL = 0;		//清空计数器
}

static void delayMs(uint32_t i)
{
	delayUnit(i, STCLK_MS_UNIT);
}

static void delayUs(uint32_t i)
{
	delayUnit(i, STCLK_US_UNIT);
}

static void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static bool checkKey(void)
{
	uint8_t key;
	uint8_t key2;
	do{
		//key = GPIO_ReadInputData(GPIOA);
		key = GPIO_ReadInputDataBit(GPIOB, KEY_PIN);
		delayMs(10);
		key2 = GPIO_ReadInputDataBit(GPIOB, KEY_PIN);
		//key2 = GPIO_ReadInputData(GPIOA);
	}while(key != key2);
	return Bit_RESET == key;
}
bool keyPressed = false;


#define DIGITAL_PIN_1 GPIO_Pin_1
#define DIGITAL_PIN_2 GPIO_Pin_2
#define DIGITAL_PIN_3 GPIO_Pin_3
#define DIGITAL_PIN_4 GPIO_Pin_4
#define DIGITAL_PIN_5 GPIO_Pin_5
#define DIGITAL_PIN_6 GPIO_Pin_6
#define DIGITAL_PIN_7 GPIO_Pin_7
static void DigitalInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = DIGITAL_PIN_1 | DIGITAL_PIN_2 | DIGITAL_PIN_3	| DIGITAL_PIN_4 | DIGITAL_PIN_5 | DIGITAL_PIN_6 | DIGITAL_PIN_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

#define DIGITAL_ON Bit_RESET
#define DIGITAL_OFF Bit_SET

/*
	1
2   3
  4
5	  6
  7
*/
static void showNumber(int number)
{
	int i = 0;
	const int light[][7] = {
		//   1            2            3           4            5             6           7
		{DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF,  DIGITAL_ON,    DIGITAL_ON, DIGITAL_ON},//0
		{DIGITAL_OFF, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF},//1
		{DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON},//2
		{DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON},//3
		{DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF},//4
		{DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON},//5
		{DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON},//6
		{DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF, DIGITAL_OFF, DIGITAL_ON, DIGITAL_OFF},//7
		{DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON},//8
		{DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_ON, DIGITAL_OFF, DIGITAL_ON, DIGITAL_ON},//9
		
	};
	const uint16_t pins[] = {DIGITAL_PIN_1, DIGITAL_PIN_2, DIGITAL_PIN_3, DIGITAL_PIN_4, DIGITAL_PIN_5, DIGITAL_PIN_6, DIGITAL_PIN_7};
	for (i = 0; i < 7; i++)
	{
		GPIO_WriteBit(GPIOA, pins[i], light[number][i]);
	}
}

void EXTIKeyInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//init input
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = KEY_EXTI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//enable  afio clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//connect exti0 line to pa 03
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	//config exti0
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升下降启用中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;							//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;	//指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;					//指定相应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//中断启用
	NVIC_Init(&NVIC_InitStructure);
}

//中断
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		bool keyPressed = checkKey();
		if (keyPressed){
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		}else{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

//定时器,
void TIMInit(void)
{
	//打开TIM6的APB1的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 36000 - 1;								//自动装在周期,CPU频率36Mhz，2倍频系数
	TIM_TimeBaseStructure.TIM_Prescaler = (2000 - 1);						//预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);												//清除中断处理位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);									//打开中断
	TIM_Cmd(TIM2, ENABLE);																			//使能中断外设
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;							//中断通断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//相应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//中断使能
	NVIC_Init(&NVIC_InitStructure);
}

BitAction timLedFlag = Bit_RESET;
void TIM2_IRQHandler(void)
{
	TIM_ClearFlag(TIM2, TIM_IT_Update);
	if (timLedFlag == Bit_RESET)
	{
		timLedFlag = Bit_SET;
	}
	else
	{
		timLedFlag = Bit_RESET;
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, timLedFlag);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

	SystemInit();
	
	LEDInit();
	//BuzzerInit();
	//KeyInit();
	//EXTIKeyInit();
	//DigitalInit();
	TIMInit();
	
	int num = 0;
	bool oldValue = false;
  while (1)
  {
		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		//GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		delayMs(50);
		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		//GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		//delayMs(50);
		
		
		/*keyPressed = checkKey();
		if (keyPressed){
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		}else{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		}
		
		if (keyPressed && !oldValue)
		{
			num++;
			if (num > 9)
			{
				num = 0;
			}
			showNumber(num);
		}
		oldValue = keyPressed;
		*/
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

