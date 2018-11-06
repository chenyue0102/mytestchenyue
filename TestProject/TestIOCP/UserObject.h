#pragma once
#include <list>
#include <string>
#include <mutex>
#include <atomic>
#include "Protocol.h"
#include "IUnknownEx.h"


class CUserObject : public IUnknownEx
{
public:
	CUserObject();
	virtual ~CUserObject();
public:
	void SetClientInfo(SOCKET s, const sockaddr_in &addr);
	void SetSocket(SOCKET s);
	void Close();
	SOCKET GetSocket()const;
	bool SendMsg(MSGHEADERLOCAL *pHeader);
public://给IOCPServer类调用
	bool OnRecvData(const char *pBuffer, DWORD dwDataLen);
	bool CheckSocket();
public://引用计数
	virtual ULONG AddRef(void)override;
	virtual ULONG Release(void)override;
public://子类调用
	virtual bool OnMsg(MSGHEADERLOCAL *pHeader);
	virtual void OnClose();
private:
	void InnerDoRecvMsg();
private:
	std::atomic_ulong m_ulRef;
	std::atomic<time_t> m_tLastMsgTime;
	mutable std::mutex m_mutex;
	SOCKET m_hSocket;
	sockaddr_in m_addr;
	std::list<std::string> m_MsgData;
	std::string m_tempData; //接收缓存，能够组成一个完整包后，将内容移植m_MsgData
};

