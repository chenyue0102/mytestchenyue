// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：TimerQueue.h
// 创建日期：2015-09-18
// 创建人：陈月
// 文件说明：封装定时器类，定时器触发是同步回掉接口
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <map>
#include <atlcomcli.h>
#include "InterfaceTimer.h"
#include "NormalLock.h"

#define MAX_TIME_KEY		(65535)

class CTimerQueue
{
	struct TimerInfo
	{
		HANDLE hTimer;
		CComPtr<ITimerCallback> pTimerCallback;
#ifdef _DEBUG
		DWORD dwCallbackThreadID;
#endif

		TimerInfo()
			: hTimer(nullptr)
#ifdef _DEBUG
			, dwCallbackThreadID(0)
#endif
		{
			
		}
	};
	typedef std::map<long, TimerInfo> TimerInfoArray;
public:
	~CTimerQueue(void);
public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Instance
	// 函数参数：
	// 返 回 值：全局唯一的CTimerQueue实例
	// 函数说明：获取定时器全局唯一的实例
	// $_FUNCTION_END *********************************************************
	static CTimerQueue& Instance();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Open
	// 函数参数：
	// 返 回 值：true or false
	// 函数说明：初始化定时器类
	// $_FUNCTION_END *********************************************************
	bool Open();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Close
	// 函数参数：
	// 返 回 值：true or false
	// 函数说明：关闭定时器类
	// $_FUNCTION_END *********************************************************
	bool Close();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：CreateTimer
	// 函数参数：
	//			 DueTime				[输入]	第一次触发OnTimer的时间，如果是0，则立即触发OnTimer，单位：毫秒
	//			 Period					[输入]	第一次触发OnTimer后，定时触发OnTimer的间隔，如果为0，则第一次触发后，就不会再触发，单位：毫秒
	//			 pTimerCallback			[输入]	OnTimer时，调用的接口函数
	//			 lTimerKey				[输入/输出]	定时器的Key，销毁定时器的时候，
	//												如果为0，则内部会分配一个ID，否则使用外部指定的值，外部指定值必须小于MAX_TIME_KEY
	// 返 回 值：true or false
	// 函数说明：开启一个定时器
	// $_FUNCTION_END *********************************************************
	bool CreateTimer(DWORD DueTime, DWORD Period, ITimerCallback *pTimerCallback, long &lTimerKey);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：DestroyTimer
	// 函数参数：
	//			 lTimerKey				[输入]	定时器的Key
	//			 bWaitCallbackFinish	[输入]	是否等待OnTimer回掉函数退出
	// 返 回 值：true or false
	// 函数说明：关闭定时器类
	// $_FUNCTION_END *********************************************************
	bool DestroyTimer(long lTimerKey, bool bWaitCallbackFinish);
private:
	long GetKey();
	static VOID CALLBACK WaitOrTimerCallback(PVOID lpParameter,	BOOL TimerOrWaitFired);
	void InnerWaitOrTimerCallback(long lKey);
private:
	//禁止new创建类，全局只能一个
	CTimerQueue(void);
	//禁止拷贝构造创建类，全局只能一个
	CTimerQueue(const CTimerQueue &other){;}
private:
	volatile long		m_lKey;
	HANDLE				m_hTimeQueque;
	CNormalLock			m_NormalLock;
	TimerInfoArray		m_TimerInfoArray;
};

