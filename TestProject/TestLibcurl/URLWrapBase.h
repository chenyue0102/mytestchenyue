#pragma once
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string>
#include <list>
#include "curl.h"


class CURLWrapBase
{
public:
	enum EnumRequest
	{
		EnumRequestNone,
		EnumRequestDownload,
	};
	struct RequestInfo
	{
		EnumRequest type;
		std::string strUrl;
		std::string strFileName;
		RequestInfo()
			: type(EnumRequestNone)
			, strUrl()
			, strFileName()
		{

		}
	};
	typedef std::list<RequestInfo> RequestInfoArray;
	struct InnerRequestInfo
	{
		RequestInfo info;
		CURLWrapBase *pThis;
		FILE *fp;
		InnerRequestInfo()
			: info()
			, pThis(nullptr)
			, fp(nullptr)
		{

		}
	};
public:
	CURLWrapBase();
	~CURLWrapBase();
public:
	void init();
	void destroy();
	bool downloadFile(const std::string &strUrl, const std::string &strFileName);
protected:
	virtual void notifyProcess(const RequestInfo &info, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
	virtual void notifyRequestResult(const RequestInfo &info, bool bResult);
private:
	void threadProc();
	bool downloadFile(CURL *curl, const RequestInfo &info);
	static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
	static int xferinfo(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
public:
	std::mutex m_mutex;
	std::thread m_thread;
	std::condition_variable m_cv;
	volatile bool m_bExit;
	RequestInfoArray m_requestInfoArray;
};

