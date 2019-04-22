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
// {4228A16F-4A4F-48F5-B280-E44D76B391DE}
static const GUID dll2iid =
{ 0x4228a16f, 0x4a4f, 0x48f5,{ 0xb2, 0x80, 0xe4, 0x4d, 0x76, 0xb3, 0x91, 0xde } };

HRESULT Ctestloaderdll::Init(ILoader * loader)
{
	if (nullptr != loader)
	{
		GUID pluginGuid = { 0 };
		wchar_t guidString[] = L"{EB26AF74-E41D-4B9C-8FE9-ADB497CBFCBD}";
		CLSIDFromString(guidString, &pluginGuid);
		IUnknown *p = nullptr;
		loader->QueryPluginInterface(pluginGuid, dll2iid, (void**)&p);
		p->Release();
	}
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
