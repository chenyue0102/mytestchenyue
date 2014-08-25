#include "StdAfx.h"
#include "RegisterDuilib.h"
#include "UIlib.h"
#include "FrameWindow.h"
#include "FrameWindow_wrapper.h"
#include "ListElementUI_wrapper.h"
#include "boost/shared_ptr.hpp"
#include <luabind/operator.hpp>

using namespace DuiLib;

template <>
struct default_converter<DuiLib::CStdString>
	: native_converter_base<DuiLib::CStdString>
{
	static int compute_score(lua_State* L, int index)
	{
		return lua_type(L, index) == LUA_TSTRING ? 0 : -1;
	}

	DuiLib::CStdString from(lua_State* L, int index)
	{
		return DuiLib::CStdString(lua_tostring(L, index), lua_strlen(L, index));
	}

	void to(lua_State* L, DuiLib::CStdString const& value)
	{
		lua_pushlstring(L, value.GetData(), value.GetLength());
	}
};

template <>
struct default_converter<DuiLib::CStdString const>
	: default_converter<DuiLib::CStdString>
{};

template <>
struct default_converter<DuiLib::CStdString const&>
	: default_converter<DuiLib::CStdString>
{};


//template <>
//struct default_converter<HWND>
//{
//	typedef boost::mpl::true_ is_native;
//
//	int const consumed_args(...)
//	{
//		return 1;
//	}
//
//	template <class U>
//		static int match(lua_State* L, U, int index)
//	{
//		return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;
//	}
//
//	template <class HWND__>
//		HWND apply(lua_State* L, luabind::detail::by_pointer<HWND__>, int index)
//	{
//		unsigned long ulValue = static_cast<unsigned long>(lua_tonumber(L, index));
//		return reinterpret_cast<HWND>(ulValue);
//	}
//
//	void apply(lua_State* L, HWND hwnd)
//	{
//		unsigned long ulValue = reinterpret_cast<unsigned long>(hwnd);
//		lua_pushnumber(L, ulValue);
//	}
//
//	template <class U>
//		void converter_postcall(lua_State*, U, int)
//	{}
//};

void ThemeNameSetter(MSGSTRU_SNSUI_SETTING_THEME &ThemeInfo, const std::string &strThemeName)
{
	_tcsncpy(ThemeInfo.szThemeName, strThemeName.c_str(), _countof(ThemeInfo.szThemeName));
}

std::string ThemeNameGetter(const MSGSTRU_SNSUI_SETTING_THEME &ThemeInfo)
{
	return std::string(ThemeInfo.szThemeName);
}

void BackImageSetter(MSGSTRU_SNSUI_SETTING_THEME &ThemeInfo, const std::string &strBackImage)
{
	_tcsncpy(ThemeInfo.szBackImage, strBackImage.c_str(), _countof(ThemeInfo.szBackImage));
}

std::string BackImageGetter(const MSGSTRU_SNSUI_SETTING_THEME &ThemeInfo)
{
	return std::string(ThemeInfo.szBackImage);
}

