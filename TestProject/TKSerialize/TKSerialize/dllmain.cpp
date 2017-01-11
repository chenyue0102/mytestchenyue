// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <Windows.h>
#include "TKSerializeApp.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			theApp.InitInstance();
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		{
			theApp.ExitInstance();
		}
		break;
	}
	return TRUE;
}

