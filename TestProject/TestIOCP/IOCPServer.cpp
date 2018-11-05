#include "stdafx.h"
#include "IOCPServer.h"
#include <assert.h>
#include <MSWSock.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

#define MAX_ACCEPT 6
#define MIN_ACCEPT 5
#define SEND_BUF_LEN 512
#define RECV_BUF_LEN 512
#define OVERLAPPED_POOL_SIZE 2048
#define MAX_CONTEXT_SIZE 50000
#define CONNECT_TIMEOUT_SECOND 2 //���Ӻ�û�з�������ʱ����

#define MACRO_SAFE_CLOSESOCKET(s) {if(s!= INVALID_SOCKET){closesocket(s); s=INVALID_SOCKET;}}

CIOCPServer::CIOCPServer()
	: m_hCompletionPort(INVALID_HANDLE_VALUE)
	, m_threads()
	, m_sListenSocket(INVALID_SOCKET)
	, m_TCPContext()
	, m_hAcceptEvent(nullptr)
	, m_AcceptOverlappedSet()
	, m_bContinueCheckSocket(true)
{
}


CIOCPServer::~CIOCPServer()
{
	assert(INVALID_HANDLE_VALUE != m_hCompletionPort);
}

bool CIOCPServer::Open(WORD wPort)
{
	bool bRes = false;

	do
	{
		WSADATA lwsaData;
		if (0 != WSAStartup(MAKEWORD(2, 2), &lwsaData))
		{
			assert(false);
			break;
		}


		if (INVALID_HANDLE_VALUE == (m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0)))
		{
			assert(false);
			break;
		}
		for (int nIndex = 0; nIndex < COMPLETE_WORK_THREAD_COUNT; nIndex++)
		{
			m_threads.push_back(std::thread(&CIOCPServer::IOCPThread, this));
		}


		if (INVALID_SOCKET == (m_sListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED)))
		{
			assert(false);
			break;
		}
		m_TCPContext.m_hSocket = m_sListenSocket;
		if (nullptr == CreateIoCompletionPort((HANDLE)m_sListenSocket, m_hCompletionPort, (ULONG_PTR)&m_TCPContext, 0))
		{
			assert(false);
			break;
		}


		SOCKADDR_IN addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(wPort);
		if (0 != bind(m_sListenSocket, (sockaddr*)&addr, sizeof(addr)))
		{
			assert(false);
			break;
		}
		if (0 != listen(m_sListenSocket, SOMAXCONN))
		{
			assert(false);
			break;
		}

		if (nullptr == (m_hAcceptEvent = WSACreateEvent()))
		{
			assert(false);
			break;
		}
		if (SOCKET_ERROR == WSAEventSelect(m_sListenSocket, m_hAcceptEvent, FD_ACCEPT))
		{
			assert(false);
			break;
		}

		for (int i = 0; i < MAX_ACCEPT; i++)
		{
			PostAccept();
		}
		m_bContinueCheckSocket = true;
		m_CheckSocketThread = std::thread(&CIOCPServer::CheckSocketThread, this);

		bRes = true;
	} while (false);
	
	if (!bRes)
	{
		Close();
	}
	return bRes;
}

bool CIOCPServer::Close()
{
	m_bContinueCheckSocket = false;
	if (nullptr != m_hAcceptEvent)
	{
		WSASetEvent(m_hAcceptEvent);
	}
	MACRO_SAFE_CLOSESOCKET(m_sListenSocket);

	while (GetAcceptOverlappedSize() > 0 || GetTCPContextSize() > 0)
	{
		{
			std::lock_guard<std::mutex> lk(m_AcceptOverlappedMutex);
			for (OVERLAPPEDPLUS *pOverlapped : m_AcceptOverlappedSet)
			{
				MACRO_SAFE_CLOSESOCKET(pOverlapped->m_sClientSocket);
			}
		}
		{
			std::lock_guard<std::mutex> lk(m_TCPContextMutex);
			for (TCPContext *pTCPContext : m_TCPContextSet)
			{
				MACRO_SAFE_CLOSESOCKET(pTCPContext->m_hSocket);
			}
		}
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	if (INVALID_HANDLE_VALUE != m_hCompletionPort)
	{
		for (unsigned int nIndex = 0; nIndex < m_threads.size(); nIndex++)
		{
			PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, 0);
		}
		for (auto &oneThread : m_threads)
		{
			oneThread.join();
		}
		m_threads.clear();
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = INVALID_HANDLE_VALUE;
	}
	if (m_CheckSocketThread.joinable())
	{
		m_CheckSocketThread.join();
	}
	if (nullptr != m_hAcceptEvent)
	{
		CloseHandle(m_hAcceptEvent);
		m_hAcceptEvent = nullptr;
	}

	{
		std::lock_guard<std::mutex> lk(m_OverlappedMutex);
		for (OVERLAPPEDPLUS *pOverlapped : m_OverlappedPool)
		{
			delete[] pOverlapped->m_wsaBuffer.buf;
			delete pOverlapped;
		}
		m_OverlappedPool.clear();
	}

	return true;
}

