// testloaderdll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "testloaderdll.h"


// 这是导出变量的一个示例
TESTLOADERDLL_API int ntestloaderdll=0;

// 这是导出函数的一个示例。
TESTLOADERDLL_API int fntestloaderdll(void)
{
    return 42;
}

int CreatePluginInterface(IPlugin ** pp)
{
	if (nullptr != pp)
	{
		Ctestloaderdll *pdll = new Ctestloaderdll;
		pdll->AddRef();
		*pp = pdll;
		return 0;
	}
	else
	{
		return -1;
	}
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 testloaderdll.h
Ctestloaderdll::Ctestloaderdll()
{
    return;
}

Ctestloaderdll::~Ctestloaderdll()
{
}

HRESULT Ctestloaderdll::Init(ILoader * loader)
{
	return S_OK;
}

HRESULT Ctestloaderdll::Destroy()
{
	return E_NOTIMPL;
}
// {660FEA6F-E753-4934-BFFC-DFCB2B75FC28}
static const GUID g_iid =
{ 0x660fea6f, 0xe753, 0x4934,{ 0xbf, 0xfc, 0xdf, 0xcb, 0x2b, 0x75, 0xfc, 0x28 } };
HRESULT Ctestloaderdll::QueryPluginInterface(REFIID iid, void ** ppvObject)
{
	if (memcmp(&g_iid, &iid, sizeof(GUID)) == 0)
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else
	{
		return E_NOTIMPL;
	}
}

HRESULT Ctestloaderdll::CallUnload()
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll::GetPluginInfo(PluginInfo * pluginInfo)
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll::GetDependentPlugin(GUID * pluginIds, INT32 * count)
{
	return E_NOTIMPL;
}
