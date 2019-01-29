#ifndef _PROTOCOLBASE_H_
#define _PROTOCOLBASE_H_
#include "typedef.h"

#ifdef WINVER
#include <Winsock2.h>
#else
#include <arpa/inet.h> 
#endif

struct MSGHEADERNET
{
	DWORD dwMsgLen;		//包含包头
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwParam;
};
struct MSGHEADERLOCAL
{
	DWORD dwMsgLen;		//包含包头
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwParam;
};
inline MSGHEADERLOCAL Net2Local(const MSGHEADERNET &net)
{
	MSGHEADERLOCAL local = { 0 };
	local.dwMsgLen = ntohl(net.dwMsgLen);
	local.dwMsgID = ntohl(net.dwMsgID);
	local.dwObjectTye = ntohl(net.dwObjectTye);
	local.dwParam = ntohl(net.dwParam);
	return local;
}
inline MSGHEADERNET Local2Net(const MSGHEADERLOCAL &local)
{
	MSGHEADERNET net = { 0 };
	net.dwMsgLen = htonl(local.dwMsgLen);
	net.dwMsgID = htonl(local.dwMsgID);
	net.dwObjectTye = htonl(local.dwObjectTye);
	net.dwParam = htonl(local.dwParam);
	return net;
}

#endif