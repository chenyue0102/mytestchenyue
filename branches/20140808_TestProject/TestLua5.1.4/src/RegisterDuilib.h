#pragma once

namespace DuiLib
{
	class CControlUI;
	class CContainerUI;
	class CComboUI;
	class CListLabelElementUI;

	class CPaintManagerUI;
	class CFrameWindow;
}

namespace DuiLib
{
	bool operator==(const CControlUI &l, const CControlUI &r);
}

namespace RegisterDuilib
{
void RegisterDuiWindow(lua_State *luaVM);

DuiLib::CContainerUI*	ToCContainerUI(DuiLib::CControlUI *pControlUI);
DuiLib::CComboUI*		ToCComboUI(DuiLib::CControlUI *pControlUI);


DuiLib::CListLabelElementUI* CreateCListLabelElementUI(DuiLib::CContainerUI *pContainer, int nPos);


DuiLib::CControlUI*		BuilderCControlUI(LPCTSTR lpstrXmlFileName, LPCTSTR lpstrType, 
										  DuiLib::CFrameWindow *pFrameWindow, DuiLib::CPaintManagerUI *pManager, DuiLib::CControlUI *pParent);

BOOL			CompareControl(DuiLib::CControlUI *pControlLeft, DuiLib::CControlUI *pControlRight);
}