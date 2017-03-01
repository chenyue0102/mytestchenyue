#pragma once
#include "SocketContext.h"
#include <MSWSock.h>
#include <vector>
#include <map>
#include <memory>
#include <thread>
#include <mutex>

class CIOCP
{
public:
	CIOCP();
	~CIOCP();
public:
	bool Open(unsigned short usPort);
	bool Close();
	bool SendData(const void *pBuffer, unsigned int nLen);
protected:
	bool InnerSendData(SocketContext *pSocketContext, const void *pBuffer, unsigned int nLen);
protected:
	void IOCPThread();
	void OnAccept(IOReadContext *pAcceptContext, DWORD dwBytesTransfered);
	void OnRead(SocketContext *pSocketContext, IOReadContext *pReadContext, DWORD dwBytesTransfered);
	void OnWrite(SocketContext *pSocketContext, IOWriteContext *pWriteContext, DWORD dwBytesTransfered);
	void OnWriteComplete(SocketContext *pSocketContext, IOWriteContext *pWriteContext, DWORD dwBytesTransfered);
protected:
	virtual void NotifyAccept(unsigned long long ullKey, const sockaddr_in &addr);
	virtual void NotifyRead(unsigned long long ullKey, const void *pBuffer, unsigned int uiLen);;
private:
	volatile HANDLE m_hCompletionPort;
	SocketContext				m_ListenSocketContext;
	LPFN_ACCEPTEX               m_lpfnAcceptEx;                // AcceptEx 和 GetAcceptExSockaddrs 的函数指针，用于调用这两个扩展函数
	LPFN_GETACCEPTEXSOCKADDRS   m_lpfnGetAcceptExSockAddrs;
	std::vector<std::thread>	m_IOCPThreadArray;
private:
	std::map<unsigned long long, std::shared_ptr<SocketContext>> m_ConnectSocketContextArray;
	std::mutex m_mxConnectSocketContext;
};

