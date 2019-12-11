#include "MD5Check.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "md5.h"


std::string byte2HexString(const std::string &byteArray)
{
	std::string strResult;
	for (auto byte : byteArray)
	{
		char sztemp[8] = { 0 };
		snprintf(sztemp, _countof(sztemp) - 1, "%02x", static_cast<unsigned int>(byte) & 0x000000ff);
		strResult += sztemp;
	}
	return strResult;
}

MD5Check::MD5Check()
{
}


MD5Check::~MD5Check()
{
}

bool MD5Check::md5Check(const std::wstring &fileName, const std::string &md5, std::atomic<bool>& bExit)
{
	std::string fileMd5;
	FILE *f = _wfopen(fileName.c_str(), L"rb");
	if (nullptr != f)
	{
		unsigned char szBuffer[1024] = { 0 };
		int bufLen = _countof(szBuffer);
		std::size_t readBytes = 0;
		CryptoPP::Weak::MD5 md5;
		while ((readBytes = fread(szBuffer, 1, bufLen, f)) > 0
			&& !bExit)
		{
			md5.Update(szBuffer, readBytes);
		}
		if (!bExit)
		{
			fileMd5.resize(md5.DigestSize());
			md5.Final(reinterpret_cast<CryptoPP::byte*>(&fileMd5[0]));
		}
		fclose(f);
		f = nullptr;
		fileMd5 = byte2HexString(fileMd5);
	}
	return !fileMd5.empty() && fileMd5 == md5;
}
