#pragma once
#include "ClientSocket.h"
class MyClientSocket :
	public ClientSocket
{
public:
	MyClientSocket();
	virtual ~MyClientSocket();
protected:
	virtual int getOnePacketLength(const char *pBuf, int nBufLen)override;
	virtual void onConnect(bool bConnect)override;
	virtual void onClose()override;
	virtual void onRecv(const char *pBuf, int nLen)override;
};

