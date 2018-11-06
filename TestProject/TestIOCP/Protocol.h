#pragma once
#include <WinSock2.h>
#include <wtypes.h>

struct MSGHEADERNET
{
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwMsgLen;
};
struct MSGHEADERLOCAL
{
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwMsgLen;
};
inline MSGHEADERLOCAL Net2Local(const MSGHEADERNET &net)
{
	MSGHEADERLOCAL local = { 0 };
	local.dwMsgID = ntohl(net.dwMsgID);
	local.dwObjectTye = ntohl(net.dwObjectTye);
	local.dwMsgLen = ntohl(net.dwMsgLen);
	return local;
}
inline MSGHEADERNET Local2Net(const MSGHEADERLOCAL &local)
{
	MSGHEADERNET net = { 0 };
	net.dwMsgID = htonl(local.dwMsgID);
	net.dwObjectTye = htonl(local.dwObjectTye);
	net.dwMsgLen = htonl(local.dwMsgLen);
	return net;
}