// TestLua.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TestLua.h"
#include "RegisterDuilib.h"
#include "TestLuaClass.h"
#include "UIlib.h"
#include "luabind/class_info.hpp"
#include "luabind/error.hpp"
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
#include <TKSnsUniversalDic.h>
#include "FrameWindow.h"
#include "LuaSerialize.h"

#define MAX_LOADSTRING 100

void LuaErrorCallbackFun(lua_State* e);
class CMyWindow;

enum 
{
	MSGID_LuaCollectGarbage = WM_USER + 5000,
	MSGID_LuaCreateWindow,
	MSGID_LuaCreateInviteDialog,
	MSGID_LuaFindAndBringWindowToTop,
	MSGID_LuaDealMessage,
	MSGID_LuaTestSerialize,
	MSGID_End,
};
class CMyWindow 
	: public DuiLib::CWindowWnd
{
public:
	CMyWindow():luaVM(NULL){}
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRet = __super::HandleMessage(uMsg, wParam, lParam);
		switch (uMsg)
		{
		case MSGID_LuaCollectGarbage:
			luabind::call_function<void>(luaVM, "LuaCollectGarbage");
			break;
		case MSGID_LuaCreateWindow:
			luabind::call_function<void>(luaVM, "LuaCreateWindow");
			break;
		case MSGID_LuaCreateInviteDialog:
			{
				TKSnsClientSnsIndex stSnsIndex;
				stSnsIndex.wSnsCID = TK_SNS_ENUM_SNSCLASS_PVT;
				stSnsIndex.wSnsTID = TK_SNS_ENUM_SNSTYPE_FRIEND;
				stSnsIndex.dwPID = 12345678;
				luabind::call_function<void>(luaVM, "LuaCreateInviteDialog", boost::ref(stSnsIndex));
			}
			break;
		case MSGID_LuaFindAndBringWindowToTop:
			{
				TKSnsClientSnsIndex stSnsIndex;
				stSnsIndex.wSnsCID = TK_SNS_ENUM_SNSCLASS_PVT;
				stSnsIndex.wSnsTID = TK_SNS_ENUM_SNSTYPE_FRIEND;
				stSnsIndex.dwPID = lParam;
				luabind::call_function<void>(luaVM, "LuaFindAndBringWindowToTop", static_cast<DWORD>(wParam), boost::ref(stSnsIndex));
			}
			break;
		case MSGID_LuaDealMessage:
			{
				DWORD dwMsgid = wParam;
				std::string strBuffer = *reinterpret_cast<std::string*>(lParam);
				luabind::call_function<void>(luaVM, "LuaDealMessage", dwMsgid, strBuffer);
			}
			break;
		case MSGID_LuaTestSerialize:
			{
				TKSnsClientSnsTimeStamp stSnsIndex;
				stSnsIndex.stSnsClientSnsIndex.wSnsCID = 1;
				stSnsIndex.stSnsClientSnsIndex.wSnsTID = 2;
				stSnsIndex.stSnsClientSnsIndex.dwPID = 123456;
				stSnsIndex.dwTimeStamp = 888888;
				CSerialization seri;
				seri.SetSerializationType(enum_Serialization_Type_Write);
				stSnsIndex.Serialization(seri);
				std::string strBuffer;
				seri.ToBuffer(strBuffer);
				luabind::call_function<void>(luaVM, "LuaTestSerialize", strBuffer);
			}
			break;
		}

		return lRet;
	}
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("CustomWindow");
	}
public:
	lua_State* luaVM;
};

CMyWindow g_pMyWindow;

