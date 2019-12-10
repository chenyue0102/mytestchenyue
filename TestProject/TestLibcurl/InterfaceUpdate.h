#pragma once
#include "MyWindows.h"

struct ICURLDownloadCallback : public IUnknown
{
	//true continue false stop
	virtual bool writeCallBack(char * ptr, size_t size, void *userdata) = 0;
	virtual void progressCallback(long long cur, long long total, void *userdata) = 0;
};

struct ICURLWrap : public IUnknown
{
	virtual void setCallback(ICURLDownloadCallback *callback, void *userdata) = 0;
	virtual bool request(const char *url) = 0;
	virtual bool perform() = 0;
	virtual void* getCURL() = 0;
};

struct IFileDownloadCallback : public IUnknown
{
	virtual void progressCallback(long long now, long long total, void *userdata) = 0;
};