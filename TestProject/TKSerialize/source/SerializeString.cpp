#include "SerializeString.h"
#include <string>


namespace SerializeExport
{

struct SerializeStringData
{
	std::string m_strData;
};
CSerializeString::CSerializeString()
	: m_pSerializeStringData(new SerializeStringData)
{
}


CSerializeString::CSerializeString(const CSerializeString &other)
	: m_pSerializeStringData(new SerializeStringData)
{
	*m_pSerializeStringData = *(other.m_pSerializeStringData);
}

CSerializeString::CSerializeString(const char * copy)
	: m_pSerializeStringData(new SerializeStringData)
{
	m_pSerializeStringData->m_strData = copy;
}

CSerializeString::CSerializeString(const char * str, size_type len)
	: m_pSerializeStringData(new SerializeStringData)
{
	m_pSerializeStringData->m_strData.append(str, len);
}

CSerializeString::~CSerializeString()
{
	delete m_pSerializeStringData;
	m_pSerializeStringData = nullptr;
}

CSerializeString & CSerializeString::operator=(const char * copy)
{
	m_pSerializeStringData->m_strData = copy;
	return *this;
}

CSerializeString& CSerializeString::operator=(const CSerializeString & copy)
{
	*m_pSerializeStringData = *copy.m_pSerializeStringData;
	return *this;
}

CSerializeString& CSerializeString::operator+=(const char * suffix)
{
	m_pSerializeStringData->m_strData += suffix;
	return *this;
}

CSerializeString& CSerializeString::operator+=(char single)
{
	m_pSerializeStringData->m_strData += single;
	return *this;
}

CSerializeString& CSerializeString::operator+=(const CSerializeString & suffix)
{
	m_pSerializeStringData->m_strData += suffix.m_pSerializeStringData->m_strData;
	return *this;
}

const char * CSerializeString::c_str() const
{
	return m_pSerializeStringData->m_strData.c_str();
}

const char * CSerializeString::data() const
{
	return m_pSerializeStringData->m_strData.data();
}

CSerializeString::size_type CSerializeString::length() const
{
	return m_pSerializeStringData->m_strData.length();
}

CSerializeString::size_type CSerializeString::size() const
{
	return m_pSerializeStringData->m_strData.size();
}

bool CSerializeString::empty() const
{
	return m_pSerializeStringData->m_strData.empty();
}

CSerializeString::size_type CSerializeString::capacity() const
{
	return m_pSerializeStringData->m_strData.capacity();
}

const char& CSerializeString::at(size_type index) const
{
	return m_pSerializeStringData->m_strData.at(index);
}

char& CSerializeString::operator[](size_type index) const
{
	return m_pSerializeStringData->m_strData[index];
}

CSerializeString::size_type CSerializeString::find(char lookup) const
{
	return m_pSerializeStringData->m_strData.find(lookup, 0);
}

CSerializeString::size_type CSerializeString::find(char tofind, size_type offset) const
{
	return m_pSerializeStringData->m_strData.find(tofind, offset);
}

void CSerializeString::clear()
{
	return m_pSerializeStringData->m_strData.clear();
}

void CSerializeString::reserve(size_type cap)
{
	return m_pSerializeStringData->m_strData.reserve(cap);
}

CSerializeString & CSerializeString::assign(const char * str, size_type len)
{
	m_pSerializeStringData->m_strData.assign(str, len);
	return *this;
}

CSerializeString& CSerializeString::append(const char* str, size_type len)
{
	m_pSerializeStringData->m_strData.append(str, len);
	return *this;
}

void CSerializeString::swap(CSerializeString& other)
{
	m_pSerializeStringData->m_strData.swap(other.m_pSerializeStringData->m_strData);
}
}