unsigned int __stdcall ThreadProc(void *)
{
	//g_pMyWindow = new CMyWindow;
	g_pMyWindow.Create(NULL, "", WS_POPUP, 0);
	// 初始化GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR m_GDIPlusToken = 0;
	Gdiplus::GdiplusStartup(&m_GDIPlusToken, &gdiplusStartupInput, NULL);

	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestLuaBind.lua");

	CLuaVM luaVM;
	g_pMyWindow.luaVM = luaVM;
	luabind::set_error_callback(&LuaErrorCallbackFun);

	//Lua中可以打印变量的类型
	module(luaVM)
		[
			class_<class_info>("class_info_data")
			.def_readonly("name", &class_info::name)
			.def_readonly("methods", &class_info::methods)
			.def_readonly("attributes", &class_info::attributes),

			def("class_info", &get_class_info)/*,
			def("class_names", &get_class_names)*/
		];

	RegisterDuilib::RegisterDuiWindow(luaVM);
	RegisterTestLuaClass(luaVM);

	if( 0 != luaL_dofile(luaVM, szLuaFileName))
	{
		return 1;
	}
	luabind::call_function<void>(luaVM, "LuaInit");
	/*luabind::call_function<void>(luaVM, "LuaTestDefineClass");
	luabind::call_function<void>(luaVM, "LuaTestCopyClass");
	luabind::call_function<void>(luaVM, "LuaInit");
	DuiLib::CControlUI *p1=new DuiLib::CControlUI;
	DuiLib::CControlUI *p2 =new DuiLib::CContainerUI;
	
	luabind::call_function<void>(luaVM, "LuaTestRawEqual", p1, p2);
	luabind::call_function<void>(luaVM, "LuaMain");
	std::string strBuffer;
	TKSnsClientGetSnsTimeStampListFromServer stSnsClientGetSnsTimeStampListFromServer;
	stSnsClientGetSnsTimeStampListFromServer.stSnsClientHeader.dwMessageID = 1;
	stSnsClientGetSnsTimeStampListFromServer.stSnsClientHeader.dwMessageType = 2;
	stSnsClientGetSnsTimeStampListFromServer.stSnsClientHeader.dwProtocolVersion = 3;
	stSnsClientGetSnsTimeStampListFromServer.stSnsClientHeader.bSuccess = 4;
	stSnsClientGetSnsTimeStampListFromServer.stSnsClientHeader.dwErrorCode = 5;
	stSnsClientGetSnsTimeStampListFromServer.dwUserID = 6;
	stSnsClientGetSnsTimeStampListFromServer.wSnsCID = 7;
	for (int nIndex = 1; nIndex < 10; nIndex++)
	{
		stSnsClientGetSnsTimeStampListFromServer.SnsTypeArray.push_back(nIndex);
	}
	stSnsClientGetSnsTimeStampListFromServer.dwSnsTypeCount = stSnsClientGetSnsTimeStampListFromServer.SnsTypeArray.size();

	for (int nIndex = 100; nIndex < 120; nIndex++)
	{
		TKSnsClientSnsTimeStamp temp;
		temp.dwTimeStamp = nIndex;
		temp.stSnsClientSnsIndex.wSnsCID = nIndex + 1000;
		temp.stSnsClientSnsIndex.wSnsTID = nIndex + 10000;
		temp.stSnsClientSnsIndex.dwPID = nIndex + 100000;
		stSnsClientGetSnsTimeStampListFromServer.SnsClientSnsTimeStampArray.push_back(temp);
	}
	stSnsClientGetSnsTimeStampListFromServer.dwSnsTimeStampCount = stSnsClientGetSnsTimeStampListFromServer.SnsClientSnsTimeStampArray.size();
	CSerialization seri;
	seri.SetSerializationType(enum_Serialization_Type_Write);
	stSnsClientGetSnsTimeStampListFromServer.Serialization(seri);
	strBuffer.append(seri.GetData(), seri.GetDataLen());
	luabind::call_function<void>(luaVM, "LuaTestNetworkDeal", 1, boost::ref(strBuffer));*/

	

	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

int GetInput()
{
	int nInput = 0;
	printf("------------------------------0 exit\n");
	printf("------------------------------1 LuaCollectGarbage\n");
	printf("------------------------------2 ShowAboutDlg\n");
	printf("------------------------------3 ShowInviteDialog\n");
	printf("------------------------------4 BringWindowToTopInviteDialog\n");
	printf("------------------------------5 SetTheme\n");
	printf("------------------------------6 TestSerialize\n");
	scanf("%d", &nInput);
	return nInput;
}

void LuaErrorCallbackFun(lua_State* e)
{
	const char *pstrError = lua_tostring(e, -1);
	printf(pstrError);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, NULL, 0, NULL);
	CloseHandle(hThread);
	hThread = NULL;
	
	BOOL bContinue = TRUE;
	while(bContinue)
	{
		switch (GetInput())
		{
		case 0:
			bContinue = FALSE;
			break;
		case 1:
			g_pMyWindow.SendMessage(MSGID_LuaCollectGarbage);
			break;
		case 2:
			//for (int a = 0; a < 500; a++)
			g_pMyWindow.SendMessage(MSGID_LuaCreateWindow);
			break;
		case 3:
			g_pMyWindow.SendMessage(MSGID_LuaCreateInviteDialog);
			break;
		case 4:
			g_pMyWindow.SendMessage(MSGID_LuaFindAndBringWindowToTop,2,12345678);
			break;
		case 5:
			{
				MSGSTRU_SNSUI_SETTING_THEME theme;
				theme.dwBackColor = 0xFF0000FF;
				std::string strBuffer;
				strBuffer.append(reinterpret_cast<const char*>(&theme), sizeof(theme));
				g_pMyWindow.SendMessage(MSGID_LuaDealMessage,1,(LPARAM)&strBuffer);
			}
			break;
		case 6:
			{
				 g_pMyWindow.SendMessage(MSGID_LuaTestSerialize);
			}
			break;
		default:
			bContinue = FALSE;
			break;
		}
	}
	return 0;
}
