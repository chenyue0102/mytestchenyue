#pragma once
#include <string>
#include <WinSock2.h>


class CIOCPBuffer
{
public:
	CIOCPBuffer();
	~CIOCPBuffer();
public:
	WSABUF* GetWSABuffer();
	bool append(const char *pData, unsigned int nLen);
	void resize(unsigned int nLen);
private:
	std::string m_strData;
	WSABUF		m_wsaBuf;
};

