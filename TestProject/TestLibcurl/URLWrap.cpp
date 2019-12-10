#include "URLWrap.h"
#include <assert.h>

#define CONNECT_TIMEOUT_SECOND 5


static size_t write_callback(char * ptr, size_t size, size_t nmemb, void * userdata)
{
	CURLWrap *pThis = reinterpret_cast<CURLWrap*>(userdata);
	if (nullptr != pThis
		&& nullptr != pThis->m_callback)
	{
		size_t length = size * nmemb;
		if (pThis->m_callback->writeCallBack(ptr, length, pThis->m_userdata))
		{
			return length;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		assert(false);
		return 0;
	}
}

static int xferinfo(void * userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	CURLWrap *pThis = reinterpret_cast<CURLWrap*>(userdata);
	if (nullptr != pThis
		&& nullptr != pThis->m_callback)
	{
		if (pThis->m_bDownload)
		{
			pThis->m_callback->progressCallback(dlnow, dltotal, pThis->m_userdata);
		}
		else
		{
			pThis->m_callback->progressCallback(ulnow, ultotal, pThis->m_userdata);
		}
	}
	else
	{
		assert(false);
	}
	return 0;
}


CURLWrap::CURLWrap()
	: m_curl(curl_easy_init())
	, m_url()
	, m_callback()
	, m_userdata()
	, m_bDownload(false)
{
	assert(nullptr != m_curl);
}


CURLWrap::~CURLWrap()
{
	curl_easy_cleanup(m_curl);
	m_curl = nullptr;
}

void CURLWrap::setCallback(ICURLDownloadCallback *callback, void *userdata)
{
	m_callback = callback;
	m_userdata = userdata;
}

bool CURLWrap::request(const char * url)
{
	bool ret = false;

	do
	{
		if (nullptr == url)
		{
			assert(false);
			break;
		}
		m_bDownload = true;
		m_url = url;
		curl_easy_reset(m_curl);
		if (!setOpt())
		{
			assert(false);
			break;
		}
		ret = true;
	} while (false);
	return ret;
}

bool CURLWrap::perform()
{
	return CURLE_OK == curl_easy_perform(m_curl);
}

void * CURLWrap::getCURL()
{
	return m_curl;
}

long long CURLWrap::getDownloadFileLength(const char * url)
{
	long long fileSize = -1;
	CURL *curl = nullptr;
	do
	{
		if (nullptr == url)
		{
			assert(false);
			break;
		}
		if (nullptr == (curl = curl_easy_init()))
		{
			assert(false);
			break;
		}
		if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, url))
		{
			assert(false);
			break;
		}
		//需要header
		if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_HEADER, 1))
		{
			assert(false);
			break;
		}
		//不需要body
		if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_NOBODY, 1))
		{
			assert(false);
			break;
		}
		if (CURLE_OK != curl_easy_perform(curl))
		{
			assert(false);
			break;
		}
		double d = 0.0;
		if (CURLE_OK != curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &d))
		{
			assert(false);
			break;
		}
		fileSize = static_cast<long long>(d);
	} while (false);
	if (nullptr != curl)
	{
		curl_easy_cleanup(curl);
		curl = nullptr;
	}
	return fileSize;
}

bool CURLWrap::setOpt()
{
	bool bRet = false;
	CURLcode ret = CURLE_OK;
	auto curl = m_curl;
	do
	{
#ifdef _DEBUG
		//启用debug日志输出
		if ((ret = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1)) != CURLE_OK)
		{
			assert(false);
			break;
		}
#endif
		//超时时间
		if ((ret = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, (long)CONNECT_TIMEOUT_SECOND)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str())) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, this)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &xferinfo)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0")) != CURLE_OK)
		{
			assert(false);
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}
