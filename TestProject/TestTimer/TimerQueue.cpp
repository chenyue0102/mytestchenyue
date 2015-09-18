#include "TimerQueue.h"
#include <assert.h>

CTimerQueue::CTimerQueue()
	: m_lKey(1)
	, m_hTimeQueque(nullptr)
{

}

CTimerQueue::~CTimerQueue(void)
{
	assert(nullptr == m_hTimeQueque);
}

CTimerQueue& CTimerQueue::Instance()
{
	static CTimerQueue TimerQueue;
	return TimerQueue;
}

bool CTimerQueue::Open()
{
	bool bRes = false;

	do 
	{
		if (nullptr != m_hTimeQueque)
		{
			assert(false);
			break;
		}
		if (nullptr == (m_hTimeQueque = CreateTimerQueue()))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);
	return bRes;
}

bool CTimerQueue::Close()
{
	bool bRes = false;

	do 
	{
		if (nullptr == m_hTimeQueque)
		{
			bRes = true;
			break;
		}
		assert(0 == m_TimerInfoArray.size());
		TimerInfoArray InfoArray = m_TimerInfoArray;
		for each(auto &OneInfo in InfoArray)
		{
			DestroyTimer(OneInfo.first, false);
		}
		InfoArray.clear();
		m_TimerInfoArray.clear();

		if (!DeleteTimerQueue(m_hTimeQueque))
		{
			assert(false);
			break;
		}
		m_hTimeQueque = nullptr;
		bRes = true;
	} while (false);
	return bRes;
}

bool CTimerQueue::CreateTimer(DWORD DueTime, DWORD Period, ITimerCallback *pTimerCallback, DWORD dwUserData, long &lTimerKey)
{
	bool bRes = false;

	do 
	{
		if (0 == DueTime
			&& 0 == Period)
		{
			assert(false);
			break;
		}
		if (nullptr == pTimerCallback)
		{
			assert(false);
			break;
		}
		if (nullptr == m_hTimeQueque)
		{
			assert(false);
			break;
		}
		lTimerKey = GetKey();

		CAutoLock AutoLock(m_NormalLock);
		HANDLE hTimer = nullptr;
		if (!CreateTimerQueueTimer(&hTimer, m_hTimeQueque, (WAITORTIMERCALLBACK)&CTimerQueue::WaitOrTimerCallback, 
			reinterpret_cast<void*>(lTimerKey), DueTime, Period, 0))
		{
			assert(false);
			break;
		}
		TimerInfo Info;
		Info.hTimer = hTimer;
		Info.pTimerCallback = pTimerCallback;
		Info.dwUserData = dwUserData;
		m_TimerInfoArray.insert(std::make_pair(lTimerKey, Info));

		bRes = true;
	} while (false);

	return bRes;
}

bool CTimerQueue::DestroyTimer(long lTimerKey, bool bWaitCallbackFinish)
{
	bool bRes = false;

	do 
	{
		TimerInfo Info;
		{
			CAutoLock AutoLock(m_NormalLock);
			auto itor = m_TimerInfoArray.find(lTimerKey);
			if (itor == m_TimerInfoArray.end())
			{
				assert(false);
				break;
			}
			Info = itor->second;
			m_TimerInfoArray.erase(itor);
		}
		
#ifdef _DEBUG
		if (bWaitCallbackFinish)
		{
			//当等待退出的时候，关闭线程ID不能够与回掉ID相同，防止死锁
			if (Info.dwCallbackThreadID == GetCurrentThreadId())
			{
				assert(false);
			}
		}
#endif
		//If this parameter is INVALID_HANDLE_VALUE, the function waits for the timer callback function to complete before returning.
		//If this parameter is NULL, the function marks the timer for deletion and returns immediately
		HANDLE hCompletionEvent = nullptr;
		if (bWaitCallbackFinish)
		{
			hCompletionEvent = INVALID_HANDLE_VALUE;
		}
		if (!DeleteTimerQueueTimer(m_hTimeQueque, Info.hTimer, hCompletionEvent))
		{
			assert(false);
			break;
		}
		bRes = true;
	} while (false);
	return bRes;
}

long CTimerQueue::GetKey()
{
	return InterlockedIncrement(&m_lKey);
}

VOID CALLBACK CTimerQueue::WaitOrTimerCallback(PVOID lpParameter, BOOL TimerOrWaitFired)
{
	long lKey = reinterpret_cast<long>(lpParameter);
	CTimerQueue::Instance().InnerWaitOrTimerCallback(lKey);
}

void CTimerQueue::InnerWaitOrTimerCallback(long lKey)
{
	
	do 
	{
		TimerInfo Info;
		{
			CAutoLock AutoLock(m_NormalLock);
			auto itor = m_TimerInfoArray.find(lKey);
			if (itor == m_TimerInfoArray.end())
			{
				assert(false);
				break;
			}
#ifdef _DEBUG
			itor->second.dwCallbackThreadID = GetCurrentThreadId();
#endif
			Info = itor->second;
		}
		if (!Info.pTimerCallback)
		{
			assert(false);
			break;
		}
		Info.pTimerCallback->OnTimer(Info.dwUserData);
	} while (false);
}
