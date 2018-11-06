#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <Winsock2.h>
#include "tsdeque.h"
#include "tsset.h"
#include "TCPContextManager.h"
#define COMPLETE_WORK_THREAD_COUNT 2



enum EnumIOOperation
{
	EnumIOOperationAccept,
	EnumIOOperationRead,
	EnumIOOperationWrite,
};

struct OVERLAPPEDPLUS
{
	WSAOVERLAPPED	m_oWsaOverlap;
	SOCKET          m_sClientSocket;
	EnumIOOperation	m_eIoOperation;
	WSABUF			m_wsaBuffer;

	OVERLAPPEDPLUS()
		: m_oWsaOverlap()
		, m_sClientSocket(INVALID_SOCKET)
		, m_eIoOperation(EnumIOOperationAccept)
		, m_wsaBuffer()
	{

	}
};

class CIOCPServer
{
public:
	CIOCPServer();
	~CIOCPServer();
public:
	bool Open(WORD wPort);
	bool Close();
public:
	bool Send(SOCKET hSocket, const char *pBuffer, unsigned int nLen);
private:
	void IOCPThread();
	void CheckSocketThread();
	void PostAccept();
	OVERLAPPEDPLUS* MallocOverlapPlus(EnumIOOperation IOOperation);
	void FreeOverlapPlus(OVERLAPPEDPLUS *pOverlapped);
	bool RemoveUserObjectLogic(CUserObject *pUserObject);

	bool InsertAcceptOverlapped(OVERLAPPEDPLUS *pOverlapped);
	bool RemoveAcceptOverlapped(OVERLAPPEDPLUS *pOverlapped);
	std::size_t GetAcceptOverlappedSize();

	bool InsertUserObject(CUserObject *pUserObject);
	bool RemoveUserObject(CUserObject *pUserObject);
	std::size_t GetUserObjectSize();
private:
	HANDLE m_hCompletionPort;
	std::vector<std::thread> m_threads;//IOCP处理线程
	
	HANDLE m_hAcceptEvent;//投递的Accept socket耗尽的情况下，触发Accept Event，继续投递Accept socket
	std::thread m_CheckSocketThread;//检查TCP连接的线程
	volatile bool m_bContinueCheckSocket;

	SOCKET m_sListenSocket;
	CUserObject m_UserObject;

	std::mutex m_OverlappedMutex;
	std::deque<OVERLAPPEDPLUS*> m_OverlappedPool;

	std::mutex m_AcceptOverlappedMutex;//Accept socket 锁
	std::set<OVERLAPPEDPLUS*> m_AcceptOverlappedSet;//Accept socket 列表

	std::mutex m_UserObjectMutex;//连接锁
	std::set<CComPtr<CUserObject>> m_UserObjectSet;

	std::mutex m_hWriteMutex;

	TCPContextManager m_TCPContextManager;
};

