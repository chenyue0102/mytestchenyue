#include "stdafx.h"
#include "IOCP.h"
#include <assert.h>


CIOCP::CIOCP()
	: m_hCompletionPort(nullptr)
	, m_ListenSocketContext()
	, m_lpfnAcceptEx(nullptr)
	, m_lpfnGetAcceptExSockAddrs(nullptr)
	, m_IOCPThreadArray()
	, m_ConnectSocketContextArray()
	, m_mxConnectSocketContext()
{
}


CIOCP::~CIOCP()
{
	assert(nullptr != m_hCompletionPort);
}

bool CIOCP::Open(unsigned short usPort)
{
	bool bRes = false;

	do 
	{
		if (nullptr == (m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0)))
		{
			assert(false);
			break;
		}
		
		auto &sockListen = m_ListenSocketContext.conSocket;
		if (INVALID_SOCKET == (sockListen = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED)))
		{
			assert(false);
			break;
		}
		CreateIoCompletionPort((HANDLE)sockListen, m_hCompletionPort, (ULONG_PTR)&m_ListenSocketContext, 0);

		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);
		addr.sin_port = htons(usPort);
		if (0 != bind(sockListen, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)))
		{
			assert(false);
			break;
		}
		
		if (0 != listen(sockListen, SOMAXCONN))
		{
			assert(false);
			break;
		}
		
		// AcceptEx 和 GetAcceptExSockaddrs 的GUID，用于导出函数指针
		GUID GuidAcceptEx = WSAID_ACCEPTEX;
		GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
		DWORD dwBytes = 0;
		if (0 != WSAIoctl(sockListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, sizeof(GuidAcceptEx), 
			&m_lpfnAcceptEx, sizeof(m_lpfnAcceptEx), &dwBytes, NULL, NULL))
		{
			assert(false);
			break;
		}

		if (0 != WSAIoctl(sockListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockAddrs, sizeof(GuidGetAcceptExSockAddrs),
			&m_lpfnGetAcceptExSockAddrs, sizeof(m_lpfnGetAcceptExSockAddrs), &dwBytes, NULL, NULL))
		{
			assert(false);
			break;
		}
		auto nThreadCount = std::thread::hardware_concurrency();
		if (0 == nThreadCount)
		{
			nThreadCount = 1;
		}
		nThreadCount *= 2;
		nThreadCount = 2;
		for (unsigned int nIndex = 0; nIndex < nThreadCount; nIndex++)
		{
			m_IOCPThreadArray.push_back(std::thread(&CIOCP::IOCPThread, this));
		}

		auto &ReadContext = m_ListenSocketContext.ReadContext;
		ReadContext.conSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		ReadContext.IOType = EnumIOTypeAccept;
		WSABUF wsaBuf = {0};
		wsaBuf.buf = const_cast<char*>(ReadContext.Buffer.data());
		wsaBuf.len = ReadContext.Buffer.size();
		dwBytes = 0;

		m_lpfnAcceptEx(sockListen, ReadContext.conSocket, wsaBuf.buf, wsaBuf.len - ((sizeof(SOCKADDR_IN) + 16) * 2), sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
			&dwBytes, &ReadContext.overlapped);
		bRes = true;
	} while (false);
	return bRes;
}

bool CIOCP::Close()
{
	bool bRes = false;

	do 
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = nullptr;

		for (auto &OneThread : m_IOCPThreadArray)
		{
			OneThread.join();
		}
		m_IOCPThreadArray.clear();

		closesocket(m_ListenSocketContext.conSocket);
		m_ListenSocketContext.conSocket = INVALID_SOCKET;

		m_lpfnAcceptEx = nullptr;
		m_lpfnGetAcceptExSockAddrs = nullptr;

		{
			std::lock_guard<std::mutex> lock(m_mxConnectSocketContext);
			for (auto &OneSockContext : m_ConnectSocketContextArray)
			{
				closesocket(OneSockContext.second->conSocket);
				OneSockContext.second->conSocket = INVALID_SOCKET;
			}
			m_ConnectSocketContextArray.clear();
		}

		bRes = true;
	} while (false);
	return bRes;
}

bool CIOCP::SendData(const void *pBuffer, unsigned int nLen)
{
	std::shared_ptr<SocketContext> pSocketContext = m_ConnectSocketContextArray.begin()->second;
	return InnerSendData(pSocketContext.get(), pBuffer, nLen);
}

