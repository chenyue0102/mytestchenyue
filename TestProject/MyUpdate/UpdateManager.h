#pragma once
#include <stdarg.h>
#include <string>
#include <atomic>
#include <thread>

struct SyncInfo
{
	std::string module;
	std::string url;
	std::wstring extractPath;
	std::wstring cachePath;
	std::wstring configPath;
	void *userdata = 0;
};
class UpdateManager
{
public:
	UpdateManager();
	~UpdateManager();
public:
	void setUpdateParam(int type, va_list argp);
	void startUpdate();
	void stopUpdate();
	void cancel();
private:
	std::atomic<bool> m_bExit;
	SyncInfo m_syncInfo;
	std::thread m_thd;
};

