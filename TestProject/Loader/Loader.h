#pragma once
#include <mutex>
#include <string>
#include <vector>
#include <map>
#include <atlcomcli.h>
#include "LoaderInterface.h"
#include "UnknownImp.h"

namespace Json
{
	class Value;
}

struct PluginDllInfo
{
	HMODULE module;
	IPlugin *plugin;
	GUID pluginGuid;

	PluginDllInfo()
		: module(nullptr)
		, plugin()
		, pluginGuid()
	{}
};

struct LoaderPluginInfo
{
	PluginDllInfo dllInfo;
	std::wstring fileName;
	GUID pluginGuid;
	bool lazyLoad;
	std::vector<GUID> dependentPluginGuids;

	LoaderPluginInfo()
		: dllInfo()
		, fileName()
		, pluginGuid()
		, lazyLoad(false)
		, dependentPluginGuids()
	{}
};
struct GUIDLess
{
	bool operator()(const GUID &left, const GUID &right)const
	{
		return memcmp(&left, &right, sizeof(GUID)) < 0;
	}
};
struct GUIDEqual
{
	GUIDEqual(const GUID &_g)
		: g(_g)
	{

	}
	bool operator()(const GUID &other)const
	{
		return memcmp(&g, &other, sizeof(GUID)) == 0;
	}
	GUID g;
};
class Loader 
	: public UnknownImp<ILoader>
{
public:
	Loader();
	virtual ~Loader();
public:
	virtual HRESULT STDMETHODCALLTYPE Init(const char *configFile)override;
	virtual HRESULT STDMETHODCALLTYPE Destroy()override;
	virtual HRESULT STDMETHODCALLTYPE LoadPlugin(REFGUID pluginId)override;
	virtual HRESULT STDMETHODCALLTYPE FreePlugin(REFGUID pluginId)override;
	virtual HRESULT STDMETHODCALLTYPE QueryPluginInterface(REFCLSID PlugidId, REFIID iid, void **ppvObject)override;
private:
	bool innerParsePluginInfo(const std::wstring &strDir, const Json::Value &value, LoaderPluginInfo &info);
	bool innerGetLoadOrder(REFGUID pluginId, std::vector<GUID> &loadPlugins);
	bool innerLoadPlugin(REFGUID pluginId, PluginDllInfo &dllInfo);
	void innnerDestroy(REFGUID pluginId);
private:
	std::mutex m_mutex;
	std::wstring m_strAppPath;
	std::map<GUID, LoaderPluginInfo, GUIDLess> m_pluginInfos;
};

