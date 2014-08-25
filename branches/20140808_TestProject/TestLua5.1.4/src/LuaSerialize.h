#pragma once
#include <iosfwd>
#include <sstream> 
#include <wtypes.h>

class CLuaSerialize
{
public:
	CLuaSerialize();
	virtual ~CLuaSerialize();
public:
	bool SetBuffer(const std::string &strBuffer);
	bool ToBuffer(std::string &strBuffer);
public:
	bool ReadDWORD(DWORD &dwValue);
	bool WriteDWORD(DWORD dwValue);

	bool ReadWORD(WORD &wValue);
	bool WriteWORD(WORD wValue);

	bool ReadString(std::string &strValue);
	bool WriteString(const std::string &strValue);
private:
	std::stringstream m_stream;
	std::size_t			m_nReadStreamLen;
};

