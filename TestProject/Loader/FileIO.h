#pragma once
#include <string>

typedef std::string  DataBuffer;
namespace FileIO
{
bool readFile(const std::string &strFilePath, DataBuffer &data);
bool readFile(const std::wstring &strFilePath, DataBuffer &data);
};

