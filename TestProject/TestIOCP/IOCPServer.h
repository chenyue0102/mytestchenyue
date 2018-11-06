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
	std::vector<std::thread> m_threads;//IOCP�����߳�
	
	HANDLE m_hAcceptEvent;//Ͷ�ݵ�Accept socket�ľ�������£�����Accept Event������Ͷ��Accept socket
	std::thread m_CheckSocketThread;//���TCP���ӵ��߳�
	volatile bool m_bContinueCheckSocket;

	SOCKET m_sListenSocket;
	CUserObject m_UserObject;

	std::mutex m_OverlappedMutex;
	std::deque<OVERLAPPEDPLUS*> m_OverlappedPool;

	std::mutex m_AcceptOverlappedMutex;//Accept socket ��
	std::set<OVERLAPPEDPLUS*> m_AcceptOverlappedSet;//Accept socket �б�

	std::mutex m_UserObjectMutex;//������
	std::set<CComPtr<CUserObject>> m_UserObjectSet;

	std::mutex m_hWriteMutex;

	TCPContextManager m_TCPContextManager;
};

