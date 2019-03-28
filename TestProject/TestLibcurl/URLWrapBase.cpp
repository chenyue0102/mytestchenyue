#include "URLWrapBase.h"
#include <assert.h>
#include <sys/stat.h>
#include "curl.h"

#define CONNECT_TIMEOUT_SECOND 5

CURLWrapBase::CURLWrapBase()
	: m_mutex()
	, m_thread()
	, m_cv()
	, m_bExit()
	, m_requestInfoArray()
{

}


CURLWrapBase::~CURLWrapBase()
{
}

void CURLWrapBase::init()
{
	//call curl_global_init(CURL_GLOBAL_ALL) first
	destroy();

	std::lock_guard<std::mutex> lk(m_mutex);
	m_bExit = false;
	m_thread = std::thread(&CURLWrapBase::threadProc, this);
}

void CURLWrapBase::destroy()
{
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = true;
		m_cv.notify_all();
	}
	if (m_thread.joinable())
	{
		m_thread.join();
	}
	std::lock_guard<std::mutex> lk(m_mutex);
	m_bExit = false;
	m_requestInfoArray.clear();
}

bool CURLWrapBase::downloadFile(const std::string & strUrl, const std::string & strFileName, USER_KEY userKey)
{
	bool bRet = false;

	do
	{
		if (strUrl.empty()
			|| strFileName.empty())
		{
			assert(false);
			break;
		}
		RequestInfo info;
		info.type = EnumRequestDownload;
		info.strUrl = strUrl;
		info.strFileName = strFileName;
		info.userKey = userKey;

		std::lock_guard<std::mutex> lk(m_mutex);
		m_requestInfoArray.push_back(info);
		m_cv.notify_one();

		bRet = true;
	} while (false);
	return bRet;
}

bool CURLWrapBase::getData(const std::string & strUrl, USER_KEY userKey)
{
	bool bRet = false;

	do
	{
		if (strUrl.empty())
		{
			assert(false);
			break;
		}
		RequestInfo info;
		info.type = EnumRequestGetData;
		info.strUrl = strUrl;
		info.userKey = userKey;

		std::lock_guard<std::mutex> lk(m_mutex);
		m_requestInfoArray.push_back(info);
		m_cv.notify_one();

		bRet = true;
	} while (false);
	return bRet;
}

bool CURLWrapBase::postData(const std::string &strUrl, const std::string &strPostData, USER_KEY userKey)
{
	bool bRet = false;

	do
	{
		if (strUrl.empty())
		{
			assert(false);
			break;
		}
		RequestInfo info;
		info.type = EnumRequestPostData;
		info.strUrl = strUrl;
		info.strPostData = strPostData;
		info.userKey = userKey;

		std::lock_guard<std::mutex> lk(m_mutex);
		m_requestInfoArray.push_back(info);
		m_cv.notify_one();

		bRet = true;
	} while (false);
	return bRet;
}

void CURLWrapBase::notifyProcess(const RequestInfo & info, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{

}

void CURLWrapBase::notifyRequestResult(const RequestInfo & info, bool bResult)
{

}

void CURLWrapBase::threadProc()
{
	CURL *curl = curl_easy_init();
	if (nullptr == curl)
	{
		assert(false);
		return;
	}

	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, 
			[this]() ->bool
			{
				return m_bExit || !m_requestInfoArray.empty();
			});
		if (m_bExit)
		{
			break;
		}
		if (m_requestInfoArray.empty())
		{
			continue;
		}
		RequestInfo info = m_requestInfoArray.front();
		m_requestInfoArray.pop_front();
		lk.unlock();

		bool bResult = processRequest(curl, info);
		notifyRequestResult(info, bResult);
	}
	curl_easy_cleanup(curl);
	curl = nullptr;
}

