// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "KSIMInstance.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		KSIM::g_KSIMInstance.init(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		KSIM::g_KSIMInstance.destroy();
		break;
	}
	return TRUE;
}