bool CIOCP::InnerSendData(SocketContext *pSocketContext, const void *pBuffer, unsigned int nLen)
{
	if (nullptr == pSocketContext
		|| nullptr == pBuffer
		|| 0 == nLen)
	{
		assert(false);
		return false;
	}
	EnterCriticalSection(&pSocketContext->cs);
	std::shared_ptr<IOWriteContext> pWriteContext = std::make_shared<IOWriteContext>();
	pWriteContext->Buffer.append(reinterpret_cast<const char*>(pBuffer), nLen);
	auto &WriteContextArray = pSocketContext->WriteContextArray;
	WriteContextArray.push_back(pWriteContext);

	switch (pSocketContext->WriteStep)
	{
	case EnumWriteStepNone:
	{
		//发送一个Write请求
		pSocketContext->WriteStep = EnumWriteStepPost;
		PostQueuedCompletionStatus(m_hCompletionPort, 0, (ULONG_PTR)pSocketContext, &pSocketContext->WriteContext.overlapped);
	}
	break;
	case EnumWriteStepPost:
	case EnumWriteStepProcessing:
	{

	}
	break;
	default:
		assert(false);
		break;
	}
	LeaveCriticalSection(&pSocketContext->cs);

	return true;
}

void CIOCP::IOCPThread()
{
	while (true)
	{
		DWORD dwBytesTransfered = 0;
		OVERLAPPED          *pOverlapped = NULL;
		SocketContext		*pSocketContext = NULL;
		if (!GetQueuedCompletionStatus(
			m_hCompletionPort,
			&dwBytesTransfered,
			(PULONG_PTR)&pSocketContext,
			&pOverlapped,
			INFINITE))
		{
			/*auto itor = std::find_if(SocketContextArray.begin(), SocketContextArray.end(),
				[pSocketContext](std::shared_ptr<PER_SOCKET_CONTEXT> pTemp) {return pSocketContext == pTemp.get(); });
			if (itor != SocketContextArray.end())
			{
				closesocket(pSocketContext->m_Socket);
				SocketContextArray.erase(itor);
				continue;
			}*/
		}
		if (nullptr == pSocketContext)
		{
			break;
		}

		IOContext* pIoContext = CONTAINING_RECORD(pOverlapped, IOContext, overlapped);
		switch (pIoContext->IOType)
		{
		case EnumIOTypeAccept:
			{
				IOReadContext *pReadContext = static_cast<IOReadContext*>(pIoContext);
				OnAccept(pReadContext, dwBytesTransfered);
			}
			break;
		case EnumIOTypeRead:
			{
				IOReadContext *pReadContext = static_cast<IOReadContext*>(pIoContext);
				OnRead(pSocketContext, pReadContext, dwBytesTransfered);
			}
			break;
		case EnumIOTypeWrite:
			{
				IOWriteContext *pWriteContext = static_cast<IOWriteContext*>(pIoContext);
				OnWrite(pSocketContext, pWriteContext, dwBytesTransfered);
			}
			break;
		case EnumIOTypeWriteComplete:
			{
				IOWriteContext *pWriteContext = static_cast<IOWriteContext*>(pIoContext);
				OnWriteComplete(pSocketContext, pWriteContext, dwBytesTransfered);
			}
			break;
		}
	}
}

void CIOCP::OnAccept(IOReadContext *pAcceptContext, DWORD dwBytesTransfered)
{
	SOCKADDR_IN* ClientAddr = NULL;
	SOCKADDR_IN* LocalAddr = NULL;
	char *pBuffer = const_cast<char*>(pAcceptContext->Buffer.data());
	int nLen = pAcceptContext->Buffer.size();
	int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);
	m_lpfnGetAcceptExSockAddrs(pBuffer, nLen - ((sizeof(SOCKADDR_IN) + 16) * 2),
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, (LPSOCKADDR*)&LocalAddr, &localLen, (LPSOCKADDR*)&ClientAddr, &remoteLen);

	std::shared_ptr<SocketContext> pNewSocketContext = std::make_shared<SocketContext>();
	unsigned long long ullKey = reinterpret_cast<unsigned long long>(pNewSocketContext.get());
	pNewSocketContext->ullKey = ullKey;
	{
		std::lock_guard<std::mutex> lock(m_mxConnectSocketContext);
		m_ConnectSocketContextArray.insert(std::make_pair(ullKey, pNewSocketContext));
	}
	NotifyAccept(ullKey, *ClientAddr);
	NotifyRead(ullKey, pAcceptContext->Buffer.data(), dwBytesTransfered);

	pNewSocketContext->conSocket = pAcceptContext->conSocket;
	pNewSocketContext->ClientAddr = *ClientAddr;
	CreateIoCompletionPort((HANDLE)pNewSocketContext->conSocket, m_hCompletionPort, (DWORD)pNewSocketContext.get(), 0);

	//投递一个接收
	auto &ReadContext = pNewSocketContext->ReadContext;
	ReadContext.conSocket = pNewSocketContext->conSocket;
	ReadContext.IOType = EnumIOTypeRead;
	WSABUF wsaBuf = { 0 };
	wsaBuf.buf = &ReadContext.Buffer[0];
	wsaBuf.len = ReadContext.Buffer.size();
	DWORD dwFlags = 0;
	DWORD dwBytes = 0;
	WSARecv(ReadContext.conSocket, &wsaBuf, 1, &dwBytes, &dwFlags, &ReadContext.overlapped, nullptr);

	//再次投递一个accept
	pAcceptContext->conSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	WSABUF newAccept = { 0 };
	newAccept.buf = &(pAcceptContext->Buffer[0]);
	newAccept.len = pAcceptContext->Buffer.size();

	DWORD dwNewAcceptBytes = 0;
	m_lpfnAcceptEx(m_ListenSocketContext.conSocket, pAcceptContext->conSocket, newAccept.buf, newAccept.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwNewAcceptBytes, &pAcceptContext->overlapped);
}

