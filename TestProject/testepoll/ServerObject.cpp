#include "ServerObject.h"
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>//sockaddr_in
#include <fcntl.h>//fcntl
#include <unistd.h>//read,close
#include "Log.h"
#include "Single.h"
#include "EPollObject.h"

#define MY_PORT 5617
#define BACKLOG 5
#define MAX_SENDLEN 512
ServerObject::ServerObject()
	: m_fdListen(-1)
	, m_mutex()
	, m_pUserObjectManager(nullptr)
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
		auto accpentFun = [this]() 
			{
				while (onAccept());
			};
		EPollObject &epollObject = Single<EPollObject>::Instance();
		if (!epollObject.updateFun(m_fdListen, ET_READ, accpentFun))
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
	std::unique_lock<std::mutex> lk(m_mutex);

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
			assert(false);
			break;
		}
		SOCKET_INFO &sockInfo = iter->second;
		if (sockInfo.sendBytes.empty())
		{
			unsigned int sendLen = innerDoSend(fd, pBuffer, nLen);
			if (sendLen < nLen)
			{
				sockInfo.sendBytes.append(pBuffer + sendLen, nLen - sendLen);
				break;
			}
		}
		else
		{
			sockInfo.sendBytes.append(pBuffer, nLen);
			break;
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

bool ServerObject::onAccept()
{
	std::unique_lock<std::mutex> lk(m_mutex);

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

		auto readFun = [this, acpSock]()
			{
				while (onRead(acpSock));
			};

		EPollObject &epollObject = Single<EPollObject>::Instance();
		if (!epollObject.updateFun(acpSock, ET_READ, readFun))
		{
			LOG(LOG_ERR, "ServerObject::onAccept updateFun errno=%d\n", errno);
			assert(false);
			break;
		}

		m_acceptSocketArray.insert(std::make_pair(acpSock, SOCKET_INFO()));

		lk.unlock();
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

bool ServerObject::onRead(int fd)
{
	std::unique_lock<std::mutex> lk(m_mutex);

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
		ssize_t ret = recv(fd, buf, sizeof(buf), 0);
		if (ret > 0)
		{
			lk.unlock();
			m_pUserObjectManager->notifyRecv(fd, buf, static_cast<unsigned int>(ret));
			lk.lock();
		}
		else
		{
			//ret==0 client close, ret < 0 error
			if (ret < 0)
			{
				if (EAGAIN != errno)
				{
					LOG(LOG_ERR, "ServerObject::onAccept accept errno=%d\n", errno);
				}
			}
			if (0 == m_acceptSocketArray.erase(fd))
			{
				LOG(LOG_ERR, "ServerObject::onAccept 0 == m_acceptSocketArray.erase(fd) failed\n");
			}
			EPollObject &epollObject = Single<EPollObject>::Instance();
			if (!epollObject.removeFun(fd))
			{
				LOG(LOG_ERR, "ServerObject::onAccept !epollObject.removeFun(fd) failed\n");
			}
			lk.unlock();
			m_pUserObjectManager->notifyClose(fd);
			lk.lock();
			if (close(fd) < 0)
			{
				LOG(LOG_ERR, "ServerObject::onAccept close errno=%d\n", errno);
				assert(false);
			}
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

unsigned int ServerObject::innerDoSend(int fd, const char * pBuffer, unsigned int nLen)
{
	ssize_t ret = 0, offset = 0;
	do
	{
		ret = ::send(fd, pBuffer + offset, nLen - offset, 0);
		if (ret > 0)
		{
			offset += ret;
		}
		else if (0 == ret)
		{
			break;
		}
		else
		{
			LOG(LOG_ERR, "ServerObject::innerDoSend send errno=%d\n", errno);
			assert(false);
			break;
		}
	} while (ret > 0 && offset < nLen);

	return static_cast<unsigned int>(offset);
}
