#include "ClientSocket.h"
#include <assert.h>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#define RECV_BUF_LEN 1024

ClientSocket::ClientSocket()
	: m_mutex()
	, m_socket(INVALID_SOCKET)
	, m_addr()
	, m_bExit(false)
	, m_recvBuffer()
	, m_cvProcess()
	, m_recvThread()
	, m_processThread()
{
}


ClientSocket::~ClientSocket()
{
}

bool ClientSocket::open(const char * pAddress, unsigned short port)
{
	bool bRet = false;

	do
	{
		close();
		if (nullptr == pAddress
			|| 0 == port)
		{
			assert(false);
			break;
		}
		
		std::lock_guard<std::mutex> lk(m_mutex);
		if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			assert(false);
			break;
		}
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(port);
		m_addr.sin_addr.S_un.S_addr = inet_addr(pAddress);

		m_recvThread = std::thread(&ClientSocket::recvThread, this);
		m_processThread = std::thread(&ClientSocket::processThread, this);
		bRet = true;
	} while (false);
	return bRet;
}

bool ClientSocket::close()
{
	bool bRet = false;

	do
	{
		assert(std::this_thread::get_id() != m_processThread.get_id());
		{
			std::lock_guard<std::mutex> lk(m_mutex);
			m_bExit = true;
			m_cvProcess.notify_all();
		}
		if (m_recvThread.joinable())
		{
			m_recvThread.join();
		}
		if (m_processThread.joinable())
		{
			m_processThread.join();
		}
		{
			std::lock_guard<std::mutex> lk(m_mutex);
			if (INVALID_SOCKET != m_socket)
			{
				closesocket(m_socket);
				m_socket = INVALID_SOCKET;
			}
			memset(&m_addr, 0, sizeof(m_addr));
			m_bExit = false;
			m_recvBuffer.clear();
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool ClientSocket::send(const char * pBuffer, int len)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	if (m_bExit 
		|| INVALID_SOCKET == m_socket
		|| nullptr == pBuffer
		|| len <= 0)
	{
		assert(false);
		return false;
	}
	else
	{
		int nOffset = 0, nRet = 0;
		while ((nRet = ::send(m_socket, pBuffer + nOffset, len - nOffset, 0)) != SOCKET_ERROR
			&& nOffset < len)
		{
			nOffset += nRet;
		}
		assert(nRet != SOCKET_ERROR);
		return (nRet != SOCKET_ERROR);
	}
}

void ClientSocket::recvThread()
{
	bool bConnect = false;
	int ret = 0;
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		ret = connect(m_socket, reinterpret_cast<const sockaddr*>(&m_addr), sizeof(m_addr));
		bConnect = (SOCKET_ERROR != ret);
	}
	this->onConnect(bConnect);
	if (!bConnect)
	{
		return;
	}
	
	fd_set set = { 0 };;
	timeval tv = { 0 };
	tv.tv_sec = 0;
	tv.tv_usec = 50 * 1000;
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		if (m_bExit)
		{
			break;
		}
		FD_ZERO(&set);
		FD_SET(m_socket, &set);
		
		lk.unlock();
		ret = select(0, &set, nullptr, nullptr, &tv);
		lk.lock();

		if (SOCKET_ERROR == ret)
		{
			lk.unlock();
			this->onClose();
			break;
		}
		else if (FD_ISSET(m_socket, &set))
		{
			char szBuf[RECV_BUF_LEN];
			if ((ret = recv(m_socket, szBuf, sizeof(szBuf), 0)) > 0)
			{
				m_recvBuffer.append(szBuf, ret);
				m_cvProcess.notify_one();
			}
			else
			{
				lk.unlock();
				this->onClose();
				break;
			}
		}
	}
}

void ClientSocket::processThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		int nPacketLen = 0;
		auto checkFun = [this, &nPacketLen]()->bool
			{
				return m_bExit 
					|| ((nPacketLen = this->getOnePacketLength(m_recvBuffer.data(), m_recvBuffer.size())) > 0);
			};
		m_cvProcess.wait(lk, checkFun);
		if (m_bExit)
		{
			break;
		}
		if (nPacketLen > 0)
		{
			std::string strTemp = m_recvBuffer.substr(0, nPacketLen);
			m_recvBuffer.erase(0, nPacketLen);
			lk.unlock();
			this->onRecv(strTemp.data(), strTemp.size());
		}
	}
}
