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

int main()
{
	ILoader *pLoader = CreateLoader();
	std::string fileName = getAppDir() + u8"\\loader.json";
	pLoader->Init(fileName.c_str());
	DestroyLoader(pLoader);
    return 0;
}

