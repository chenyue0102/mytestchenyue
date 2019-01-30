#ifndef _PROTOCOLBASE_H_
#define _PROTOCOLBASE_H_

#ifdef _WIN32
#include <Winsock2.h>
#include <Windows.h>
#else
#include <arpa/inet.h> 
#include "typedef.h"
#endif

struct MSGHEADER
{
	DWORD dwMsgLen;		//°üº¬°üÍ·
	DWORD dwMsgID;
	DWORD dwObjectTye;
	DWORD dwParam;
};

#define Net2Host Host2Net

inline MSGHEADER Host2Net(const MSGHEADER &local)
{
	MSGHEADER net = { 0 };
	net.dwMsgLen = htonl(local.dwMsgLen);
	net.dwMsgID = htonl(local.dwMsgID);
	net.dwObjectTye = htonl(local.dwObjectTye);
	net.dwParam = htonl(local.dwParam);
	return net;
}

#define PID_ACK 0x80000000

#define PID_GET_IPADDRESS 1
struct MSG_GET_IPADDRESS_REQ
{
	MSGHEADER header;
};

struct MSG_GET_IPADDRESS_ACK
{
	MSGHEADER header;
	char szIpAddress[16];
};

#define PID_SEND_BIG_DATA 2
struct MSG_BIG_DATA_REQ
{
	MSGHEADER header;
	char a[1024 * 100];
	char b[1024 * 100];
	char c[1024 * 100];
	char d[1024 * 100];
	char e[1024 * 100];
	char f[1024 * 100];
};

struct MSG_BIG_DATA_ACK
{
	MSGHEADER header;
};

#define PID_GET_BIG_DATA 3
struct MSG_GET_BIG_DATA_REQ
{
	MSGHEADER header;
};

struct MSG_GET_BIG_DATA_ACK
{
	MSGHEADER header;
	char a[1024 * 100];
	char b[1024 * 100];
	char c[1024 * 100];
	char d[1024 * 100];
	char e[1024 * 100];
	char f[1024 * 100];
};

#endif