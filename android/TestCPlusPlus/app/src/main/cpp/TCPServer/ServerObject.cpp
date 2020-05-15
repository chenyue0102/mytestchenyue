#include "ServerObject.h"
#include <algorithm>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>//sockaddr_in
#include <fcntl.h>//fcntl
#include <unistd.h>//read,close
#include "Log.h"
#include "Single.h"
#include "EPollObject.h"
#include "TaskPool.h"

#define MY_PORT 5617
#define MY_UDPPORT 5618
#define BACKLOG 8
#define MAX_SENDLEN 512
ServerObject::ServerObject()
	: m_fdListen(-1)
	, m_fdUdp(-1)
	, m_mutex()
	, m_port()
	, m_pUserObjectManager(nullptr)
	, m_pUDPUserObjectManager(nullptr)
{
}


ServerObject::~ServerObject()
{
}

bool ServerObject::init(IUserObjectManager *pUserObjectManager)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	bool bRes = false;

	do
	{
		if (nullptr == (m_pUserObjectManager = pUserObjectManager))
		{
			LOG(LOG_ERR, "ServerObject::init pUserObjectManager failed\n");
			assert(false);
			break;
		}
		if ((m_fdListen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			LOG(LOG_ERR, "ServerObject::init socket errno=%d\n", errno);
			assert(false);
			break;
		}
		int optval = 1;
		if (setsockopt(m_fdListen, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		{
			printf("ServerObject::init setsockopt errno=%d\n", errno);
			break;
		}

		int flags = fcntl(m_fdListen, F_GETFL, 0);
		if (fcntl(m_fdListen, F_SETFL, flags | O_NONBLOCK) < 0)
		{
			LOG(LOG_ERR, "ServerObject::init fcntl errno=%d\n", errno);
			assert(false);
			break;
		}

		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(MY_PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(m_fdListen, (const sockaddr*)&addr, sizeof(addr)) < 0)
		{
			LOG(LOG_ERR, "ServerObject::init bind errno=%d\n", errno);
			assert(false);
			break;
		}
		if (-1 == listen(m_fdListen, BACKLOG))
		{
			LOG(LOG_ERR, "ServerObject::init listen errno=%d\n", errno);
			assert(false);
			break;
		}
		EPollObject &epollObject = Single<EPollObject>::Instance();

		auto acceptFun = [this]()
		{
			onAsyncAccept();
		};
		if (!epollObject.updateFun(m_fdListen, ET_READ, acceptFun))
		{
			LOG(LOG_ERR, "ServerObject::init updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		auto acceptErrorFun = [this]()
		{
			onAsyncAcceptError();
		};
		if (!epollObject.updateFun(m_fdListen, ET_ERROR, acceptErrorFun))
		{
			LOG(LOG_ERR, "ServerObject::init updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		bRes = true;
	} while (false);
	return bRes;
}

bool ServerObject::destory()
{
	std::lock_guard<std::mutex> lk(m_mutex);


	return false;
}

bool ServerObject::send(int fd, const char * pBuffer, unsigned int nLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		if (nullptr == pBuffer
			|| 0 == nLen)
		{
			LOG(LOG_ERR, "ServerObject::send param failed\n");
			assert(false);
			break;
		}
		auto iter = m_acceptSocketArray.find(fd);
		if (iter == m_acceptSocketArray.end())
		{
			LOG(LOG_ERR, "ServerObject::send iter == m_acceptSocketArray.end() failed\n");
			//assert(false);
			break;
		}
		SOCKET_INFO &sockInfo = iter->second;
		if (sockInfo.sendBytes.empty())
		{
			ssize_t sendLen = innerDoSend(fd, pBuffer, nLen);
			if (sendLen < 0)
			{
				sockInfo.bClosing = true;
				//assert(false);
				break;
			}
			else
			{
				if (sendLen < nLen)
				{
					sockInfo.sendBytes.append(pBuffer + sendLen, nLen - sendLen);
				}
			}
		}
		else
		{
			sockInfo.sendBytes.append(pBuffer, nLen);
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool ServerObject::closeSocket(int fd, bool bFocus)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		auto iter = m_acceptSocketArray.find(fd);
		if (iter == m_acceptSocketArray.end())
		{
			LOG(LOG_ERR, "ServerObject::closeSocket iter == m_acceptSocketArray.end() failed\n");
			//assert(false);
			break;
		}
		if (bFocus)
		{
			linger optval;
			optval.l_onoff = 1;
			optval.l_linger = 0;
			if (-1 == setsockopt(fd, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval)))
			{
				LOG(LOG_ERR, "ServerObject::closeSocket setsockopt errno=%d\n", errno);
			}
			if (!innerCleanSocket(fd))
			{
				LOG(LOG_ERR, "ServerObject::closeSocket innerCleanSocket failed\n");
				assert(false);
				break;
			}
		}
		else
		{
			SOCKET_INFO &sockInfo = iter->second;
			if (sockInfo.sendBytes.empty())
			{
				if (!innerCleanSocket(fd))
				{
					LOG(LOG_ERR, "ServerObject::closeSocket innerCleanSocket failed\n");
					assert(false);
					break;
				}
			}
			else
			{
				sockInfo.bClosing = true;//等待所有数据包都发送后再关闭
			}
		}
		bRet = true;
	} while (false);
	return bRet;
}

void ServerObject::eventLoop()
{
	while (true)
	{
		sleep(1);
	}
}

void ServerObject::onAsyncAccept()const
{
	ServerObject *pThis = const_cast<ServerObject*>(this);
	auto asyncFun = [pThis]()
	{
		pThis->callInnerAccept();
	};
	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.AddOrderTask(asyncFun, getTaskGroupId());
}

void ServerObject::onAsyncAcceptError() const
{
	ServerObject *pThis = const_cast<ServerObject*>(this);
	auto asyncFun = [pThis]()
	{
		pThis->callInnerAcceptError();
	};
	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.AddOrderTask(asyncFun, getTaskGroupId());
}

void ServerObject::onAsyncRead(int fd)const
{
	ServerObject *pThis = const_cast<ServerObject*>(this);
	auto asyncFun = [pThis, fd]()
	{
		pThis->callInnerRead(fd);
	};
	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.AddOrderTask(asyncFun, getTaskGroupId());
}

void ServerObject::onAsyncSend(int fd)const
{
	ServerObject *pThis = const_cast<ServerObject*>(this);
	auto asyncFun = [pThis, fd]()
	{
		pThis->callInnerSend(fd);
	};
	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.AddOrderTask(asyncFun, getTaskGroupId());
}

void ServerObject::onAsyncError(int fd)const
{
	ServerObject *pThis = const_cast<ServerObject*>(this);
	auto asyncFun = [pThis, fd]()
	{
		pThis->callInnerCleanSocket(fd);
	};
	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.AddOrderTask(asyncFun, getTaskGroupId());
}

void ServerObject::callInnerCleanSocket(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	innerCleanSocket(fd);
}

void ServerObject::callInnerAccept()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	while (innerAccept());
}

void ServerObject::callInnerAcceptError()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	LOG(LOG_ERR, "ServerObject::callInnerAcceptError\n");
	assert(false);
}

void ServerObject::callInnerRead(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	while (innerRead(fd));
}

void ServerObject::callInnerSend(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	innerSendCachingData(fd);
}

ssize_t ServerObject::innerDoSend(int fd, const char * pBuffer, ssize_t nLen)
{
	ssize_t ret = 0, offset = 0;
	bool bRet = true;
	do
	{
		//MSG_NOSIGNAL标记，发送失败，不发送信号SIGPIPE 
		ret = ::send(fd, pBuffer + offset, std::min(nLen - offset, static_cast<ssize_t>(MAX_SENDLEN)), MSG_NOSIGNAL);
		if (ret > 0)
		{
			offset += ret;
		}
		else if (0 == ret)
		{
			LOG(LOG_ERR, "ServerObject::innerDoSend send 0\n");
			assert(false);
			break;
		}
		else
		{
			if (!(EAGAIN == errno
				|| EINTR == errno))
			{
				LOG(LOG_ERR, "ServerObject::innerDoSend send errno=%d\n", errno);
				offset = ret;
			}
			break;
		}
	} while (ret > 0 && offset < nLen);
	return offset;
}

bool ServerObject::innerCleanSocket(int fd)
{
	if (0 == m_acceptSocketArray.erase(fd))
	{
		LOG(LOG_ERR, "ServerObject::onRead 0 == m_acceptSocketArray.erase(fd) failed\n");
	}
	EPollObject &epollObject = Single<EPollObject>::Instance();
	if (!epollObject.removeFun(fd))
	{
		LOG(LOG_ERR, "ServerObject::onRead !epollObject.removeFun(fd) failed\n");
	}
	if (close(fd) < 0)
	{
		LOG(LOG_ERR, "ServerObject::onRead close errno=%d\n", errno);
		assert(false);
	}
	if (nullptr != m_pUserObjectManager)
	{
		m_pUserObjectManager->notifyClose(fd);
	}
	return true;
}

bool ServerObject::innerAccept()
{
	bool bRet = false;
	int acpSock = -1;

	do
	{
		if (nullptr == m_pUserObjectManager)
		{
			LOG(LOG_ERR, "ServerObject::onAccept nullptr == m_pUserObjectManager\n");
			assert(false);
			break;
		}
		sockaddr_in addr = { 0 };
		socklen_t addrlen = sizeof(addr);
		if ((acpSock = accept(m_fdListen, reinterpret_cast<sockaddr*>(&addr), &addrlen)) < 0)
		{
			if (EAGAIN != errno)
			{
				LOG(LOG_ERR, "ServerObject::onAccept accept errno=%d\n", errno);
				assert(false);
			}
			break;
		}
		int flags = fcntl(m_fdListen, F_GETFL, 0);
		if (fcntl(acpSock, F_SETFL, flags | O_NONBLOCK) < 0)
		{
			LOG(LOG_ERR, "ServerObject::onAccept fcntl errno=%d\n", errno);
			assert(false);
			break;
		}

		EPollObject &epollObject = Single<EPollObject>::Instance();

		auto readFun = [this, acpSock]()
		{
			onAsyncRead(acpSock);
		};
		if (!epollObject.updateFun(acpSock, ET_READ, readFun))
		{
			LOG(LOG_ERR, "ServerObject::onAccept updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		auto sendFun = [this, acpSock]()
		{
			onAsyncSend(acpSock);
		};
		if (!epollObject.updateFun(acpSock, ET_WRITE, sendFun))
		{
			LOG(LOG_ERR, "ServerObject::onAccept updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		auto errorFun = [this, acpSock]()
		{
			onAsyncError(acpSock);
		};
		if (!epollObject.updateFun(acpSock, ET_ERROR, errorFun))
		{
			LOG(LOG_ERR, "ServerObject::onAccept updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		m_acceptSocketArray.insert(std::make_pair(acpSock, SOCKET_INFO()));

		m_pUserObjectManager->notifyAccept(acpSock, addr);

		bRet = true;
	} while (false);

	if (!bRet)
	{
		if (-1 != acpSock)
		{
			if (close(acpSock) < 0)
			{
				LOG(LOG_ERR, "ServerObject::onAccept close errno=%d\n", errno);
			}
			acpSock = -1;
		}
	}
	return bRet;
}

bool ServerObject::innerRead(int fd)
{
	bool bRet = false;
	char buf[1024];

	do
	{
		if (nullptr == m_pUserObjectManager)
		{
			LOG(LOG_ERR, "ServerObject::onRead nullptr == m_pUserObjectManager failed\n");
			assert(false);
			break;
		}
		auto iter = m_acceptSocketArray.find(fd);
		if (iter == m_acceptSocketArray.end())
		{
			LOG(LOG_ERR, "ServerObject::onRead iter == m_acceptSocketArray.end() failed\n");
			break;
		}

		ssize_t ret = recv(fd, buf, sizeof(buf), 0);
		bool bCleanSocket = false;
		if (ret > 0)
		{
			if (!iter->second.bClosing)
			{
				m_pUserObjectManager->notifyRecv(fd, buf, static_cast<unsigned int>(ret));
			}
		}
		else if (0 == ret)
		{
			//client close
			bCleanSocket = true;
		}
		else
		{
			//error
			if (EAGAIN == errno
				|| EINTR == errno)
			{
				break;
			}
			else
			{
				LOG(LOG_ERR, "ServerObject::onRead recv errno=%d\n", errno);
				bCleanSocket = true;
			}
		}

		if (bCleanSocket)
		{
			innerCleanSocket(fd);
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool ServerObject::innerSendCachingData(int fd)
{
	bool bRet = false;

	do
	{
		if (nullptr == m_pUserObjectManager)
		{
			LOG(LOG_ERR, "ServerObject::innerSendCachingData nullptr == m_pUserObjectManager failed\n");
			assert(false);
			break;
		}
		auto iter = m_acceptSocketArray.find(fd);
		if (iter == m_acceptSocketArray.end())
		{
			LOG(LOG_ERR, "ServerObject::innerSendCachingData iter == m_acceptSocketArray.end() failed\n");
			break;
		}
		SOCKET_INFO &sockInfo = iter->second;
		auto &sendBytes = sockInfo.sendBytes;
		if (sendBytes.empty())
		{
			break;
		}
		ssize_t sendLen = innerDoSend(fd, sendBytes.data(), sendBytes.size());
		if (sendLen < 0)
		{
			innerCleanSocket(fd);
			break;
		}
		else
		{
			sendBytes.erase(0, sendLen);

			if (sendBytes.empty()
				&& sockInfo.bClosing)
			{
				innerCleanSocket(fd);
				break;
			}
		}

		//bRet = true;
	} while (false);
	return bRet;
}

std::size_t ServerObject::getTaskGroupId() const
{
	return reinterpret_cast<std::size_t>(this);
}
