#pragma once
#include <Unknwn.h>
#ifndef interface
#define interface struct
#endif

interface ITimerCallback : public IUnknown
{
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：OnTimer
	// 函数参数：
	//			 dwUserData				[输入]	用户在启动定时器的时候，所传入的参数
	// 返 回 值：
	// 函数说明：超时触发了的定时回掉函数
	// $_FUNCTION_END *********************************************************
	virtual void STDMETHODCALLTYPE OnTimer(DWORD dwUserData) = 0;
};