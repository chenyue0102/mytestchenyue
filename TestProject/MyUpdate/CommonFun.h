#pragma once
#include <string>
namespace CommonFun
{
int mkdirex(const std::string &dirname);
int mkdirex(const std::wstring &dirname);
std::string readFileBytes(const std::string &filename);
std::string readFileBytes(const std::wstring &fileName);
std::wstring utf82wchar(const std::string &utf8);
std::string wchar2utf8(const std::wstring &wchar);
std::string getConfigText(const std::string &filename, const std::string &propname);
std::wstring getConfigText(const std::wstring &filename, const std::wstring &propname);
void setConfigText(const std::string &filename, const std::string &propname, const std::string &value);
void setConfigText(const std::wstring &filename, const std::wstring &propname, const std::wstring &value);
long long getFileSize(const std::wstring &filename);
};

