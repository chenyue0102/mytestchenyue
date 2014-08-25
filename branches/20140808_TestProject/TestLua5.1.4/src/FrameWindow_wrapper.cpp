#include "StdAfx.h"
#include "FrameWindow_wrapper.h"


CFrameWindow_wrapper::CFrameWindow_wrapper(void)
{
	printf("CFrameWindow_wrapper\n");
}

CFrameWindow_wrapper::CFrameWindow_wrapper( const CFrameWindow_wrapper &other )
	: CFrameWindow(other)
{
	printf("copy CFrameWindow_wrapper\n");
}


CFrameWindow_wrapper::~CFrameWindow_wrapper(void)
{
	printf("~CFrameWindow_wrapper\n");
}

void CFrameWindow_wrapper::Init()
{
	call<void>("Init");
}

void CFrameWindow_wrapper::default_Init( DuiLib::CFrameWindow *ptr )
{
	return ptr->DuiLib::CFrameWindow::Init();
}

void CFrameWindow_wrapper::Notify( DuiLib::TNotifyUI& msg )
{
	call<void>("Notify", boost::ref(msg));
}

void CFrameWindow_wrapper::default_Notify( DuiLib::CFrameWindow *ptr, DuiLib::TNotifyUI& msg)
{
	return ptr->DuiLib::CFrameWindow::Notify(msg);
}

LRESULT CFrameWindow_wrapper::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return call<LRESULT>("HandleMessage", uMsg, wParam, lParam);
}

LRESULT CFrameWindow_wrapper::default_HandleMessage(DuiLib::CFrameWindow *ptr, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return ptr->DuiLib::CFrameWindow::HandleMessage(uMsg, wParam, lParam);
}

void CFrameWindow_wrapper::OnFinalMessage( HWND hWnd )
{
	call<void>("OnFinalMessage", hWnd);
}

void CFrameWindow_wrapper::default_OnFinalMessage( DuiLib::CFrameWindow *ptr, HWND hWnd )
{
	return ptr->DuiLib::CFrameWindow::OnFinalMessage(hWnd);
}

void CFrameWindow_wrapper::OnDealMessage( int aiMsgID, const std::string &strBuffer )
{
	call<void>("OnDealMessage", aiMsgID, boost::cref(strBuffer));
}

void CFrameWindow_wrapper::default_OnDealMessage( DuiLib::CFrameWindow *ptr, int aiMsgID, const std::string &strBuffer )
{
	return ptr->DuiLib::CFrameWindow::OnDealMessage(aiMsgID, strBuffer);
}
