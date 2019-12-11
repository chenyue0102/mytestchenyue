#include "FileDownload.h"
#include <assert.h>
#include <minmax.h>
#include "URLWrap.h"
#include "multi.h"

extern long long getDownloadFileLength(const char *url);
FileDownload::FileDownload()
	: m_fileWrite()
	, m_url()
	, m_fileName()
	, m_callback(nullptr)
	, m_ranges()
	, m_userdata(nullptr)
	, m_totalSize()
{
}


FileDownload::~FileDownload()
{
}

void FileDownload::setCallback(IFileDownloadCallback * callback, void *userdata)
{
	m_callback = callback;
	m_userdata = userdata;
}

void FileDownload::setUrl(const std::string &url)
{
	m_url = url;
}

void FileDownload::setFilePathName(const std::wstring &fileName)
{
	m_fileName = fileName;
}

void FileDownload::setRanges(const FileRangeArray & ranges)
{
	m_ranges = ranges;
}

bool FileDownload::perform(std::atomic<bool> &bExit)
{
	bool ret = false;
	CURLM *curlm = nullptr;
	std::vector<std::shared_ptr<CURLWrap>> requestArray;

	do
	{
		if (!m_fileWrite.open(m_fileName.c_str(), L"rb+"))
		{
			//清空打开的情况下，不再续传
			m_ranges.clear();
			if (!m_fileWrite.open(m_fileName.c_str(), L"wb+"))
			{
				assert(false);
				break;
			}
		}
		if (0 == m_totalSize)
		{
			m_totalSize = getDownloadFileLength(m_url.c_str());
		}
		if (0 == m_totalSize)
		{
			assert(false);
			break;
		}
		if (m_ranges.empty())
		{
			FileRange range;
			range.offset = 0;
			range.size = m_totalSize;
			m_ranges.push_back(range);
		}
		m_fileWrite.setNotGetFileRange(m_ranges);
		

		if (nullptr == (curlm = curl_multi_init()))
		{
			assert(false);
			break;
		}
		
		for (auto &range : m_ranges)
		{
			std::shared_ptr<CURLWrap> pwrap = std::make_shared<CURLWrap>();
			pwrap->setCallback(this, &range);
			pwrap->request(m_url.c_str());
			std::string strRange = std::to_string(range.offset) + "-" + std::to_string(range.offset + range.size - 1);
			curl_easy_setopt(pwrap->getCURL(), CURLOPT_RANGE, strRange.c_str());
			curl_multi_add_handle(curlm, pwrap->getCURL());
			requestArray.push_back(pwrap);
		}

		int still_running = 0;
		int numfds = 0;
		CURLMcode mc = curl_multi_perform(curlm, &still_running);
		while (still_running
			&& !bExit)
		{
			mc = curl_multi_wait(curlm, nullptr, 0, 1000, &numfds);
			if (CURLM_OK != mc)
			{
				break;
			}
			if (!numfds)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			mc = curl_multi_perform(curlm, &still_running);
		}

		bool err = false;
		for (auto request : requestArray)
		{
			long code = 0;
			curl_easy_getinfo(request->getCURL(), CURLINFO_HTTP_CODE, &code);
			if (200 != code
				&& 206 != code)
			{
				err = true;
				break;
			}
		}
		m_fileWrite.flush();
		m_fileWrite.close();
		if (err)
		{
			break;
		}
		if (0 != m_fileWrite.getNotGetFileSize())
		{
			break;
		}
		ret = true;
	} while (false);
	
	
	if (nullptr != curlm)
	{
		curl_multi_cleanup(curlm);
		curlm = nullptr;
	}
	return ret;
}

bool FileDownload::writeCallBack(char * ptr, size_t size, void *userdata)
{
	FileRange *range = reinterpret_cast<FileRange*>(userdata);
	if (m_fileWrite.write(ptr, range->offset, size))
	{
		range->offset += size;
		range->size -= size;
		return true;
	}
	else
	{
		return false;
	}
}

void FileDownload::progressCallback(long long, long long , void *)
{
	if (m_callback)
	{
		long long notDownloadSize = m_fileWrite.getNotGetFileSize();
		m_callback->progressCallback(m_totalSize - notDownloadSize, m_totalSize, m_userdata);
	}
}
