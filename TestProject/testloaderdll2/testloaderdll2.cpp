// testloaderdll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "testloaderdll2.h"


// 这是导出变量的一个示例
TESTLOADERDLL2_API int ntestloaderdll2=0;

// 这是导出函数的一个示例。
TESTLOADERDLL2_API int fntestloaderdll2(void)
{
    return 42;
}

int CreatePluginInterface(IPlugin ** pp)
{
	if (nullptr != pp)
	{
		Ctestloaderdll2 *pdll = new Ctestloaderdll2;
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
// 有关类定义的信息，请参阅 testloaderdll2.h
Ctestloaderdll2::Ctestloaderdll2()
{
    return;
}

Ctestloaderdll2::~Ctestloaderdll2()
{
}

HRESULT Ctestloaderdll2::Init(ILoader * loader)
{
	return  S_OK;
}

HRESULT Ctestloaderdll2::Destroy()
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll2::QueryPluginInterface(REFIID iid, void ** ppvObject)
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll2::CallUnload()
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll2::GetPluginInfo(PluginInfo * pluginInfo)
{
	return E_NOTIMPL;
}

HRESULT Ctestloaderdll2::GetDependentPlugin(GUID * pluginIds, INT32 * count)
{
	return E_NOTIMPL;
}