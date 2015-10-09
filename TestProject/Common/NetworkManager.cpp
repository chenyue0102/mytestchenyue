#include "NetworkManager.h"
#include <assert.h>
#include <process.h>

#define RECEIVE_BUF_LEN		2048
CNetworkManager::CNetworkManager(void)
	: m_socket(INVALID_SOCKET)
	, m_hSelectEvent(WSACreateEvent())
	, m_hReceiveThread(nullptr)
	, m_hExitThreadEvent(WSACreateEvent())
	, m_pNetworkCallback(nullptr)
	, m_usPort(0)
	, m_dwEventSelect(FD_CONNECT | FD_READ | FD_CLOSE)
	, m_bExitFlag(FALSE)
{
	memset(&m_addr, 0, sizeof(m_addr));
}

CNetworkManager::~CNetworkManager(void)
{
	StopSocket();
	if (nullptr != m_hSelectEvent)
	{
		CloseHandle(m_hSelectEvent);
		m_hSelectEvent = nullptr;
	}
	if (nullptr != m_hExitThreadEvent)
	{
		CloseHandle(m_hExitThreadEvent);
		m_hExitThreadEvent = nullptr;
	}
}

BOOL CNetworkManager::Init(INetworkCallback	*pNetworkCallback, const std::string &strAddress, USHORT usPort)
{
	m_pNetworkCallback = pNetworkCallback;
	m_strAddress = strAddress;
	m_usPort = usPort;
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(m_usPort);
	m_addr.sin_addr.s_addr = inet_addr(m_strAddress.c_str());
	m_strNetworkRecvBuffer.resize(RECEIVE_BUF_LEN);
	return TRUE;
}

BOOL	CNetworkManager::StopSocket()
{
	m_bExitFlag = TRUE;
	if (nullptr != m_hReceiveThread)
	{
		SetEvent(m_hExitThreadEvent);
		DWORD dwWaitResult = WaitForSingleObject(m_hReceiveThread, INFINITE);
		assert(dwWaitResult == WAIT_OBJECT_0);
		CloseHandle(m_hReceiveThread);
		m_hReceiveThread = nullptr;
	}
	if (INVALID_SOCKET != m_socket)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	return TRUE;
}

BOOL CNetworkManager::Connect()
{
	BOOL bRes = FALSE;
	do 
	{
		if (!StopSocket())
		{
			assert(false);
			break;
		}
		m_bExitFlag = FALSE;
		ResetEvent(m_hExitThreadEvent);
		WSAResetEvent(m_hSelectEvent);
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == m_socket)
		{
			assert(false);
			break;
		}
		if (SOCKET_ERROR == WSAEventSelect(m_socket, m_hSelectEvent,  m_dwEventSelect))
		{
			assert(false);
			break;
		}

		if (SOCKET_ERROR == WSAConnect(m_socket, reinterpret_cast<sockaddr*>(&m_addr), sizeof(m_addr), nullptr, nullptr, nullptr, nullptr))
		{
			if (GetLastError() != WSAEWOULDBLOCK)
			{
				assert(false);
				break;
			}
		}
		
		m_hReceiveThread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, &CNetworkManager::SocketThread, this, 0, nullptr));
		if (nullptr == m_hReceiveThread)
		{
			assert(false);
			break;
		}
		bRes = TRUE;
	} while (FALSE);

	return bRes;
}

BOOL CNetworkManager::SendData( const void *pBuf, DWORD dwBufLen )
{
	BOOL bRes = FALSE;
	do 
	{
		if (nullptr == pBuf
			|| 0 == dwBufLen)
		{
			assert(false);
			break;
		}
		//send函数如果多线程调用，有可能出现乱报，必须加锁
		CAutoLock AutoLock(m_NormalLock);
		int nSendPos = 0;
		BOOL bSendError = FALSE;
		while(static_cast<DWORD>(nSendPos) < dwBufLen)
		{
			int nCurLength = send(m_socket, reinterpret_cast<const char*>(pBuf) + nSendPos, dwBufLen - nSendPos, 0);
			if (SOCKET_ERROR == nCurLength)
			{
				bSendError = TRUE;
				assert(false);
				break;
			}
			else if (nCurLength > 0)
			{
				nSendPos += nCurLength;
			}
			else
			{
				//返回0，表示0个字节已被发送，是合法的返回值。
				break;
			}
		}
		if (bSendError)
		{
			assert(false);
			break;
		}
		
		bRes = TRUE;
	} while (FALSE);
	return bRes;
}

unsigned int __stdcall CNetworkManager::SocketThread( void *pArgument )
{
	CNetworkManager *pManager = reinterpret_cast<CNetworkManager*>(pArgument);
	HANDLE hWaitEvents[] = {pManager->m_hExitThreadEvent, pManager->m_hSelectEvent};
	BOOL bContinue = TRUE;
	DWORD dwWaitResult = 0;

	while (bContinue)
	{
		dwWaitResult = WSAWaitForMultipleEvents(_countof(hWaitEvents), hWaitEvents, FALSE, WSA_INFINITE, FALSE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0 + 0:
			bContinue = FALSE;
			break;
		case WAIT_OBJECT_0 + 1:
			{
				WSAResetEvent(hWaitEvents[1]);
				WSANETWORKEVENTS wsaNetworkEvent = { 0 };
				if (SOCKET_ERROR == WSAEnumNetworkEvents(pManager->m_socket, pManager->m_hSelectEvent, &wsaNetworkEvent))
				{
					bContinue = FALSE;
					assert(false);
				}
				else
				{
					pManager->OnSockEvent(wsaNetworkEvent, bContinue);
				}
			}
			break;
		case WAIT_TIMEOUT:
			{
				assert(false);
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	return 0;
}

void CNetworkManager::OnSockEvent( const WSANETWORKEVENTS &wsaNetworkEvent, BOOL &bContinue )
{
	if (FD_READ & wsaNetworkEvent.lNetworkEvents)
	{
		BOOL bSuccess = (0 == wsaNetworkEvent.iErrorCode[FD_READ_BIT]);
		if (bSuccess)
		{
			m_strNetworkRecvBuffer.clear();
			unsigned long lRead = 0;
			if (SOCKET_ERROR != ioctlsocket(m_socket, FIONREAD, &lRead))	//获取缓冲区中数据量大小
			{
				m_strNetworkRecvBuffer.resize(lRead);
				int iRecvLen = recv(m_socket, &*m_strNetworkRecvBuffer.begin(), lRead, 0);
				if (iRecvLen <= 0
					|| iRecvLen != lRead)
				{
					bSuccess = FALSE;
					assert(false);
				}
			}
			else
			{
				bSuccess = FALSE;
				assert(false);
			}
			if (bSuccess)
			{
				m_pNetworkCallback->NotifyRead(m_strNetworkRecvBuffer.data(), lRead);
			}
		}
		else
		{
			assert(false);
		}
	}

	if (FD_CLOSE & wsaNetworkEvent.lNetworkEvents)
	{
		bContinue = FALSE;
		m_pNetworkCallback->NotifyClose();
	}

	if (FD_CONNECT & wsaNetworkEvent.lNetworkEvents)
	{
		BOOL bSuccess = (0 == wsaNetworkEvent.iErrorCode[FD_CONNECT_BIT]);
		if (!bSuccess)
		{
			bContinue = FALSE;
		}
		m_pNetworkCallback->NotifyConnect(bSuccess);
	}
}