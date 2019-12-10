#define _CRT_SECURE_NO_WARNINGS
#include "FileWrite.h"
#include <algorithm>
#include <codecvt>
#include <assert.h>

class FindRange
{
public:
	FindRange(long long offset, long long length)
		: m_offset(offset)
		, m_length(length)
	{

	}
	bool operator()(const FileRange &range)const
	{
		return (m_offset >= range.offset 
			&& m_offset <= (range.offset + range.size)
			&& (m_offset + m_length) <= (range.offset + range.size));
	}
private:
	long long m_offset;
	long long m_length;
};

FileWrite::FileWrite()
	: m_mtx()
	, m_f(nullptr)
{
}


FileWrite::~FileWrite()
{
}

bool FileWrite::open(const char * pFileName, const char *mode)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	bool ret = false;

	do
	{
		if (nullptr == pFileName
			|| nullptr == mode)
		{
			assert(false);
			break;
		}
		std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
		std::wstring strWchar = utf8_wstr_cvt.from_bytes(pFileName);
		std::wstring strWMode = utf8_wstr_cvt.from_bytes(mode);
		if (nullptr == (m_f = _wfopen(strWchar.c_str(), strWMode.c_str())))
		{
			break;
		}

		ret = true;
	} while (false);
	if (!ret
		&& nullptr != m_f)
	{
		fclose(m_f);
		m_f = nullptr;
	}
	return ret;
}

bool FileWrite::setNotGetFileRange(const FileRangeArray & ranges)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	m_ranges = ranges;
	return true;
}

bool FileWrite::getNotGetFileRange(FileRangeArray & ranges)const
{
	std::lock_guard<std::mutex> lk(m_mtx);
	ranges = m_ranges;
	return true;
}

bool FileWrite::close()
{
	std::lock_guard<std::mutex> lk(m_mtx);
	fclose(m_f);
	m_f = 0;
	return true;
}

bool FileWrite::write(void * buffer, long long offset, long long length)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	bool ret = false;

	do
	{
		if (nullptr == m_f)
		{
			assert(false);
			break;
		}
		if (0 != _fseeki64(m_f, offset, SEEK_SET))
		{
			assert(false);
			break;
		}
		if (static_cast<size_t>(length) != fwrite(buffer, 1, static_cast<size_t>(length), m_f))
		{
			assert(false);
			break;
		}
		if (0 != innerCalcRanges(offset, length))
		{
			assert(false);
			break;
		}
		ret = true;
	} while (false);
	return ret;
}

bool FileWrite::flush()
{
	std::lock_guard<std::mutex> lk(m_mtx);
	return 0 == fflush(m_f);
}

long long FileWrite::getNotGetFileSize()
{
	std::lock_guard<std::mutex> lk(m_mtx);
	long long size = 0;
	for (auto &range : m_ranges)
	{
		size += range.size;
	}
	return size;
}

bool FileWrite::innerCalcRanges(long long offset, long long length)
{
	bool ret = false;

	do
	{
		if (m_ranges.empty())
		{
			ret = 0;
			break;
		}
		auto iter = std::find_if(m_ranges.begin(), m_ranges.end(), FindRange(offset, length));
		if (iter == m_ranges.end())
		{
			assert(false);
			break;
		}
		//偏移相等，直接改这个节点
		if (iter->offset == offset)
		{
			iter->offset += length;
			iter->size -= length;
			if (iter->size <= 0)
			{
				m_ranges.erase(iter);
			}
			ret = 0;
			break;
		}
		//这个节点拆成2个
		FileRange newRange = FileRange();
		newRange.offset = offset + length;
		newRange.size = (iter->offset + iter->size) - newRange.offset;
		iter->size = (offset - iter->offset);
		if (iter->size <= 0)
		{
			iter = m_ranges.erase(iter);
		}
		else
		{
			++iter;
		}
		if (newRange.size > 0)
		{
			m_ranges.insert(iter, newRange);
		}
		ret = true;
	} while (false);
	return ret;
}
