/*
不是线程安全类，只能在一个线程调用本类函数
*/
#pragma once
#include "curl.h"
#include <string>
#include "InterfaceUpdate.h"
#include "MyUnknownImpEx.h"
#include "MyCom.h"


class CURLWrap : public CMyUnknownImpEx<ICURLWrap>
{
	friend size_t write_callback(char * ptr, size_t size, size_t nmemb, void * userdata);
	friend int xferinfo(void *userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
public:
	CURLWrap();
	virtual ~CURLWrap();
public:
	void setCallback(ICURLDownloadCallback *callback, void *userdata);
	bool request(const char *url);
	bool perform();
	void* getCURL();
	static long long getDownloadFileLength(const char *url);
protected:
	virtual bool setOpt();
protected:
	CURL *m_curl;
	std::string m_url;
	CMyComPtr<ICURLDownloadCallback> m_callback;
	void *m_userdata;
	bool m_bDownload;
};

