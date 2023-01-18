#include "systick.h"
#include "stm32f10x.h"

void SysTickInit(void)
{
	 SysTick_Config(SystemCoreClock / 8);		
}

void DoDelay(uint32_t count)
{
	uint32_t tmp;
	SysTick->LOAD = count;			//计数器归零后，重新装载的值
	SysTick->CTRL = 0x01;		//启动定时器，归零后无动作
	SysTick->VAL = 0;			//清零计数器
	
	do{
		tmp = SysTick->CTRL;
	}while((tmp & 0x01) && !(tmp & (1 << 16)));
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

void DelayMs(uint32_t ms)
{
	uint32_t count = 9 * ms * 1000;
	DoDelay(count);
}