template<typename T>
BOOL MemcpyCopyStruct(T &t, const std::string &strBuffer)
{
	if (sizeof(T) == strBuffer.size())
	{
		memcpy(&t, strBuffer.data(), sizeof(T));
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

namespace DuiLib
{
bool operator==( CControlUI const &l,  CControlUI const &r)
{
	const CControlUI *pleft = &l;
	const CControlUI *pright = &r;
	return pleft== pright;
}
}

namespace RegisterDuilib
{

void RegisterDuiWindow( lua_State *luaVM )
{
	luabind::module(luaVM, "DuiLib")
	[
		class_<HWND__>("HWND").
		def(constructor<>())
	];
	luabind::module(luaVM, "DuiLib")
	[
		class_<HMENU__>("HMENU").
		def(constructor<>())
	];
	luabind::module(luaVM, "DuiLib")
	[
		class_<HDC__>("HDC").
		def(constructor<>())
	];

	luabind::module(luaVM)
	[
		class_<SIZE>("SIZE").
		def(constructor<>()).
		def_readwrite("cx", &SIZE::cx).
		def_readwrite("cy", &SIZE::cy)
	];
	
	luabind::module(luaVM, "DuiLib")
	[
		class_<CControlUI>("CControlUI").
		def(constructor<>()).
		def(const_self == const_self).
		def("GetName", &CControlUI::GetName).
		def("SetName", &CControlUI::SetName).
		def("GetClass", &CControlUI::GetClass).
		def("GetText", &CControlUI::GetText).
		def("SetText", &CControlUI::SetText).
		def("GetToolTip", &CControlUI::GetToolTip).
		def("SetToolTip", &CControlUI::SetToolTip)
	];

	luabind::module(luaVM, "DuiLib")
	[
		class_<CContainerUI, CControlUI>("CContainerUI").
		def(constructor<>())
	];

	luabind::module(luaVM, "DuiLib")
	[
		class_<CComboUI, CContainerUI>("CComboUI").
		def(constructor<>()).
		def("GetCurSel", &CComboUI::GetCurSel).
		def("SelectItem", &CComboUI::SelectItem)
	];


	luabind::module(luaVM, "DuiLib")
	[
		class_<CListElementUI, CControlUI, CListElementUI_wrapper>("CListElementUI").
		def(constructor<>())
	];


	luabind::module(luaVM, "DuiLib")
	[
		class_<CListLabelElementUI, CListElementUI>("CListLabelElementUI").
		def(constructor<>())
	];

	luabind::module(luaVM, "DuiLib")
	[
		class_<TNotifyUI>("TNotifyUI").
		def(constructor<>()).
		def_readwrite("sType", &TNotifyUI::sType).
		def_readwrite("pSender", &TNotifyUI::pSender).
		def_readwrite("dwTimestamp", &TNotifyUI::dwTimestamp).
		def_readwrite("ptMouse", &TNotifyUI::ptMouse).
		def_readwrite("wParam", &TNotifyUI::wParam).
		def_readwrite("lParam", &TNotifyUI::lParam)
	];

	luabind::module(luaVM, "DuiLib")
	[
		class_<CPaintManagerUI>("CPaintManagerUI").
		def(constructor<>()).
		def("GetPaintDC", &CPaintManagerUI::GetPaintDC).
		def("GetPaintWindow", &CPaintManagerUI::GetPaintWindow).
		def("FindSubControlByName", &CPaintManagerUI::FindSubControlByName, dependency(result, _1)).
		def("GetRoot", &CPaintManagerUI::GetRoot, dependency(result, _1)).
		scope
		[
			def("SetResourcePath", &CPaintManagerUI::SetResourcePath),
			def("GetResourcePath", &CPaintManagerUI::GetResourcePath),
			def("MessageLoop", &CPaintManagerUI::MessageLoop)
		]
	];

	luabind::module(luaVM, "DuiLib")
	[
		class_<CFrameWindow, CFrameWindow_wrapper/*, boost::shared_ptr<CFrameWindow>*/ >("CFrameWindow").
		def(constructor<>()).
		//CWindowWnd函数
		def("GetHWND", &CFrameWindow::GetHWND).
		def("Create", (HWND (CFrameWindow::*)(HWND, LPCTSTR, DWORD, DWORD, int, int, int, int, HMENU))&CFrameWindow::Create).
		def("ShowWindow", &CFrameWindow::ShowWindow).
		def("ShowModal", &CFrameWindow::ShowModal).
		def("Close", &CFrameWindow::Close).
		def("CenterWindow", &CFrameWindow::CenterWindow).
		def("SendMessage", &CFrameWindow::SendMessage).
		def("PostMessage", &CFrameWindow::PostMessage).
		def("HandleMessage", &CFrameWindow::HandleMessage, &CFrameWindow_wrapper::default_HandleMessage).
		def("OnFinalMessage", &CFrameWindow::OnFinalMessage, &CFrameWindow_wrapper::default_OnFinalMessage).
		//CCustomWindow函数
		def("Init", &CFrameWindow::Init, &CFrameWindow_wrapper::default_Init).
		def("Notify", &CFrameWindow::Notify, &CFrameWindow_wrapper::default_Notify).
		def("SetInnerSkinFile", &CFrameWindow::SetInnerSkinFile).
		def("SetSkinResource", &CFrameWindow::SetSkinResource).
		def("GetManager", &CFrameWindow::GetManager, dependency(result, _1)).
		//CFrameWindow函数
		def("BringWindowToTop", &CFrameWindow::BringWindowToTop).
		def("OnDealMessage", &CFrameWindow::OnDealMessage, &CFrameWindow_wrapper::default_OnDealMessage).
		def("SetTheme", &CFrameWindow::SetTheme)
		//属性
	];

	luabind::module(luaVM)
	[
		class_<MSGSTRU_SNSUI_SETTING_THEME>("MSGSTRU_SNSUI_SETTING_THEME").
		def(constructor<>()).
		def_readwrite("dwVersion", &MSGSTRU_SNSUI_SETTING_THEME::dwVersion).
		property("szThemeName", &ThemeNameGetter, &ThemeNameSetter).
		property("szBackImage", &BackImageGetter, &BackImageSetter).
		def_readwrite("sImageSize", &MSGSTRU_SNSUI_SETTING_THEME::sImageSize).
		def_readwrite("BackImageAlign", &MSGSTRU_SNSUI_SETTING_THEME::BackImageAlign).
		def_readwrite("dwBackColor", &MSGSTRU_SNSUI_SETTING_THEME::dwBackColor).
		def_readwrite("dwTextColor", &MSGSTRU_SNSUI_SETTING_THEME::dwTextColor).
		def_readwrite("dwEditEmptyTipTextColor", &MSGSTRU_SNSUI_SETTING_THEME::dwEditEmptyTipTextColor).
		def_readwrite("dwEditEmptyTipTextColor", &MSGSTRU_SNSUI_SETTING_THEME::dwEditEmptyTipTextColor).
		def("Serialization", &MemcpyCopyStruct<MSGSTRU_SNSUI_SETTING_THEME>)
	];
	

	luabind::module(luaVM, "CreateUI")
	[
		def("CreateCListLabelElementUI", &CreateCListLabelElementUI, dependency(result, _1))
	];


	luabind::module(luaVM, "Conver")
	[
		def("ToCContainerUI", &ToCContainerUI, dependency(result, _1)),
		def("ToCComboUI", &ToCComboUI, dependency(result, _1))
	];
	
	luabind::module(luaVM)
	[
		def("BuilderCControlUI", &BuilderCControlUI, dependency(result, _3)),
		def("CompareControl", &CompareControl)
	];
}


DuiLib::CContainerUI* ToCContainerUI( DuiLib::CControlUI *pControlUI )
{
	return dynamic_cast<DuiLib::CContainerUI*>(pControlUI);
}

CListLabelElementUI* CreateCListLabelElementUI( DuiLib::CContainerUI *pContainer, int nPos )
{
	if (NULL == pContainer)
	{
		return NULL;
	}
	CListLabelElementUI *pUI = new CListLabelElementUI;
	if (-1 == nPos || nPos >= pContainer->GetCount())
	{
		pContainer->Add(pUI);
	}
	else
	{
		pContainer->AddAt(pUI, nPos);
	}
	return pUI;
}

DuiLib::CComboUI* ToCComboUI( DuiLib::CControlUI *pControlUI )
{
	return dynamic_cast<DuiLib::CComboUI*>(pControlUI);
}

DuiLib::CControlUI* BuilderCControlUI( LPCTSTR lpstrXmlFileName, LPCTSTR lpstrType, 
									  DuiLib::CFrameWindow *pFrameWindow, DuiLib::CPaintManagerUI *pManager, DuiLib::CControlUI *pParent )
{
	if (NULL == lpstrXmlFileName
		|| NULL == pManager
		|| NULL == pParent)
	{
		return NULL;
	}
	CDialogBuilder builder;
	return builder.Create(lpstrXmlFileName, lpstrType, static_cast<IDialogBuilderCallback*>(pFrameWindow), pManager, pParent);
}

BOOL CompareControl( DuiLib::CControlUI *pControlLeft, DuiLib::CControlUI *pControlRight )
{
	return (pControlLeft == pControlRight);
}

}