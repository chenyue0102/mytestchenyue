#ifndef _LOADERINTERFACE_H_
#define _LOADERINTERFACE_H_

#include <UnKnwn.h>


struct ILoader : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE Init(const char *configFile) = 0;
	virtual HRESULT STDMETHODCALLTYPE Destroy() = 0;
	virtual HRESULT STDMETHODCALLTYPE LoadPlugin(REFGUID pluginId) = 0;
	virtual HRESULT STDMETHODCALLTYPE FreePlugin(REFGUID pluginId) = 0;
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFCLSID PlugidId, REFIID iid, void **ppvObject) = 0;
};

struct PluginInfo
{
	INT32 cbSize;
	DWORD dwVersion;
	GUID PluginID;
	char szPluginName[16];
	DWORD dwLevel;
};

struct IPlugin : public IUnknown
{
	//��ʼ�����
	virtual HRESULT STDMETHODCALLTYPE Init(ILoader *loader) = 0;
	//�������
	virtual HRESULT STDMETHODCALLTYPE Destroy() = 0;
	//�����ӿ�
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFIID iid, void **ppvObject) = 0;
	//�Ƿ�����ж��
	virtual HRESULT STDMETHODCALLTYPE CallUnload() = 0;
	//��ȡ�����Ϣ
	virtual HRESULT STDMETHODCALLTYPE GetPluginInfo(PluginInfo *pluginInfo) = 0;
	//��ȡ���������
	virtual HRESULT STDMETHODCALLTYPE GetDependentPlugin(GUID *pluginIds, INT32 *count) = 0;
};

typedef int (*CREATEPLUGININTERFACE)(IPlugin **pp);

#endif