bool CURLWrapBase::processRequest(CURL * curl, RequestInfo &info)
{
	bool bRet = false;
	CURLcode ret = CURLE_OK;
	InnerRequestInfo innerInfo;

	do
	{
		innerInfo.pRefInfo = &info;
		innerInfo.pThis = this;

		struct stat st = { 0 };
		if (info.type == EnumRequestDownload)
		{
			stat(info.strFileName.c_str(), &st);
#pragma warning(push)
#pragma warning(disable:4996)
			innerInfo.fp = fopen(info.strFileName.c_str(), "ab+");
#pragma warning(pop)
		}
		else if (EnumRequestGetData == info.type)
		{
			//do nothing
		}
		else
		{
			assert(false);
		}
		
		curl_easy_reset(curl);
#ifdef _DEBUG
		if ((ret = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		
#endif
		if (EnumRequestPostData == info.type)
		{
			if ((ret = curl_easy_setopt(curl, CURLOPT_POST, 1)) != CURLE_OK)
			{
				assert(false);
				break;
			}
			//要保证发送的缓冲区在传输时有效，除非设置CURLOPT_COPYPOSTFIELDS
			if ((ret = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, info.strPostData.c_str())) != CURLE_OK)
			{
				assert(false);
				break;
			}
			//enable the cookie engine without reading any initial cookies
			if ((ret = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "")) != CURLE_OK)
			{
				assert(false);
				break;
			}
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, CONNECT_TIMEOUT_SECOND)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_URL, info.strUrl.c_str())) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CURLWrapBase::write_callback)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &innerInfo)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, &CURLWrapBase::xferinfo)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &innerInfo)) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if ((ret = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0")) != CURLE_OK)
		{
			assert(false);
			break;
		}
		if (EnumRequestDownload == info.type)
		{
			if (0 != st.st_size)
			{
				std::string strRange = std::to_string(st.st_size);
				strRange += "-";
				if ((ret = curl_easy_setopt(curl, CURLOPT_RANGE, strRange.c_str())) != CURLE_OK)
				{
					assert(false);
					break;
				}
			}
		}

		if ((ret = curl_easy_perform(curl)) != CURLE_OK)
		{
			break;
		}
		
		bRet = true;
	} while (false);

	if (nullptr != innerInfo.fp)
	{
		fclose(innerInfo.fp);
		innerInfo.fp = nullptr;
	}

	return bRet;
}

size_t CURLWrapBase::write_callback(char * ptr, size_t size, size_t nmemb, void * userdata)
{
	InnerRequestInfo *pInfo = reinterpret_cast<InnerRequestInfo*>(userdata);
	if (nullptr == pInfo
		|| nullptr == pInfo->pThis
		|| nullptr == pInfo->pRefInfo)
	{
		assert(false);
		return 0;
	}
	if (EnumRequestDownload == pInfo->pRefInfo->type
		&& pInfo->fp == nullptr)
	{
		assert(false);
		return 0;
	}
	
	{
		std::lock_guard<std::mutex> lk(pInfo->pThis->m_mutex);
		if (pInfo->pThis->m_bExit)
		{
			return 0;
		}
	}
	switch (pInfo->pRefInfo->type)
	{
		case EnumRequestDownload:
		{
			fwrite(ptr, 1, size * nmemb, pInfo->fp);
			break;
		}
		case EnumRequestGetData:
		{
			pInfo->pRefInfo->strResultData.append(ptr, size * nmemb);
			break;
		}
		default:
		{
			assert(false);
			return 0;
			break;
		}
	}
	
	return size * nmemb;
}

int CURLWrapBase::xferinfo(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	InnerRequestInfo *pInfo = reinterpret_cast<InnerRequestInfo*>(p);
	if (nullptr == pInfo
		|| nullptr == pInfo->pThis
		|| nullptr == pInfo->pRefInfo)
	{
		assert(false);
		return 0;
	}
	if (EnumRequestDownload == pInfo->pRefInfo->type
		&& pInfo->fp == nullptr)
	{
		assert(false);
		return 0;
	}
	pInfo->pThis->notifyProcess(*(pInfo->pRefInfo), dltotal, dlnow, ultotal, ulnow);
	return 0;
}
