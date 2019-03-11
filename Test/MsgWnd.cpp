#include "MsgWnd.h"
#include <stdio.h>
#include <mutex>
#include <assert.h>
#include <tchar.h>

#define PROP_NAME _T("PropClassPointer")

static HINSTANCE g_hInstance = nullptr;
TCHAR g_WindowClass[256] = { 0 };
std::once_flag g_onceFlag;

static HMODULE ModuleHandleByAddr(const void* ptrAddr)
{
	MEMORY_BASIC_INFORMATION info;
	::VirtualQuery(ptrAddr, &info, sizeof(info));
	return (HMODULE)info.AllocationBase;
}

static HMODULE ThisModuleHandle()
{
	static HMODULE sInstance = ModuleHandleByAddr((void*)&ThisModuleHandle);
	return sInstance;
}

static void initMsgWnd()
{
	g_hInstance = ThisModuleHandle();
	_sntprintf(g_WindowClass, _countof(g_WindowClass) - 1, _T("MsgWnd_%p"), &MsgWnd::WindowProc);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MsgWnd::WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_WindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	ATOM n = RegisterClassEx(&wcex);
	assert(0 != n);
}


MsgWnd::MsgWnd()
{
	
}

MsgWnd::~MsgWnd()
{
	destroy();
}

bool MsgWnd::create(IMsgWndCallback * pCallback)
{
	destroy();
	bool bRet = false;

	do
	{
		std::call_once(g_onceFlag, &initMsgWnd);
		if (nullptr == pCallback)
		{
			assert(false);
			break;
		}
		if ((m_hWnd = CreateWindow(g_WindowClass, _T(""), WS_POPUP, 0, 0, 0, 0, NULL, NULL, g_hInstance, NULL)) == nullptr)
		{
			assert(false);
			break;
		}
		if (0 == SetProp(m_hWnd, PROP_NAME, this))
		{
			assert(false);
			break;
		}
		m_pIMsgWndCallback = pCallback;
		bRet = true;
	} while (false);
	
	return (nullptr != m_hWnd);
}

bool MsgWnd::destroy()
{
	if (nullptr != m_hWnd)
	{
		m_pIMsgWndCallback = nullptr;
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
	return true;
}

HWND MsgWnd::getHwnd()
{
	assert(nullptr != m_hWnd);
	return m_hWnd;
}

LRESULT MsgWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MsgWnd *pThis = reinterpret_cast<MsgWnd*>(GetProp(hwnd, PROP_NAME));
	if (nullptr != pThis
		&& nullptr != pThis->m_pIMsgWndCallback)
	{
		pThis->m_pIMsgWndCallback->onMsg(uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
