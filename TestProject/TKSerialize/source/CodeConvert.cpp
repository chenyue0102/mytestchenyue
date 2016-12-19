#include "CodeConvert.h"
#include <windows.h>
#include <atlenc.h>


#define CODE_PAGE_GB18030 54936

namespace CodeConvert
{
void test()
{

}
std::wstring TranslateString(const std::string &strText, UINT CodePage/* = CP_ACP*/)
{
	std::wstring strWText;
	int nWideLength = 0;
	nWideLength = MultiByteToWideChar(CodePage, 0, strText.c_str(), static_cast<int>(strText.length()), NULL, 0);
	if (0 != nWideLength)
	{
		strWText.resize(nWideLength, L'\0');
		MultiByteToWideChar(CodePage, 0, strText.c_str(), static_cast<int>(strText.length()), &*strWText.begin(), nWideLength);
	}
	return strWText;
}

std::string TranslateString(const std::wstring &strWText, UINT CodePage/* = CP_ACP*/)
{
	std::string strText;
	int nLength = 0;
	nLength = WideCharToMultiByte(CodePage, 0, strWText.c_str(), static_cast<int>(strWText.length()), NULL, 0, NULL, NULL);
	if (0 != nLength)
	{
		strText.resize(nLength, '\0');
		WideCharToMultiByte(CodePage, 0, strWText.c_str(), static_cast<int>(strWText.length()), &*strText.begin(), nLength, NULL, NULL);
	}
	return strText;
}

std::string GB2312ToUtf8(const std::string &strGB2312)
{
	return TranslateString(TranslateString(strGB2312, CODE_PAGE_GB18030), CP_UTF8);
}

std::string Utf8ToGB2312(const std::string &strUtf8)
{
	return TranslateString(TranslateString(strUtf8, CP_UTF8), CODE_PAGE_GB18030);
}

std::string Base64Decode(const std::string &strBase64)
{
	std::string strTemp;
	int nLength = strBase64.size() + 4;
	strTemp.resize(nLength);

	::Base64Decode(strBase64.data(), strBase64.size(), reinterpret_cast<BYTE*>(&strTemp[0]), &nLength);
	return std::string(strTemp.data(), nLength);
}

std::string Base64Encode(const std::string &strBinary)
{
	int nLength = strBinary.size() * 2 + 4;
	std::string strTemp;
	strTemp.resize(nLength);
	::Base64Encode(reinterpret_cast<const BYTE*>(strBinary.data()), strBinary.size(), &strTemp[0], &nLength);
	return std::string(strTemp.data(), nLength);
}

bool IsUtf8(const std::string &strText)
{
	auto nLength = strText.size();

	int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
	unsigned char chr = '\0';
	bool bAllAscii = true; //如果全部都是ASCII, 也可以说是UTF-8
	for (unsigned int i = 0; i < nLength; ++i)
	{
		chr = strText[i];
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
			bAllAscii = false;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
					return false;

				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx
		{
			if ((chr & 0xC0) != 0x80)
				return false;

			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则
		return false;
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8
		return true;

	return true;
}

}
