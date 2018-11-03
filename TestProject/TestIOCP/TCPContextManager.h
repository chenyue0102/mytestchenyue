#pragma once
#include <WinSock2.h>
#include "tsset.h"

struct TCPContext
{
	SOCKET m_hSocket;
	sockaddr_in addr;

	bool CheckSocket()
	{
		return true;
	}
	TCPContext()
		: m_hSocket(INVALID_SOCKET)
		, addr()
	{

	}
};

class TCPContextManager : public TCPContext
{
public:
	TCPContextManager();
	~TCPContextManager();
public:
	TCPContext* CreateContext();
	void FreeContext(TCPContext *pTCPContext);
public:
	void OnRecvData(const char *pBuffer, DWORD dwRecvLen, TCPContext *pTCPContext);
private:
	tsset<TCPContext*> m_TCPContextSet;
};

