#include "StdAfx.h"
#include ".\timequeue.h"

#define UM_ON_TIMER		(WM_USER + 5000)

void	CloseTlsWindow(HWND hWnd)
{
	if (NULL != hWnd)
	{
		CloseWindow(hWnd);
	}
}

CTimeQueue::CTimeQueue(void)
: m_hTimeQueque(NULL)
, m_hMsgWnd(NULL)
{

}

CTimeQueue::~CTimeQueue(void)
{
	if (NULL != m_hTimeQueque)
	{
		DeleteTimerQueue(m_hTimeQueque);
		m_hTimeQueque = NULL;
	}
	if (NULL != m_hMsgWnd)
	{
		DestroyWindow(m_hMsgWnd);
		m_hMsgWnd = NULL;
	}
	if (!m_strClassName.IsEmpty())
	{
		UnregisterClass(m_strClassName, GetInstance());
	}
}

BOOL	CTimeQueue::Init()
{
	BOOL bRes = FALSE;

	do 
	{
		if (NULL != m_hMsgWnd)
		{
			bRes = TRUE;
			break;
		}
		if (NULL == m_hTimeQueque)
		{
			m_hTimeQueque = CreateTimerQueue();
		}
		if (NULL == m_hTimeQueque)
		{
			break;
		}
		if (!RegisterWindowClass())
		{
			break;
		}

		DWORD dwStyle = WS_POPUP;
		
		m_hMsgWnd = CreateWindow(GetClassName(), NULL, dwStyle, 0, 0, 0, 0, NULL, NULL, GetInstance(), NULL);
		if (NULL == m_hMsgWnd)
		{
			break;
		}

		bRes = TRUE;
	} while (0);
	

	return bRes;
}

LRESULT CTimeQueue::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (UM_ON_TIMER == uMsg)
	{
		ITimeCallback *pCallback = reinterpret_cast<ITimeCallback*>(lParam);
		try
		{
			if (IsBadReadPtr(pCallback, sizeof(ITimeCallback)))
			{
				//这个已经被释放了
				ATLASSERT(0);
			}
			else
			{
				pCallback->OnTimer(static_cast<DWORD>(wParam));
			}
		}
		catch (...)
		{
			//ATLASSERT(0);
		}
		return 0;
	}
	else
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

DWORD	CTimeQueue::GetClassStyle()
{
	return 0;
}

LPCTSTR		CTimeQueue::GetClassName()
{
	return m_strClassName;
}

HINSTANCE	CTimeQueue::GetInstance()
{
	return GetModuleHandle(NULL);
}

BOOL	CTimeQueue::RegisterWindowClass()
{
	m_strClassName.Format(_T("TimeQueue:%p:%x"), GetInstance(), GetClassStyle());
	WNDCLASS wc = { 0 };
	if (::GetClassInfo(GetInstance(), GetClassName(), &wc))
	{
		return TRUE;
	}
	else
	{
		wc.style = GetClassStyle();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = NULL;
		wc.lpfnWndProc = CTimeQueue::WndProc;
		wc.hInstance = GetInstance();
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = GetClassName();
		ATOM ret = ::RegisterClass(&wc);
		ATLASSERT(ret!=NULL);
		return ret != NULL;
	}
}

VOID CTimeQueue::WaitOrTimerCallback(PVOID lpParameter,	BOOL TimerOrWaitFired)
{
	ONTIMER_INFO *pOnTimeInfo = reinterpret_cast<ONTIMER_INFO*>(lpParameter);

	if (NULL != pOnTimeInfo && IsWindow(pOnTimeInfo->hWnd))
	{
		ITimeCallback *pCallback = pOnTimeInfo->pCallback;
		PostMessage(pOnTimeInfo->hWnd, UM_ON_TIMER, pOnTimeInfo->dwUserData, (LPARAM)pCallback);	//让窗口所在的线程来处理回调，
	}
	else
	{
		ATLASSERT(0);
	}
}

HANDLE	CTimeQueue::CreateTimer(DWORD DueTime, DWORD Period, ITimeCallback *pCallback, DWORD dwUserData)
{
	if (NULL == m_hMsgWnd)
	{
		if (!Init())
		{
			ASSERT(FALSE);
			return NULL;
		}
	}
	HANDLE hTimer = NULL;

	{
		ONTIMER_INFO OneTimerInfo;
		OneTimerInfo.hTimer = NULL;
		OneTimerInfo.hWnd = m_hMsgWnd;
		ASSERT(IsWindow(OneTimerInfo.hWnd));
		OneTimerInfo.pCallback = pCallback;
		OneTimerInfo.dwUserData = dwUserData;
		m_OnTimerArray.push_back(OneTimerInfo);
	}
	ONTIMER_INFO_ARRAY::iterator itorTimer = m_OnTimerArray.end();
	--itorTimer;	//指向刚插入的
	CreateTimerQueueTimer(&hTimer, m_hTimeQueque, (WAITORTIMERCALLBACK)CTimeQueue::WaitOrTimerCallback, &*itorTimer, DueTime, Period, 0);

	if (NULL != hTimer)
	{
		itorTimer->hTimer = hTimer;
	}
	else
	{
		m_OnTimerArray.erase(itorTimer);
	}
	return hTimer;
}

BOOL	CTimeQueue::RemoveTimer(HANDLE hTimer)
{
	//If this parameter is INVALID_HANDLE_VALUE, the function waits for the timer callback function to complete before returning.
	//If this parameter is NULL, the function marks the timer for deletion and returns immediately
	BOOL bRes = DeleteTimerQueueTimer(m_hTimeQueque, hTimer, INVALID_HANDLE_VALUE);//等待回调函数处理完成才返回

	for (ONTIMER_INFO_ARRAY::iterator itor = m_OnTimerArray.begin();
		itor != m_OnTimerArray.end();
		++itor)
	{
		if (itor->hTimer == hTimer)
		{
			m_OnTimerArray.erase(itor);
			break;
		}
	}
	return bRes;
}