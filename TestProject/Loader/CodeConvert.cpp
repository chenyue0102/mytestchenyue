#include "CodeConvert.h"
#include <codecvt>


namespace CodeConvert
{

std::wstring utf8_to_wstr(const std::string & str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8_wstr_cvt;
	return utf8_wstr_cvt.from_bytes(str);
}
}
