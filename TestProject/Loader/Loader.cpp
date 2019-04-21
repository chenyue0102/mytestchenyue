#include "Loader.h"
#include <assert.h>
#include <algorithm>
#include <Objbase.h>
#include "FileIO.h"
#include "CodeConvert.h"
#include "json/reader.h"

static const unsigned char utf8BOM[] = { 0xEF,0xBB,0xBF };


Loader::Loader()
	: m_mutex()
	, m_strAppPath()
	, m_pluginInfos()
{
}


Loader::~Loader()
{
}

HRESULT Loader::Init(const char * configFile)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == configFile)
		{
			assert(false);
			break;
		}
		std::wstring strConfigFile(CodeConvert::utf8_to_wstr(configFile));
		DataBuffer data;
		if (!FileIO::readFile(strConfigFile, data))
		{
			assert(false);
			break;
		}
		const char *begin = data.c_str();
		size_t len = data.size();
		if (len >= sizeof(utf8BOM))
		{
			if (0 == memcmp(utf8BOM, begin, sizeof(utf8BOM)))
			{
				begin += sizeof(utf8BOM);
				len -= sizeof(utf8BOM);
			}
		}
		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(begin, begin + len, root))
		{
			assert(false);
			break;
		}
		if (!root.isArray())
		{
			assert(false);
			break;
		}

		auto iter = std::find_if(strConfigFile.rbegin(), strConfigFile.rend(), 
									[](const wchar_t c)->bool {return c == L'\\' || c == L'/'; });
		if (iter == strConfigFile.rend())
		{
			assert(false);
			break;
		}
		strConfigFile.erase(++(++iter).base(), strConfigFile.end());
		
		for (auto &itemNode : root)
		{
			LoaderPluginInfo info;
			if (!innerParsePluginInfo(strConfigFile, itemNode, info))
			{
				assert(false);
				break;
			}
			m_pluginInfos.insert(std::make_pair(info.pluginGuid, info));
		}
		hr = S_OK;
	} while (false);

	return hr;
}

HRESULT Loader::Destroy()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	for (auto &info : m_pluginInfos)
	{
		innnerDestroy(info.second.pluginGuid);
	}
	return S_OK;
}

HRESULT Loader::LoadPlugin(REFGUID pluginId)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	std::vector<PluginDllInfo> dllInfos;
	HRESULT hr = E_FAIL;
	do
	{
		auto iter = m_pluginInfos.find(pluginId);
		if (iter == m_pluginInfos.end())
		{
			assert(false);
			break;
		}
		if (nullptr != iter->second.dllInfo.module)
		{
			assert(false);
			break;
		}
		//获取加载dll的加载顺序
		std::vector<GUID> loadPlugins;
		if (!innerGetLoadOrder(iter->first, loadPlugins))
		{
			assert(false);
			break;
		}

		bool bError = false;
		//顺序加载dll，获得插件接口
		for (auto &guid : loadPlugins)
		{
			PluginDllInfo dllInfo;
			if (!innerLoadPlugin(guid, dllInfo))
			{
				bError = true;
				assert(false);
				break;
			}
			dllInfos.push_back(dllInfo);
		}

		//依次执行Init
		for (auto &dllInfo : dllInfos)
		{
			auto iterCur = m_pluginInfos.find(dllInfo.pluginGuid);
			if (iterCur == m_pluginInfos.end())
			{
				bError = true;
				assert(false);
				break;
			}
			auto &findPlugin = iterCur->second;
			if (nullptr != findPlugin.dllInfo.module)
			{
				bError = true;
				assert(false);
				break;
			}

			lk.unlock();
			if (FAILED(dllInfo.plugin->Init(this)))
			{
				lk.lock();
				bError = true;
				assert(false);
				break;
			}
			lk.lock();

			findPlugin.dllInfo.module = dllInfo.module;
			findPlugin.dllInfo.plugin = dllInfo.plugin;
		}

		if (bError)
		{
			assert(false);
			break;
		}

		hr = S_OK;
	} while (false);
	
	if (FAILED(hr))
	{
		for (auto riter = dllInfos.rbegin(); riter != dllInfos.rend(); ++riter)
		{
			auto &dllInfo = *riter;
			auto iterCache = m_pluginInfos.find(dllInfo.pluginGuid);
			if (iterCache != m_pluginInfos.end())
			{
				iterCache->second.dllInfo.module = nullptr;
				iterCache->second.dllInfo.plugin = nullptr;
			}

			lk.unlock();
			if (nullptr != dllInfo.plugin)
			{
				dllInfo.plugin->Destroy();
			}
			if (nullptr != dllInfo.module)
			{
				FreeLibrary(dllInfo.module);
			}
			lk.lock();
		}
	}
	return hr;
}

