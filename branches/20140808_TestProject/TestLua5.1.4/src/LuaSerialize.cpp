#include "LuaSerialize.h"
#include <assert.h>

#define MAX_BUFFER_SIZE		(1024 * 1024 * 10)

CLuaSerialize::CLuaSerialize()
: m_nReadStreamLen(0)
{
}


CLuaSerialize::~CLuaSerialize()
{
}

bool CLuaSerialize::SetBuffer(const std::string &strBuffer)
{
	m_nReadStreamLen = strBuffer.size();
	m_stream.str(strBuffer);
	return true;
}

bool CLuaSerialize::ToBuffer(std::string &strBuffer)
{
	strBuffer = m_stream.str();
	return true;
}

bool CLuaSerialize::ReadDWORD(DWORD &dwValue)
{
	if (m_stream.read(reinterpret_cast<char*>(&dwValue), sizeof(dwValue)).eof())
	{
		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}

bool CLuaSerialize::WriteDWORD(DWORD dwValue)
{
	m_stream.write(reinterpret_cast<const char*>(&dwValue), sizeof(dwValue));
	return true;
}

bool CLuaSerialize::ReadWORD(WORD &wValue)
{
	if (m_stream.read(reinterpret_cast<char*>(&wValue), sizeof(wValue)).eof())
	{
		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}

bool CLuaSerialize::WriteWORD(WORD wValue)
{
	m_stream.write(reinterpret_cast<const char*>(&wValue), sizeof(wValue));
	return true;
}

bool CLuaSerialize::ReadString(std::string &strValue)
{
	DWORD dwValue = 0;
	bool bSuccess = false;

	do 
	{
		if (!ReadDWORD(dwValue))
		{
			assert(false);
			break;
		}
		std::stringstream::pos_type curPos = m_stream.tellg();
		size_t nOffst = static_cast<size_t>(curPos);
		if (m_nReadStreamLen - nOffst < dwValue)
		{
			assert(false);
			break;
		}
		strValue.resize(dwValue);
		if (m_stream.read(&*strValue.begin(), strValue.size()).eof())
		{
			assert(false);
			break;
		}
		
		bSuccess = true;
	} while (FALSE);
	return bSuccess;
}

bool CLuaSerialize::WriteString(const std::string &strValue)
{
	m_stream.write(strValue.data(), strValue.length());
	return true;
}
