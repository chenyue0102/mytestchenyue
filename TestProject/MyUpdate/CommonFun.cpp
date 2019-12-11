#include "CommonFun.h"
#include <io.h>
#include <assert.h>
#include <codecvt>
#include <string>
#include <Windows.h>

#define APPNAME L"settings"
namespace CommonFun
{
int mkdirex(const std::string &dirname)
{
	return mkdirex(utf82wchar(dirname));
}

int mkdirex(const std::wstring &dirname)
{
	int ret = -1;
	do
	{
		std::wstring text(dirname);
		if (text.empty())
		{
			ret = EINVAL;
			assert(false);
			break;
		}
		auto riter = text.rbegin();
		if (*riter == L'\\' || *riter == L'/')
		{
			text.erase((++riter).base());
		}
		ret = 0;
		for (size_t i = 0; i < text.size(); i++)
		{
			if (text[i] == L'\\'
				|| text[i] == L'/')
			{
				wchar_t old = text[i];
				text[i] = '\0';
				if (0 != _waccess(text.c_str(), 0))
				{
					if (0 != (ret = _wmkdir(text.c_str())))
					{
						assert(false);
						break;
					}
				}
				text[i] = old;
			}
		}
		if (0 != ret)
		{
			break;
		}
		if (0 != _waccess(text.c_str(), 0))
		{
			if (0 != (ret = _wmkdir(text.c_str())))
			{
				assert(false);
				break;
			}
		}
		ret = 0;
	} while (false);
	return ret;
}
std::string readFileBytes(const std::string &fileName)
{
	return readFileBytes(utf82wchar(fileName));
}
std::string readFileBytes(const std::wstring &fileName)
{
	std::string bytes;
	FILE *f = nullptr;

	do
	{
		if (nullptr == (f = _wfopen(fileName.c_str(), L"r")))
		{
			break;
		}
		if (0 != fseek(f, 0, SEEK_END))
		{
			assert(false);
			break;
		}
		long size = ftell(f);
		bytes.resize(size);
		if (0 != fseek(f, 0, SEEK_SET))
		{
			assert(false);
			break;
		}
		if (size != fread(&bytes[0], 1, size, f))
		{
			assert(false);
			break;
		}
	} while (false);
	if (nullptr != f)
	{
		fclose(f);
		f = nullptr;
	}
	return bytes;
}
std::wstring utf82wchar(const std::string & utf8)
{
	std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
	return utf8_wstr_cvt.from_bytes(utf8);
}
std::string wchar2utf8(const std::wstring & wchar)
{
	std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
	return utf8_wstr_cvt.to_bytes(wchar);
}
std::string getConfigText(const std::string & filename, const std::string & propname)
{
	return wchar2utf8(getConfigText(utf82wchar(filename), utf82wchar(propname)));
}
std::wstring getConfigText(const std::wstring & filename, const std::wstring & propname)
{
	WCHAR szTemp[256] = { 0 };
	DWORD dwCount = GetPrivateProfileStringW(APPNAME, propname.c_str(), L"", szTemp, _countof(szTemp) - 1, filename.c_str());
	szTemp[dwCount] = L'\0';
	return std::wstring(szTemp);
}
void setConfigText(const std::string & filename, const std::string & propname, const std::string & value)
{
	return setConfigText(utf82wchar(filename), utf82wchar(propname), utf82wchar(value));
}
void setConfigText(const std::wstring & filename, const std::wstring & propname, const std::wstring & value)
{
	WritePrivateProfileStringW(APPNAME, propname.c_str(), value.c_str(), filename.c_str());
}
long long getFileSize(const std::wstring & filename)
{
	long long fileSize = 0;
	struct _stat64 s;
	_wstati64(filename.c_str(), &s);
	return s.st_size;
}
}
