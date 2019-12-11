/*
不支持多线程调用
*/
#pragma once
#include <mutex>
#include <thread>
#include <string>
#include <atomic>
#include "FileWrite.h"
#include "URLWrap.h"


struct IFileDownloadCallback
{
	virtual void progressCallback(long long now, long long total, void *userdata) = 0;
};
class FileDownload : public ICURLDownloadCallback
{
public:
	FileDownload();
	~FileDownload();
public:
	void setCallback(IFileDownloadCallback *callback, void *userdata);
	void setUrl(const std::string &url);
	void setFilePathName(const std::wstring &fileName);
	void setRanges(const FileRangeArray &ranges);
	bool perform(std::atomic<bool> &bExit);
private:
	virtual bool writeCallBack(char * ptr, size_t size, void *userdata)override;
	virtual void progressCallback(long long cur, long long total, void *userdata)override;
private:
	FileWrite m_fileWrite;
	std::string m_url;
	std::wstring m_fileName;
	IFileDownloadCallback *m_callback;
	FileRangeArray m_ranges;
	void *m_userdata;
	long long m_totalSize;
};

