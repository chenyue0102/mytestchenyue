#pragma once
#include <WinSock2.h>
#include <atlcomcli.h>
#include <set>
#include <map>
#include "UserObject.h"


class TCPContextManager
{
public:
	TCPContextManager();
	~TCPContextManager();
public:
	CUserObject* CreateContext(const char *pBuffer, DWORD dwRecvLen, SOCKET s, const sockaddr_in &adddr);
	void FreeContext(CUserObject *pUserObject);
public:
	bool OnRecvData(const char *pBuffer, DWORD dwRecvLen, CUserObject *pUserObject);
private:
	CUserObject* InnerCreateUserObject(DWORD dwObjectType);
private:
	std::mutex m_mutex;
	std::set<CComPtr<CUserObject>> m_UserObjectSet;
};