void CIOCP::OnRead(SocketContext *pSocketContext, IOReadContext *pReadContext, DWORD dwBytesTransfered)
{
	unsigned long long ullKey = reinterpret_cast<unsigned long long>(pSocketContext);
	{
		std::lock_guard<std::mutex> lock(m_mxConnectSocketContext);
		auto itor = m_ConnectSocketContextArray.find(ullKey);
		if (itor == m_ConnectSocketContextArray.end())
		{
			assert(false);
			return;
		}
	}
	NotifyRead(ullKey, pReadContext->Buffer.data(), dwBytesTransfered);
	
	//投递一个recv
	WSABUF wsaBuf = { 0 };
	wsaBuf.buf = &pReadContext->Buffer[0];
	wsaBuf.len = pReadContext->Buffer.size();

	DWORD dwBytes = 0, dwFlags = 0;
	WSARecv(pReadContext->conSocket, &wsaBuf, 1, &dwBytes, &dwFlags, &pReadContext->overlapped, nullptr);
}

void CIOCP::OnWrite(SocketContext *pSocketContext, IOWriteContext *pWriteContext, DWORD dwBytesTransfered)
{
	std::vector<std::shared_ptr<IOWriteContext>> TempWriteContextArray;
	EnterCriticalSection(&pSocketContext->cs);
	pSocketContext->WriteStep = EnumWriteStepProcessing;

	TempWriteContextArray = std::move(pSocketContext->WriteContextArray);
	if (0 != TempWriteContextArray.size())
	{
		for (auto &OneWriteContext : TempWriteContextArray)
		{
			OneWriteContext->IOType = EnumIOTypeWriteComplete;
		}
		pSocketContext->WriteCompleteContextArray.insert(pSocketContext->WriteCompleteContextArray.end(),
			TempWriteContextArray.begin(), TempWriteContextArray.end());
	}
	

	if (0 != TempWriteContextArray.size())
	{
		std::unique_ptr<WSABUF[]> pwsaBuf(std::make_unique<WSABUF[]>(TempWriteContextArray.size()));
		for (unsigned int nIndex = 0; nIndex < TempWriteContextArray.size(); nIndex++)
		{
			auto &OneWriteContext = TempWriteContextArray[nIndex];
			OneWriteContext->bHaveWSASend = true;
			pwsaBuf[nIndex].buf = &(OneWriteContext->Buffer[0]);
			pwsaBuf[nIndex].len = OneWriteContext->Buffer.size();
		}
		DWORD dwFlags = 0;
		DWORD dwSendNumBytes = 0;
		if (0 != WSASend(pSocketContext->conSocket, pwsaBuf.get(), TempWriteContextArray.size(), &dwSendNumBytes, dwFlags,
			&TempWriteContextArray[0]->overlapped, nullptr))
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				assert(false);
			}
		}
		TempWriteContextArray.clear();
	}
		
	pSocketContext->WriteStep = EnumWriteStepNone;
	LeaveCriticalSection(&pSocketContext->cs);
}

void CIOCP::OnWriteComplete(SocketContext *pSocketContext, IOWriteContext *pWriteContext, DWORD dwBytesTransfered)
{
	int nCurBytesTransfered = dwBytesTransfered;
	EnterCriticalSection(&pSocketContext->cs);
	auto &WriteCompleteContextArray = pSocketContext->WriteCompleteContextArray;
	auto itor = std::find_if(WriteCompleteContextArray.begin(), WriteCompleteContextArray.end(),
		[pWriteContext](const std::shared_ptr<IOWriteContext> &pTemp) ->bool {return pWriteContext == pTemp.get(); });
	while (itor != WriteCompleteContextArray.end())
	{
		IOWriteContext *pOneWriteContext = itor->get();
		nCurBytesTransfered -= pOneWriteContext->Buffer.size();
		if (0 == nCurBytesTransfered)
		{
			itor = WriteCompleteContextArray.erase(itor);//成功发送
			break;
		}
		else if (nCurBytesTransfered > 0)
		{
			itor = WriteCompleteContextArray.erase(itor);//成功发送
		}
		else
		{
			assert(false);//部分发送
		}
	}

	LeaveCriticalSection(&pSocketContext->cs);
}

void CIOCP::NotifyAccept(unsigned long long ullKey, const sockaddr_in &addr)
{

}

void CIOCP::NotifyRead(unsigned long long ullKey, const void *pBuffer, unsigned int uiLen)
{
	std::string strTempData((char*)pBuffer, uiLen);
	strTempData += '\n';
	OutputDebugStringA(strTempData.c_str());
	OutputDebugStringA((std::to_string(GetCurrentThreadId()) + '\0').c_str());
}