HRESULT Loader::FreePlugin(REFGUID pluginId)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	HRESULT hr = E_FAIL;

	do
	{
		auto iter = m_pluginInfos.find(pluginId);
		if (iter == m_pluginInfos.end())
		{
			assert(false);
			break;
		}
		auto &dllInfo = iter->second.dllInfo;
		if (nullptr == dllInfo.module)
		{
			assert(false);
		}
		HMODULE module = dllInfo.module;
		IPlugin *plugin = dllInfo.plugin;
		dllInfo.module = nullptr;
		dllInfo.plugin = nullptr;

		lk.unlock();
		if (nullptr != plugin)
		{
			plugin->Destroy();
		}
		FreeLibrary(module);
		
		hr = S_OK;
	} while (false);
	return hr;
}

HRESULT Loader::QueryPluginInterface(REFCLSID PlugidId, REFIID iid, void ** ppvObject)
{
	std::unique_lock<std::mutex> lk(m_mutex);
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == ppvObject)
		{
			assert(false);
		}
		auto iter = m_pluginInfos.find(PlugidId);
		if (iter == m_pluginInfos.end())
		{
			assert(false);
			break;
		}
		auto &dllInfo = iter->second.dllInfo;
		if (nullptr == dllInfo.plugin)
		{
			lk.unlock();
			if (FAILED(LoadPlugin(PlugidId)))
			{
				assert(false);
				break;
			}
			lk.lock();
		}
		if (nullptr == dllInfo.plugin)
		{
			assert(false);
			break;
		}
		if (FAILED(hr = dllInfo.plugin->QueryPluginInterface(iid, ppvObject)))
		{
			assert(false);
			break;
		}
		hr = S_OK;
	} while (false);
	return hr;
}

