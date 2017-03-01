#include "stdafx.h"
#include "IOCPBuffer.h"


CIOCPBuffer::CIOCPBuffer()
	: m_strData()
	, m_wsaBuf()
{
}


CIOCPBuffer::~CIOCPBuffer()
{
}

WSABUF* CIOCPBuffer::GetWSABuffer()
{
	m_wsaBuf.buf = const_cast<char*>(m_strData.data());
	m_wsaBuf.len = m_strData.size();
	return &m_wsaBuf;
}

bool CIOCPBuffer::append(const char *pData, unsigned int nLen)
{
	m_strData.append(pData, nLen);
	return true;
}

void CIOCPBuffer::resize(unsigned int nLen)
{
	m_strData.resize(nLen, '\0');
}
