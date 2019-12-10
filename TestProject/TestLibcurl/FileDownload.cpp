#include "FileDownload.h"
#include <assert.h>
#include <minmax.h>
#include "URLWrap.h"


FileDownload::FileDownload()
	: m_fileWrite()
	, m_url()
	, m_fileName()
	, m_callback(nullptr)
	, m_ranges()
	, m_userdata(nullptr)
	, m_totalSize()
	, m_bExit(false)
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

void FileDownload::setUrl(const char * url)
{
	m_url = url;
}

void FileDownload::setFilePathName(const char * fileName)
{
	m_fileName = fileName;
}

void FileDownload::setRanges(const FileRangeArray & ranges)
{
	m_ranges = ranges;
}

bool FileDownload::perform()
{
	bool ret = false;
	CURLM *curlm = nullptr;
	std::vector<std::shared_ptr<CURLWrap>> requestArray;

	do
	{
		m_bExit = false;
		if (!m_fileWrite.open(m_fileName.c_str(), "rb+"))
		{
			//清空打开的情况下，不再续传
			m_ranges.clear();
			if (!m_fileWrite.open(m_fileName.c_str(), "wb+"))
			{
				assert(false);
				break;
			}
		}
		if (m_ranges.empty())
		{
			long long fileSize = CURLWrap::getDownloadFileLength(m_url.c_str());
			if (0 == fileSize)
			{
				assert(false);
				break;
			}
			FileRange range;
			range.offset = 0;
			range.size = fileSize;
			m_ranges.push_back(range);
		}
		m_fileWrite.setNotGetFileRange(m_ranges);
		if (0 == m_totalSize)
		{
			m_totalSize = CURLWrap::getDownloadFileLength(m_url.c_str());
		}

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
			&& !m_bExit)
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
			if (200 != code)
			{
				err = true;
				break;
			}
		}
		requestArray.clear();
		m_fileWrite.flush();
		m_fileWrite.close();
		if (err)
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

void FileDownload::cancel()
{
	m_bExit = true;
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
