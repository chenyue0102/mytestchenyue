#ifndef _simpletcpserver_h_
#define _simpletcpserver_h_
#include <stdint.h>
#include "simpletcpheader.h"
/*
简单tcp服务器，采用select模型
*/
class SimpleTcpClient;
class SimpleTcpServer
{
public:
	struct ICallback 
	{
		virtual bool onAcceptTcpClient(SOCKET s, const sockaddr_in &addr) = 0;
	};
public:
	SimpleTcpServer();
	~SimpleTcpServer();

public:
	void setCallback(ICallback *callback);
	void setPort(uint16_t port);
	void setAddress(const sockaddr_in &addr);

public:
	void startServer();
	void stopServer();

private:
	//线程函数
    static void* threadProc(void *arg);
	void innerThreadProc();

private:
	struct SimpleTcpServerData;
	SimpleTcpServerData *mData;
};

#endif
