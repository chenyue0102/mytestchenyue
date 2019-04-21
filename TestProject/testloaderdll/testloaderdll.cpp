// testloaderdll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "testloaderdll.h"


// ���ǵ���������һ��ʾ��
TESTLOADERDLL_API int ntestloaderdll=0;

// ���ǵ���������һ��ʾ����
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

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� testloaderdll.h
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
