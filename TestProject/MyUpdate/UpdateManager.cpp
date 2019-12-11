#include "UpdateManager.h"
#include <assert.h>
#include "MyUpdateDefine.h"
#include "CommonFun.h"
#include "FileDownload.h"
#include "MD5Check.h"

#define GET_VALUE(value, type)\
	type t = va_arg(argp, type)	;\
	if (nullptr != t)\
	{\
		value = t;\
	}

using namespace MyUpdateExport;

struct UpdateConfig
{
	std::string version;
};

struct UpdateModule
{
	std::string module;
	std::string version;
	std::string url;
	std::string md5;
	bool md5Valid = false;
	long long fileSize = 0;
	NOTIFYRESULT notifyResult = 0;
	NOTIFYPERCENT notifyPercent = 0;
};

enum EUpdateStep
{
	EUpdateStepNone,
	EUpdateStepDownload,
};
struct UpdateStep
{
	EUpdateStep step;
	FileRangeArray ranges;
};

static void notifyPercent(long long now, long long total, SyncInfo &module)
{

}

static void notifyResult(int result, int action, SyncInfo &module, std::atomic<bool>& bExit)
{

}


static void innerSync(SyncInfo syncInfo, std::atomic<bool>& bExit)
{
	//读取本地的版本
	UpdateConfig localConfig;
#ifdef _DEBUG
	localConfig.version = "1234";
#endif
	//将版本与模块发送给服务器

	//从服务器得到差分数据信息
	UpdateModule moduleInfo;
#ifdef _DEBUG
	moduleInfo.module = syncInfo.module;
	moduleInfo.url = syncInfo.url;
	moduleInfo.version = "4567";
	moduleInfo.md5 = "d3cdd89935d2a0122839a308cad4707b";
	moduleInfo.fileSize = 1120590;
	moduleInfo.md5Valid = true;
#endif
	if (localConfig.version == moduleInfo.version)
	{
		notifyResult(EResultOK, EActionNone, syncInfo, bExit);
		return;
	}

	//下载更新包
	std::wstring downloadPath = syncInfo.cachePath + L'/' + CommonFun::utf82wchar(syncInfo.module + moduleInfo.version);
	std::wstring downloadFilePath = downloadPath + L'/' + CommonFun::utf82wchar(syncInfo.module + ".dat");
	CommonFun::mkdirex(downloadPath.c_str());

	FileDownload fileDownload;
	fileDownload.setUrl(moduleInfo.url.c_str());
	fileDownload.setFilePathName(downloadFilePath.c_str());
	//fileDownload.setCallback
	if (!fileDownload.perform(bExit))
	{
		//save step
		notifyResult(EResultDownloadFailed, EActionNone, syncInfo, bExit);
		return;
	}

	//文件大小校验
	if (0 != moduleInfo.fileSize
		&& moduleInfo.fileSize != CommonFun::getFileSize(downloadFilePath))
	{
		if (0 != _wremove(downloadFilePath.c_str()))
		{
			assert(false);
		}
		notifyResult(EResultMd5Failed, EActionNone, syncInfo, bExit);
		return;
	}

	//文件md5校验
	if (!moduleInfo.md5.empty()
		&& moduleInfo.md5Valid)
	{
		MD5Check md5Check;
		if (!md5Check.md5Check(downloadFilePath, moduleInfo.md5, bExit))
		{
			if (0 != _wremove(downloadFilePath.c_str()))
			{
				assert(false);
			}
			notifyResult(EResultMd5Failed, EActionNone, syncInfo, bExit);
			return;
		}
	}

	//解压缩

}


UpdateManager::UpdateManager()
	: m_bExit(false)
{
}


UpdateManager::~UpdateManager()
{
	stopUpdate();
}

void UpdateManager::setUpdateParam(int type, va_list argp)
{
	switch (type)
	{
	case EParamModule:
	{
		GET_VALUE(m_syncInfo.module, const char*);
		break;
	}
	case EParamURL:
	{
		GET_VALUE(m_syncInfo.url, const char*);
		break;
	}
	case EParamExtractPath:
	{
		std::string text;
		GET_VALUE(text, const char*);
		m_syncInfo.extractPath = CommonFun::utf82wchar(text);
		break;
	}
	case EParamCachePath:
	{
		std::string text;
		GET_VALUE(text, const char*);
		m_syncInfo.cachePath = CommonFun::utf82wchar(text);
		break;
	}
	case EParamConfigPath:
	{
		std::string text;
		GET_VALUE(text, const char*);
		m_syncInfo.configPath = CommonFun::utf82wchar(text);
		break;
	}
	case EParamUserData:
	{
		GET_VALUE(m_syncInfo.userdata, void*);
		break;
	}
	default:
	{
		assert(false);
		break;
	}
	}
}

void UpdateManager::startUpdate()
{
	stopUpdate();
	m_bExit = false;
	m_thd = std::thread(&innerSync, m_syncInfo, std::ref(m_bExit));
}

void UpdateManager::stopUpdate()
{
	if (m_thd.joinable())
	{
		m_bExit = true;
		m_thd.join();
		std::thread().swap(m_thd);
	}
}

void UpdateManager::cancel()
{
	m_bExit = true;
}
