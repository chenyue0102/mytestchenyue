// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�TimerQueue.h
// �������ڣ�2015-09-18
// �����ˣ�����
// �ļ�˵������װ��ʱ���࣬��ʱ��������ͬ���ص��ӿ�
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <map>
#include <atlcomcli.h>
#include "InterfaceTimer.h"
#include "NormalLock.h"

class CTimerQueue
{
	struct TimerInfo
	{
		HANDLE hTimer;
		DWORD dwUserData;
		CComPtr<ITimerCallback> pTimerCallback;
#ifdef _DEBUG
		DWORD dwCallbackThreadID;
#endif

		TimerInfo()
			: hTimer(nullptr)
			, dwUserData(0)
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
	// �������ƣ�Instance
	// ����������
	// �� �� ֵ��ȫ��Ψһ��CTimerQueueʵ��
	// ����˵������ȡ��ʱ��ȫ��Ψһ��ʵ��
	// $_FUNCTION_END *********************************************************
	static CTimerQueue& Instance();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Open
	// ����������
	// �� �� ֵ��true or false
	// ����˵������ʼ����ʱ����
	// $_FUNCTION_END *********************************************************
	bool Open();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Close
	// ����������
	// �� �� ֵ��true or false
	// ����˵�����رն�ʱ����
	// $_FUNCTION_END *********************************************************
	bool Close();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�CreateTimer
	// ����������
	//			 DueTime				[����]	��һ�δ���OnTimer��ʱ�䣬�����0������������OnTimer
	//			 Period					[����]	��һ�δ���OnTimer�󣬶�ʱ����OnTimer�ļ�������Ϊ0�����һ�δ����󣬾Ͳ����ٴ���
	//			 pTimerCallback			[����]	OnTimerʱ�����õĽӿں���
	//			 dwUserData				[����]	OnTimerʱ�����ýӿڵĲ���
	//			 lTimerKey				[���]	��ʱ����Key�����ٶ�ʱ����ʱ��ʹ��
	// �� �� ֵ��true or false
	// ����˵��������һ����ʱ��
	// $_FUNCTION_END *********************************************************
	bool CreateTimer(DWORD DueTime, DWORD Period, 
			ITimerCallback *pTimerCallback, DWORD dwUserData, long &lTimerKey);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�DestroyTimer
	// ����������
	//			 lTimerKey				[����]	��ʱ����Key
	//			 bWaitCallbackFinish	[����]	�Ƿ�ȴ�OnTimer�ص������˳�
	// �� �� ֵ��true or false
	// ����˵�����رն�ʱ����
	// $_FUNCTION_END *********************************************************
	bool DestroyTimer(long lTimerKey, bool bWaitCallbackFinish);
private:
	long GetKey();
	static VOID CALLBACK WaitOrTimerCallback(PVOID lpParameter,	BOOL TimerOrWaitFired);
	void InnerWaitOrTimerCallback(long lKey);
private:
	//��ֹnew�����࣬ȫ��ֻ��һ��
	CTimerQueue(void);
	//��ֹ�������촴���࣬ȫ��ֻ��һ��
	CTimerQueue(const CTimerQueue &other){;}
private:
	volatile long		m_lKey;
	HANDLE				m_hTimeQueque;
	CNormalLock			m_NormalLock;
	TimerInfoArray		m_TimerInfoArray;
};

