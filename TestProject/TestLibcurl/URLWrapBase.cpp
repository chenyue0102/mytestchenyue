#include "URLWrapBase.h"
#include <assert.h>
#include <sys/stat.h>
#include "curl.h"


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

bool CURLWrapBase::downloadFile(const std::string & strUrl, const std::string & strFileName)
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

	std::unique_lock<std::mutex> lk(m_mutex);
	while (true)
	{
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

		bool bResult = downloadFile(curl, info);
		notifyRequestResult(info, bResult);
	}
	curl_easy_cleanup(curl);
	curl = nullptr;
}

bool CURLWrapBase::downloadFile(CURL * curl, const RequestInfo &info)
{
	bool bRet = false;
	CURLcode ret = CURLE_OK;
	InnerRequestInfo innerInfo;

	do
	{
		struct stat st = { 0 };
		stat(info.strFileName.c_str(), &st);

		
		innerInfo.info = info;
		innerInfo.pThis = this;
		innerInfo.fp = fopen(info.strFileName.c_str(), "ab+");
		
		curl_easy_reset(curl);
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
	assert(pInfo->info.type == EnumRequestDownload);
	if (nullptr == pInfo
		|| pInfo->pThis == nullptr
		|| pInfo->fp == nullptr)
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
	fwrite(ptr, 1, size * nmemb, pInfo->fp);
	return size * nmemb;
}

int CURLWrapBase::xferinfo(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	InnerRequestInfo *pInfo = reinterpret_cast<InnerRequestInfo*>(p);
	if (nullptr == pInfo
		|| pInfo->pThis == nullptr
		|| pInfo->fp == nullptr)
	{
		assert(false);
		return 0;
	}
	pInfo->pThis->notifyProcess(pInfo->info, dltotal, dlnow, ultotal, ulnow);
	return 0;
}
