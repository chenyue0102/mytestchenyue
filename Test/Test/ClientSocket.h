#pragma once
#include <mutex>
#include <thread>
#include <string>
#include <WinSock2.h>

class ClientSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();
public:
	bool open(const char *pAddress, unsigned short port);
	bool close();
	bool send(const char *pBuffer, int len);
private:
	void recvThread();
	void processThread();
protected:
	//如果接收了一个完整包,返回包长度，否则返回0
	virtual int getOnePacketLength(const char *pBuf, int nBufLen) = 0;
	virtual void onConnect(bool bConnect) = 0;
	virtual void onClose() = 0;
	virtual void onRecv(const char *pBuf, int nLen) = 0;
private:
	std::mutex m_mutex;
	SOCKET m_socket;
	sockaddr_in m_addr;
	volatile bool m_bExit;
	std::string m_recvBuffer;
	std::condition_variable m_cvProcess;
	std::thread m_recvThread;
	std::thread m_processThread;
};

