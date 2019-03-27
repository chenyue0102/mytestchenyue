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
		EnumRequestGetData,
	};
	struct RequestInfo
	{
		EnumRequest type;
		std::string strUrl;
		std::string strFileName;
		std::string strData;
		void *pUserData;
		RequestInfo()
			: type(EnumRequestNone)
			, strUrl()
			, strFileName()
			, strData()
			, pUserData(nullptr)
		{

		}
	};
	typedef std::list<RequestInfo> RequestInfoArray;
	struct InnerRequestInfo
	{
		RequestInfo *pRefInfo;
		CURLWrapBase *pThis;
		FILE *fp;
		InnerRequestInfo()
			: pRefInfo(nullptr)
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
public:
	bool downloadFile(const std::string &strUrl, const std::string &strFileName, void *pUserData);
	bool getData(const std::string &strUrl, void *pUserData);
protected:
	virtual void notifyProcess(const RequestInfo &info, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
	virtual void notifyRequestResult(const RequestInfo &info, bool bResult);
private:
	void threadProc();
	bool processRequest(CURL *curl, RequestInfo &info);
	static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
	static int xferinfo(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
public:
	mutable std::mutex m_mutex;
	std::thread m_thread;
	std::condition_variable m_cv;
	volatile bool m_bExit;
	RequestInfoArray m_requestInfoArray;
};

