#include "URLWrap.h"
#include <assert.h>

CURLWrap::CURLWrap()
	: m_callback(nullptr)
	, m_userdata(nullptr)
{

}

CURLWrap::~CURLWrap()
{
	
}

void CURLWrap::setCallback(ICURLDownloadCallback *callback, void *userdata)
{
	m_callback = callback;
	m_userdata = userdata;
}

size_t CURLWrap::writeCallback(char * ptr, size_t size, size_t nmemb)
{
	if (nullptr != m_callback)
	{
		m_callback->writeCallBack(ptr, size * nmemb, m_userdata);
		return size * nmemb;
	}
	else
	{
		return 0;
	}
}

int CURLWrap::progressCallback(long long dltotal, long long dlnow, long long ultotal, long long ulnow)
{
	if (nullptr != m_callback)
	{
		if (m_bDownload)
		{
			m_callback->progressCallback(dlnow, dltotal, m_userdata);
		}
		else
		{
			m_callback->progressCallback(ulnow, ultotal, m_userdata);
		}
		
	}
	return 0;
}

CURLWrapData::CURLWrapData()
{

}
CURLWrapData::~CURLWrapData()
{

}

std::string CURLWrapData::getResult()
{
	return m_data;
}

size_t CURLWrapData::writeCallback(char * ptr, size_t size, size_t nmemb)
{
	m_data.append(ptr, size * nmemb);
	return size *nmemb;
}

int CURLWrapData::progressCallback(long long dltotal, long long dlnow, long long ultotal, long long ulnow)
{
	return 0;
}
