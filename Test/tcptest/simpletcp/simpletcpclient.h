#ifndef _simpletcpclient_h_
#define _simpletcpclient_h_
#include <stdint.h>
#include "simpletcpheader.h"
/*
简单tcp客户端
*/
class SimpleTcpClient {
public:
	struct ITcpCallback {
		//连接关闭
		virtual void onClose() = 0;
		//连接结果回馈
		virtual void onConnect(bool success) = 0;
		virtual void onRecv(void *data, uint32_t len) = 0;
	};
public:
	SimpleTcpClient();
	~SimpleTcpClient();

public:
	//需要保证在SimpleTcpClient生命周期有效
	void setCallback(ITcpCallback *callback);
    void connectServer(const char *ip, uint16_t port);
	void setSocket(SOCKET s, const sockaddr_in &addr);
    void closeSocket();
    uint32_t sendData(const void*data, uint32_t size);

private:
	void startThread();
	void stopThread();

private:
    static void* threadProc(void *arg);
	void innerThreadProc();

private:
	struct SimpleTcpClientData;
	SimpleTcpClientData *mData;
};

#endif
