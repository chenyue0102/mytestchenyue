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
	//初始化组件
	virtual HRESULT STDMETHODCALLTYPE Init(ILoader *loader) = 0;
	//销毁组件
	virtual HRESULT STDMETHODCALLTYPE Destroy() = 0;
	//创建接口
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFIID iid, void **ppvObject) = 0;
	//是否允许卸载
	virtual HRESULT STDMETHODCALLTYPE CallUnload() = 0;
	//获取组件信息
	virtual HRESULT STDMETHODCALLTYPE GetPluginInfo(PluginInfo *pluginInfo) = 0;
	//获取依赖的组件
	virtual HRESULT STDMETHODCALLTYPE GetDependentPlugin(GUID *pluginIds, INT32 *count) = 0;
};

typedef int (*CREATEPLUGININTERFACE)(IPlugin **pp);

#endif