bool Loader::innerParsePluginInfo(const std::wstring &strDir, const Json::Value &value, LoaderPluginInfo &info)
{
	bool bRet = false;

	do
	{
		if (!value.isObject())
		{
			assert(false);
			break;
		}
		const Json::Value &fileName = value["fileName"];
		if (!fileName.isString())
		{
			assert(false);
			break;
		}
		info.fileName = strDir + CodeConvert::utf8_to_wstr(fileName.asString());

		const Json::Value &pluginGuid = value["pluginGuid"];
		if (!pluginGuid.isString())
		{
			assert(false);
			break;
		}
		GUID guid = { 0 };
		std::wstring wguid = CodeConvert::utf8_to_wstr(pluginGuid.asString());
		if (CLSIDFromString(wguid.c_str(), &info.pluginGuid) != NOERROR)
		{
			assert(false);
			break;
		}
		const Json::Value &lazyLoad = value["lazyLoad"];
		if (lazyLoad.isBool())
		{
			info.lazyLoad = lazyLoad.asBool();
		}

		const Json::Value &dependentPluginGuids = value["dependentPluginGuids"];
		if (dependentPluginGuids.isArray())
		{
			for (auto &itemNode : dependentPluginGuids)
			{
				if (!itemNode.isString())
				{
					assert(false);
					break;
				}
				std::wstring tempString = CodeConvert::utf8_to_wstr(itemNode.asString());
				GUID tempGuid = { 0 };
				if (CLSIDFromString(tempString.c_str(), &tempGuid) != NOERROR)
				{
					assert(false);
					break;
				}
				info.dependentPluginGuids.push_back(tempGuid);
			}
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool Loader::innerGetLoadOrder(REFGUID pluginId, std::vector<GUID> &loadPlugins)
{
	auto iter = m_pluginInfos.find(pluginId);
	if (iter == m_pluginInfos.end())
	{
		assert(false);
		return false;
	}
	auto &pluginInfo = iter->second;
	assert(nullptr == pluginInfo.dllInfo.module);

	for (auto &dependent : pluginInfo.dependentPluginGuids)
	{
		auto iterDependent = m_pluginInfos.find(dependent);
		if (iterDependent == m_pluginInfos.end())
		{
			assert(false);
			return false;
		}
		auto &findPlugin = iterDependent->second;
		//已经加载
		if (nullptr != findPlugin.dllInfo.module)
		{
			continue;
		}
		//已经在加载队列中
		if (loadPlugins.end() != std::find_if(loadPlugins.begin(), loadPlugins.end(), GUIDEqual(findPlugin.pluginGuid)))
		{
			continue;
		}
		if (!innerGetLoadOrder(findPlugin.pluginGuid, loadPlugins))
		{
			assert(false);
			return false;
		}
	}
	if (loadPlugins.end() == std::find_if(loadPlugins.begin(), loadPlugins.end(), GUIDEqual(pluginId)))
	{
		loadPlugins.push_back(pluginId);
		return true;
	}
	else
	{
		//循环依赖
		assert(false);
		return false;
	}
}

bool Loader::innerLoadPlugin(REFGUID pluginId, PluginDllInfo & dllInfo)
{
	bool bRet = false;
	HMODULE module = nullptr;
	IPlugin *plugin = nullptr;
	do
	{
		auto iter = m_pluginInfos.find(pluginId);
		if (iter == m_pluginInfos.end())
		{
			assert(false);
			break;
		}
		if ((module = LoadLibraryW(iter->second.fileName.c_str())) == nullptr)
		{
			assert(false);
			break;
		}
		CREATEPLUGININTERFACE CreatePluginInterface = (CREATEPLUGININTERFACE)GetProcAddress(module, "CreatePluginInterface");
		if (nullptr == CreatePluginInterface)
		{
			assert(false);
			break;
		}
		CreatePluginInterface(&plugin);
		if (nullptr == plugin)
		{
			assert(false);
			break;
		}
		dllInfo.module = module;
		dllInfo.plugin = plugin;
		dllInfo.pluginGuid = pluginId;
		bRet = true;
	} while (false);

	if (!bRet
		&& nullptr != module)
	{
		FreeLibrary(module);
		module = nullptr;
	}
	return bRet;
}

void Loader::innnerDestroy(REFGUID pluginId)
{
	do
	{
		auto iter = m_pluginInfos.find(pluginId);
		if (iter == m_pluginInfos.end())
		{
			assert(false);
			break;
		}
		auto &info = iter->second;
		if (nullptr == info.dllInfo.module)
		{
			break;
		}

		auto &dependentPluginGuids = info.dependentPluginGuids;
		for (auto &guid : info.dependentPluginGuids)
		{
			innnerDestroy(guid);
		}
		auto &dllInfo = info.dllInfo;
		if (nullptr != dllInfo.plugin)
		{
			dllInfo.plugin->Destroy();
			dllInfo.plugin->Release();
			dllInfo.plugin = nullptr;
		}
		if (nullptr != dllInfo.module)
		{
			FreeLibrary(dllInfo.module);
			dllInfo.module = nullptr;
		}
	} while (false);
}
