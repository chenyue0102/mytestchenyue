#pragma once
#include <WinSock2.h>
#include <atlcomcli.h>
#include <set>
#include <map>
#include "UserObject.h"


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
	bool OnRecvData(const char *pBuffer, DWORD dwRecvLen, TCPContext *pTCPContext);
private:
	CUserObject* CreateUserObject(DWORD dwObjectType);
private:
	std::mutex m_mutex;
	std::set<TCPContext*> m_TCPContextSet;
	std::map<TCPContext*, CComPtr<CUserObject>> m_ContextObjectMap;
};

