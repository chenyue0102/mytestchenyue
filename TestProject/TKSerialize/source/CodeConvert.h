#pragma once
#include <string>
namespace CodeConvert
{
void test();

std::string GB2312ToUtf8(const std::string &strGB2312);
std::string Utf8ToGB2312(const std::string &strUtf8);
std::string Base64Decode(const std::string &strBase64);
std::string Base64Encode(const std::string &strBinary);
bool IsUtf8(const std::string &strText);
};