void CIOCPServer::PostAccept()
{
	bool bRes = false;

	do 
	{
		SOCKET sAcceptSocket = INVALID_SOCKET;
		OVERLAPPEDPLUS *pOverlapped = nullptr;
		if (GetAcceptOverlappedSize() >= MAX_ACCEPT)
		{
			break;
		}
		if (INVALID_SOCKET == (sAcceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED)))
		{
			assert(false);
			break;
		}
		setsockopt(sAcceptSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)&m_sListenSocket, sizeof(m_sListenSocket));
		if (nullptr == (pOverlapped = MallocOverlapPlus(EnumIOOperationAccept)))
		{
			MACRO_SAFE_CLOSESOCKET(sAcceptSocket);
			assert(false);
			break;
		}
		pOverlapped->m_sClientSocket = sAcceptSocket;
		
		if (!InsertAcceptOverlapped(pOverlapped))
		{
			delete []pOverlapped->m_wsaBuffer.buf;
			delete pOverlapped;
			pOverlapped = nullptr;
			MACRO_SAFE_CLOSESOCKET(sAcceptSocket);
			assert(false);
			break;
		}

		DWORD dwBytes = 0;
		BOOL lbSuccess = AcceptEx(m_sListenSocket,
			sAcceptSocket,
			pOverlapped->m_wsaBuffer.buf,
			pOverlapped->m_wsaBuffer.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
			sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16,
			&dwBytes,
			(LPWSAOVERLAPPED)pOverlapped);
		if (!lbSuccess && WSAGetLastError() != ERROR_IO_PENDING)
		{
			if (RemoveAcceptOverlapped(pOverlapped))
			{
				FreeOverlapPlus(pOverlapped);
				MACRO_SAFE_CLOSESOCKET(sAcceptSocket);
			}
			break;
		}

		bRes = true;
	} while (false);
}

OVERLAPPEDPLUS* CIOCPServer::MallocOverlapPlus(EnumIOOperation IOOperation)
{
	std::lock_guard<std::mutex> lk(m_OverlappedMutex);
	OVERLAPPEDPLUS *pOverlapped = nullptr;
	if (m_OverlappedPool.empty())
	{
		pOverlapped = new OVERLAPPEDPLUS();
		pOverlapped->m_wsaBuffer.buf = new char[SEND_BUF_LEN]();
		pOverlapped->m_wsaBuffer.len = SEND_BUF_LEN;
	}
	else
	{
		pOverlapped = m_OverlappedPool.front();
		m_OverlappedPool.pop_front();
	}
	if (nullptr != pOverlapped)
	{
		pOverlapped->m_sClientSocket = INVALID_SOCKET;
		pOverlapped->m_eIoOperation = IOOperation;
	}
	return pOverlapped;
}

void CIOCPServer::FreeOverlapPlus(OVERLAPPEDPLUS *pOverlapped)
{
	std::lock_guard<std::mutex> lk(m_OverlappedMutex);
	if (nullptr != pOverlapped)
	{
		if (m_OverlappedPool.size() < OVERLAPPED_POOL_SIZE)
		{
			m_OverlappedPool.push_back(pOverlapped);
		}
		else
		{
			delete []pOverlapped->m_wsaBuffer.buf;
			delete pOverlapped;
			pOverlapped = nullptr;
		}
	}
	else
	{
		assert(false);
	}
}

TCPContext* CIOCPServer::CreateContext()
{
	return m_TCPContextManager.CreateContext();
}

