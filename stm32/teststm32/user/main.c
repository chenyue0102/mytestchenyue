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

void delayMs(uint32_t i)
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
		
		USART_SendData(USART1, 'x');
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == Bit_RESET);
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

void USARTInit(void)
{
	//启用USART1时钟,RCC_APB2Periph_AFIO端口复用
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	//enable usart1
	USART_Cmd(USART1, ENABLE);
	
	//使能中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//清理USARTx的标记
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//设置中断
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//相应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART1SendData(uint16_t c)
{
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == Bit_RESET);
	USART_ClearFlag(USART1, USART_FLAG_TC);
}

void USART1_IRQHandler(void)
{
	uint16_t r = USART_ReceiveData(USART1);
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	
	if ('0' == r)
	{
		timLedFlag = Bit_SET;
	}
	else
	{
		timLedFlag = Bit_RESET;
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, timLedFlag);
	
	USART1SendData(r);
}
#define SPI_SCL GPIO_Pin_13			//时钟
#define SPI_MOSI GPIO_Pin_15			//主机输出
#define SPI_SDA 
//#define SPI_MISO GPIO_
#define OLED_CS GPIO_Pin_11				//片选信号
#define OLED_RESET GPIO_Pin_12		//液晶屏复位信号，低电平复位
#define OLED_DC GPIO_Pin_10			//液晶屏寄存器/数据选择信号，低电平：寄存器，高电平：数据 

#define LED_LIGHT GPIO_Pin_9 		//背光

#define OLED_CMD 0
#define OLED_DATA 1

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
	u8  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	
_lcd_dev lcddev;

#define LCD_W 320
#define LCD_H 480

//#define OLED_RST_Clr() GPIO_ResetBits(GPIOA, OLED_RESET)
//#define OLED_RST_Set() GPIO_SetBits(GPIOA, OLED_RESET)

//#define OLED_DC_Clr() GPIO_ResetBits(GPIOA, OLED_DC)
//#define OLED_DC_Set() GPIO_SetBits(GPIOA, OLED_DC)

//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA, SPI_SCL)
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOA, SPI_SCL)

//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA, SPI_SDA)
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOA, SPI_SDA)


void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//配置管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED_LIGHT | OLED_DC | OLED_CS | SPI_SCL | OLED_RESET | SPI_MOSI;//输出与时钟
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*
	GPIO_InitStructure.GPIO_Pin = SPI_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	*/
}

#define LCD_RST_CLR() GPIO_ResetBits(GPIOB, OLED_RESET)
#define LCD_RST_SET() GPIO_SetBits(GPIOB, OLED_RESET)
#define LCD_DC_CLR() GPIO_ResetBits(GPIOB, OLED_DC)
#define LCD_DC_SET() GPIO_SetBits(GPIOB, OLED_DC)
#define LCD_CS_CLR() GPIO_ResetBits(GPIOB, OLED_CS)
#define LCD_CS_SET() GPIO_SetBits(GPIOB, OLED_CS)
#define SPI_MOSI_SET() GPIO_SetBits(GPIOB, SPI_MOSI)
#define SPI_MOSI_CLR() GPIO_ResetBits(GPIOB, SPI_MOSI)
#define SPI_SCLK_CLR() GPIO_ResetBits(GPIOB, SPI_SCL)
#define SPI_SCLK_SET() GPIO_SetBits(GPIOB, SPI_SCL)


void LCD_RESET(void)
{
	LCD_RST_CLR();
	delayMs(100);
	LCD_RST_SET();
	delayMs(50);
}

void SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
	  if(Data&0x80)	
	  SPI_MOSI_SET(); 
      else SPI_MOSI_CLR();
	   
      SPI_SCLK_CLR();       
      SPI_SCLK_SET();
      Data<<=1; 
	}
}

void LCD_WR_DATA(u8 data)
{
	LCD_CS_CLR();
	LCD_DC_SET();
	SPIv_WriteData(data);
	LCD_CS_SET();
}

void LCD_WR_REG(u8 data)
{
	LCD_CS_CLR();
	LCD_DC_CLR();
	SPIv_WriteData(data);
	LCD_CS_SET();
}

void LCD_WriteReg(u8 reg, u16 regValue)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(regValue);
}

void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;	
		default:break;
	}		
}	

void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);

	LCD_WriteRAM_Prepare();	//	
}   

#define USE_HORIZONTAL  	 0

void Lcd_WriteData_16Bit(u16 Data)
{	
  //18Bit	
	LCD_WR_DATA((Data>>8)&0xF8);//RED
	LCD_WR_DATA((Data>>3)&0xFC);//GREEN
	LCD_WR_DATA(Data<<3);//BLUE
}

void LCD_Clear(u16 Color)
{
  unsigned int i,m;  
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	LCD_CS_CLR();
	LCD_DC_SET();
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {	
			Lcd_WriteData_16Bit(Color);
		}
	}
	 LCD_CS_SET();
} 

#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{  	
	u16 i,j;			
	u16 width=ex-sx+1; 		//
	u16 height=ey-sy+1;		//
	LCD_SetWindows(sx,sy,ex,ey);//
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		Lcd_WriteData_16Bit(color);	//
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//
}
void mainApp(void);

void HAL_Delay(uint32_t t)
{
	delayMs(t);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */	

void LCD_Init()
{
	LCD_GPIOInit();
	LCD_RESET();
	
	LCD_WR_REG(0XF7);
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x51);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x82);
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x09);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x41);
	LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x80);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0xB0);
	LCD_WR_DATA(0x11);
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x02);
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x42);
	LCD_WR_REG(0xB7);
	LCD_WR_DATA(0xc6);
	LCD_WR_REG(0xBE);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0xE9);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x36);
	LCD_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x66);
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x89);
	LCD_WR_DATA(0x4B);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0XE1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x1A);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2F);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x11);
	delayMs(120);
	LCD_WR_REG(0x29);
	
  LCD_direction(USE_HORIZONTAL);
	GPIO_SetBits(GPIOB, LED_LIGHT);
	LCD_Clear(WHITE);
}
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

	SystemInit();
	//LEDInit();
	//BuzzerInit();
	//KeyInit();
	//EXTIKeyInit();
	//DigitalInit();
	//TIMInit();
	//USARTInit();
	//OLED_Init();
	LCD_Init();
	
	//mainApp();
	
	int num = 0;
	bool oldValue = false;
  while (1)
  {
		LCD_Fill(10,10,50,50,BLUE);
		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		//GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		delayMs(50);
		//USART1SendData('a');
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

