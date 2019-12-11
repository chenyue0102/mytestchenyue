#pragma once
#include <string>

extern long long getDownloadFileLength(const char *url);
class CURLWrapBase
{
	friend size_t write_callback(char * ptr, size_t size, size_t nmemb, void * userdata);
	friend int xferinfo(void * userdata, long long dltotal, long long dlnow, long long ultotal, long long ulnow);
public:
	CURLWrapBase();
	virtual ~CURLWrapBase();
public:
	bool request(const char *url);
	bool perform();
	void* getCURL();
protected:
	virtual bool setOpt();
	virtual size_t writeCallback(char * ptr, size_t size, size_t nmemb) = 0;
	virtual int progressCallback(long long dltotal, long long dlnow, long long ultotal, long long ulnow) = 0;
protected:
	void *m_curl;
	std::string m_url;
	bool m_bDownload;
};