bool CIOCPServer::RemoveTcpContextLogic(TCPContext *pTCPContext)
{
	if (RemoveTcpContext(pTCPContext))
	{
		MACRO_SAFE_CLOSESOCKET(pTCPContext->m_hSocket);
		m_TCPContextManager.FreeContext(pTCPContext);
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

bool CIOCPServer::InsertAcceptOverlapped(OVERLAPPEDPLUS *pOverlapped)
{
	std::lock_guard<std::mutex> lk(m_AcceptOverlappedMutex);
	return m_AcceptOverlappedSet.insert(pOverlapped).second;
}

bool CIOCPServer::RemoveAcceptOverlapped(OVERLAPPEDPLUS *pOverlapped)
{
	std::lock_guard<std::mutex> lk(m_AcceptOverlappedMutex);
	return (0 != m_AcceptOverlappedSet.erase(pOverlapped));
}

std::size_t CIOCPServer::GetAcceptOverlappedSize()
{
	std::lock_guard<std::mutex> lk(m_AcceptOverlappedMutex);
	return m_AcceptOverlappedSet.size();
}

bool CIOCPServer::InsertTCPContext(TCPContext *pTCPContext)
{
	std::lock_guard<std::mutex> lk(m_TCPContextMutex);
	return m_TCPContextSet.insert(pTCPContext).second;
}

bool CIOCPServer::RemoveTcpContext(TCPContext * pTCPContext)
{
	std::lock_guard<std::mutex> lk(m_TCPContextMutex);
	return (0 != m_TCPContextSet.erase(pTCPContext));
}

std::size_t CIOCPServer::GetTCPContextSize()
{
	std::lock_guard<std::mutex> lk(m_TCPContextMutex);
	return m_TCPContextSet.size();
}

void CIOCPServer::IOCPThread()
{
	DWORD dwNumberOfBytes = 0;
	TCPContext *pTCPContext = nullptr;
	OVERLAPPEDPLUS *lpOverlapped = nullptr;
	struct sockaddr_in *lpstrLocalAddr = nullptr, *lpstrRemoteAddr = nullptr;
	int liLocalAddrLen = 0, liRemoteAddrLen = 0;
	int liRet = 0;
	ULONG ulFlags = 0;

	while (true)
	{
		pTCPContext = nullptr;
		lpOverlapped = nullptr;
		dwNumberOfBytes = 0;
		if (GetQueuedCompletionStatus(m_hCompletionPort, &dwNumberOfBytes, (PULONG_PTR)&pTCPContext, (LPOVERLAPPED*)&lpOverlapped, INFINITE))
		{
			if (nullptr == pTCPContext)
			{
				break;
			}
			switch (lpOverlapped->m_eIoOperation)
			{
			case EnumIOOperationAccept:
			{
				if (!RemoveAcceptOverlapped(lpOverlapped))
				{
					assert(false);
					continue;
				}
				if (GetAcceptOverlappedSize() < MAX_ACCEPT)
				{
					PostAccept();
				}
				if (0 == dwNumberOfBytes)//�����ϣ�û�з����Ͷ���
				{
					MACRO_SAFE_CLOSESOCKET(lpOverlapped->m_sClientSocket);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				if (GetTCPContextSize() >= MAX_CONTEXT_SIZE)
				{
					MACRO_SAFE_CLOSESOCKET(lpOverlapped->m_sClientSocket);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				//ȡ�öԷ�IP
				GetAcceptExSockaddrs(lpOverlapped->m_wsaBuffer.buf,
					lpOverlapped->m_wsaBuffer.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
					sizeof(SOCKADDR_IN) + 16,
					sizeof(SOCKADDR_IN) + 16,
					(SOCKADDR **)&lpstrLocalAddr,
					&liLocalAddrLen,
					(SOCKADDR **)&lpstrRemoteAddr,
					&liRemoteAddrLen);

				TCPContext *lpNewContext = CreateContext();
				if (nullptr == lpNewContext)
				{
					MACRO_SAFE_CLOSESOCKET(lpOverlapped->m_sClientSocket);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				lpNewContext->m_hSocket = lpOverlapped->m_sClientSocket;
				lpNewContext->addr.sin_addr.s_addr = lpstrRemoteAddr->sin_addr.s_addr;
				lpNewContext->addr.sin_port = lpstrRemoteAddr->sin_port;
				InsertTCPContext(lpNewContext);
				if (nullptr == CreateIoCompletionPort((HANDLE)lpNewContext->m_hSocket, m_hCompletionPort, (ULONG_PTR)lpNewContext, 0))
				{
					RemoveTcpContextLogic(lpNewContext);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				m_TCPContextManager.OnRecvData(lpOverlapped->m_wsaBuffer.buf, dwNumberOfBytes, lpNewContext);

				lpOverlapped->m_eIoOperation = EnumIOOperationRead;
				liRet = WSARecv(lpNewContext->m_hSocket,
					&lpOverlapped->m_wsaBuffer,
					1,
					&dwNumberOfBytes,
					&ulFlags,
					(OVERLAPPED *)lpOverlapped,
					NULL);
				if (liRet == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
				{
					//�ͷ�lpOverlapPlus��lpNewContext
					RemoveTcpContextLogic(lpNewContext);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				break;
			}
			case EnumIOOperationRead:
			{
				if (0 == dwNumberOfBytes)
				{
					RemoveTcpContextLogic(pTCPContext);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				m_TCPContextManager.OnRecvData(lpOverlapped->m_wsaBuffer.buf, dwNumberOfBytes, pTCPContext);
				liRet = WSARecv(pTCPContext->m_hSocket,
					&lpOverlapped->m_wsaBuffer,
					1,
					&dwNumberOfBytes,
					&ulFlags,
					(OVERLAPPED *)lpOverlapped,
					NULL);

				if (liRet == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
				{
					RemoveTcpContextLogic(pTCPContext);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				break;
			}
			case EnumIOOperationWrite:
			{
				FreeOverlapPlus(lpOverlapped);
				break;
			}
			default:
				assert(false);
				break;
			}
		}
		else
		{
			switch (lpOverlapped->m_eIoOperation)
			{
			case EnumIOOperationAccept:
			{
				if (RemoveAcceptOverlapped(lpOverlapped))
				{
					MACRO_SAFE_CLOSESOCKET(lpOverlapped->m_sClientSocket);
					FreeOverlapPlus(lpOverlapped);
					continue;
				}
				break;
			}
			case EnumIOOperationRead:
			{
				RemoveTcpContextLogic(pTCPContext);
				FreeOverlapPlus(lpOverlapped);
				break;
			}
			case EnumIOOperationWrite:
			{
				FreeOverlapPlus(lpOverlapped);
				break;
			}
			default:
				break;
			}
		}
	}

}

void CIOCPServer::CheckSocketThread()
{
	DWORD  dwOptval = 0;
	int nOptlen = 0;
	int nResult = 0;
	OVERLAPPEDPLUS *pOverlapped = nullptr;
	DWORD dwWaitResult = 0;
	std::size_t nAcceptSize = 0;
	time_t tLastCheckTime = time(nullptr), tCurTime = 0;
	while (m_bContinueCheckSocket)
	{
		dwWaitResult = WaitForSingleObject(m_hAcceptEvent, 1000);
		if (!m_bContinueCheckSocket)
		{
			break;
		}
		if (WSA_WAIT_EVENT_0 == dwWaitResult)//Accept socket�ľ��ˣ�������������Ҫ���ˡ�
		{
			WSAResetEvent(m_hAcceptEvent);
		}
		if ((nAcceptSize = GetAcceptOverlappedSize()) < MIN_ACCEPT)//Accept socket�����ˣ�����Ͷ��
		{
			for (; nAcceptSize < MAX_ACCEPT; nAcceptSize++)
			{
				PostAccept();
			}
		}

		tCurTime = time(nullptr);
		if (tCurTime > tLastCheckTime + 10)
		{
			//������Ӻ󣬲�����������
			{
				std::lock_guard<std::mutex> lk(m_AcceptOverlappedMutex);
				for (OVERLAPPEDPLUS *pOverlapped : m_AcceptOverlappedSet)
				{
					nOptlen = sizeof(dwOptval);
					nResult = getsockopt(pOverlapped->m_sClientSocket, SOL_SOCKET, SO_CONNECT_TIME, (char*)&dwOptval, &nOptlen);
					if (SOCKET_ERROR == nResult
						|| ((dwOptval != 0xFFFFFFFF) && (dwOptval > CONNECT_TIMEOUT_SECOND)))
					{
						MACRO_SAFE_CLOSESOCKET(pOverlapped->m_sClientSocket);
					}
				}
			}

			//�����������
			{
				std::lock_guard<std::mutex> lk(m_TCPContextMutex);
				for (TCPContext *pTCPContext : m_TCPContextSet)
				{
					if (!pTCPContext->CheckSocket())
					{
						MACRO_SAFE_CLOSESOCKET(pTCPContext->m_hSocket);
					}
				}
			}
			
			tLastCheckTime = tCurTime;
		}
	}
}