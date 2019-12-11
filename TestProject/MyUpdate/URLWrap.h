/*
不是线程安全类，只能在一个线程调用本类函数
*/
#pragma once
#include "URLWrapBase.h"

struct ICURLDownloadCallback
{
	//true continue false stop
	virtual bool writeCallBack(char * ptr, size_t size, void *userdata) = 0;
	virtual void progressCallback(long long cur, long long total, void *userdata) = 0;
};
class CURLWrap : public CURLWrapBase
{
public:
	CURLWrap();
	virtual ~CURLWrap();
public:
	void setCallback(ICURLDownloadCallback *callback, void *userdata);
protected:
	virtual size_t writeCallback(char * ptr, size_t size, size_t nmemb)override;
	virtual int progressCallback(long long dltotal, long long dlnow, long long ultotal, long long ulnow)override;
protected:
	ICURLDownloadCallback *m_callback;
	void *m_userdata;
};

class CURLWrapData : public CURLWrapBase
{
public:
	CURLWrapData();
	virtual ~CURLWrapData();
public:
	std::string getResult();
protected:
	virtual size_t writeCallback(char * ptr, size_t size, size_t nmemb)override;
	virtual int progressCallback(long long dltotal, long long dlnow, long long ultotal, long long ulnow)override;
private:
	std::string m_data;
};
