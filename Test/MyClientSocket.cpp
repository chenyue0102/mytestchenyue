#include "stdafx.h"
#include "MyClientSocket.h"


MyClientSocket::MyClientSocket()
{
}


MyClientSocket::~MyClientSocket()
{
}

int MyClientSocket::getOnePacketLength(const char * pBuf, int nBufLen)
{
	if (nBufLen >= 4)
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

void MyClientSocket::onConnect(bool bConnect)
{
	printf("onConnect=%s\n", bConnect ? "true" : "false");
}

void MyClientSocket::onClose()
{
	printf("onClose\n");
}

void MyClientSocket::onRecv(const char * pBuf, int nLen)
{
	std::string str(pBuf, nLen);
	printf("onRecv=%s\n", str.c_str());
}
