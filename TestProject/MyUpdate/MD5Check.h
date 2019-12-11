#pragma once
#include <atomic>
#include <string>

class MD5Check
{
public:
	MD5Check();
	~MD5Check();
public:
	bool md5Check(const std::wstring &fileName, const std::string &md5, std::atomic<bool> &bExit);
};

