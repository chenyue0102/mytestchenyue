#pragma once
#include <list>
#include <atlstr.h>

interface ITimeCallback
{
	virtual void OnTimer(ULONG ulUserData) = 0;
};
class CTimeQueue
{
public:
	CTimeQueue(void);
	~CTimeQueue(void);
public:
	BOOL	Init();

	HANDLE	CreateTimer(DWORD DueTime, DWORD Period, ITimeCallback *pCallback, DWORD dwUserData);
	BOOL	RemoveTimer(HANDLE hTimer);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK WaitOrTimerCallback(PVOID lpParameter,	BOOL TimerOrWaitFired);

	BOOL		RegisterWindowClass();
	DWORD		GetClassStyle();
	HINSTANCE	GetInstance();
	LPCTSTR		GetClassName();
private:
	HWND	m_hMsgWnd;	//当前线程的处理窗口，类库是多线程安全的
	CString	m_strClassName;
	HANDLE	m_hTimeQueque;

	typedef struct _ONTIMER_INFO
	{
		HANDLE			hTimer;
		HWND			hWnd;
		DWORD			dwUserData;
		ITimeCallback	*pCallback;
	}ONTIMER_INFO;
	typedef std::list<ONTIMER_INFO>		ONTIMER_INFO_ARRAY;
	ONTIMER_INFO_ARRAY	m_OnTimerArray;
};
