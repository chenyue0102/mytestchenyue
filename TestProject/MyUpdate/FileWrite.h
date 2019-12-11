#pragma once
#include <mutex>
#include <vector>

struct FileRange
{
	long long offset;	//起始偏移，默认0
	long long size;		//大小

	FileRange()
		: offset()
		, size()
	{}
};
typedef std::vector<FileRange> FileRangeArray;
class FileWrite
{
public:
	FileWrite();
	~FileWrite();
public:
	bool open(const std::wstring &fileName, const std::wstring &mode);
	bool setNotGetFileRange(const FileRangeArray &ranges);
	bool getNotGetFileRange(FileRangeArray &ranges)const;
	bool close();
	bool write(void *buffer, long long offset, long long length);
	bool flush();
	long long getNotGetFileSize();
private:
	bool innerCalcRanges(long long offset, long long length);
private:
	mutable std::mutex m_mtx;
	FILE *m_f;
	FileRangeArray m_ranges;
};

