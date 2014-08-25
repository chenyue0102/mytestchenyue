#pragma once
#include "framewindow.h"

class CFrameWindow_wrapper 
	: public DuiLib::CFrameWindow
	, public luabind::wrap_base
{
public:
	CFrameWindow_wrapper(void);
	CFrameWindow_wrapper(const CFrameWindow_wrapper &other);
	~CFrameWindow_wrapper(void);
public:
	virtual void Init();
	static void default_Init(DuiLib::CFrameWindow *ptr);

	virtual void Notify(DuiLib::TNotifyUI& msg);
	static void default_Notify(DuiLib::CFrameWindow *ptr, DuiLib::TNotifyUI& msg);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT default_HandleMessage(DuiLib::CFrameWindow *ptr, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void OnFinalMessage(HWND hWnd);
	static void default_OnFinalMessage(DuiLib::CFrameWindow *ptr, HWND hWnd);

	virtual void OnDealMessage(int aiMsgID,  const std::string &strBuffer);
	static void default_OnDealMessage(DuiLib::CFrameWindow *ptr, int aiMsgID,  const std::string &strBuffer);
};

