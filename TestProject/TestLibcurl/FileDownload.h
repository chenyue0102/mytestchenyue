#pragma once
#include <mutex>
#include <thread>
#include <string>
#include <atomic>
#include "FileWrite.h"
#include "URLWrap.h"
#include "MyUnknownImpEx.h"
#include "MyCom.h"

class FileDownload : public CMyUnknownImpEx<ICURLDownloadCallback>
{
public:
	FileDownload();
	~FileDownload();
public:
	void setCallback(IFileDownloadCallback *callback, void *userdata);
	void setUrl(const char *url);
	void setFilePathName(const char *fileName);
	void setRanges(const FileRangeArray &ranges);
	bool perform();
	//只有这个函数支持多线程调用
	void cancel();
private:
	virtual bool writeCallBack(char * ptr, size_t size, void *userdata)override;
	virtual void progressCallback(long long cur, long long total, void *userdata)override;
private:
	FileWrite m_fileWrite;
	std::string m_url;
	std::string m_fileName;
	CMyComPtr<IFileDownloadCallback> m_callback;
	FileRangeArray m_ranges;
	void *m_userdata;
	long long m_totalSize;
	std::atomic<bool> m_bExit;
};

