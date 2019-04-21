// testloader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "LoaderExport.h"
#include "LoaderInterface.h"

#ifdef _DEBUG
#pragma comment(lib, "LoaderD.lib")
#else
#pragma comment(lib, "Loader.lib")
#endif

std::string getAppDir()
{
	char szPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(nullptr, szPath, _countof(szPath) - 1);
	char *p = strrchr(szPath, '\\');
	if (p != nullptr)
	{
		*p = '\0';
	}
	return szPath;
}
// {660FEA6F-E753-4934-BFFC-DFCB2B75FC28}
static const GUID iid =
{ 0x660fea6f, 0xe753, 0x4934,{ 0xbf, 0xfc, 0xdf, 0xcb, 0x2b, 0x75, 0xfc, 0x28 } };

int main()
{
	ILoader *pLoader = CreateLoader();
	std::string fileName = getAppDir() + u8"\\loader.json";
	pLoader->Init(fileName.c_str());
	const wchar_t *pguid = L"{680111D4-B97D-404B-BE49-0FBAECC83B2F}";
	GUID guid = { 0 };
	CLSIDFromString(pguid, &guid);
	pLoader->LoadPlugin(guid);

	IUnknown *punknown = nullptr;
	pLoader->QueryPluginInterface(guid, iid, (void**)&punknown);

	pLoader->FreePlugin(guid);
	pLoader->LoadPlugin(guid);

	pLoader->Destroy();
	DestroyLoader(pLoader);
    return 0;
}

