#pragma once
#include <Windows.h>

struct IMsgWndCallback
{
	virtual void onMsg(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};
class MsgWnd
{
public:
	MsgWnd();
	~MsgWnd();
public:
	bool create(IMsgWndCallback *pCallback);
	bool destroy();
	HWND getHwnd();
private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	friend void initMsgWnd();
	HWND m_hWnd;
	IMsgWndCallback *m_pIMsgWndCallback;
};

