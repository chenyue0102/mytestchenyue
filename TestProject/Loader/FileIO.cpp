#include "FileIO.h"
#include <assert.h>
#include "CodeConvert.h"

#define MAX_FILE_SIZE (1024 * 1024 * 10)		//10M
namespace FileIO
{
bool readFile(const std::string & strFilePath, DataBuffer &data)
{
	return readFile(CodeConvert::utf8_to_wstr(strFilePath), data);
}

bool readFile(const std::wstring & strFilePath, DataBuffer & data)
{
	bool bRet = false;

	do
	{
		FILE *f = _wfopen(strFilePath.c_str(), L"rb");
		if (nullptr == f)
		{
			assert(false);
			break;
		}
		if (fseek(f, 0, SEEK_END) != 0)
		{
			assert(false);
			break;
		}
		long long llSize = _ftelli64(f);
		if (llSize > MAX_FILE_SIZE)
		{
			assert(false);
			break;
		}
		if (fseek(f, 0, SEEK_SET) != 0)
		{
			assert(false);
			break;
		}
		data.resize(static_cast<size_t>(llSize));
		if (fread(&data[0], 1, llSize, f) != llSize)
		{
			assert(false);
			break;
		}
		if (fclose(f) != 0)
		{
			assert(false);
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}
}
