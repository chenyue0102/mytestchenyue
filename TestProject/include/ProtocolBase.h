#ifndef _PROTOCOLBASE_H_
#define _PROTOCOLBASE_H_


struct MSGHEADERNET
{
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwMsgLen;		//不包含包头
};
struct MSGHEADERLOCAL
{
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwMsgLen;		//不包含包头
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

#endif