#include "UserObjectManager.h"
#include "UserObjectBase.h"
#include "Log.h"


UserObjectManager::UserObjectManager()
	: m_mutex()
	, m_fdObjectArray()
{
}


UserObjectManager::~UserObjectManager()
{
}

void UserObjectManager::notifyAccept(int fd, sockaddr_in & addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	if (m_fdObjectArray.find(fd) == m_fdObjectArray.end())
	{
		std::unique_ptr<UserObjectBase> pUserObject(new UserObjectBase);
		pUserObject->setSockInfo(fd, addr);
		m_fdObjectArray.insert(std::make_pair(fd, std::move(pUserObject)));
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyAccept fd failed\n");
	}
}

void UserObjectManager::notifyClose(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	if (0 == m_fdObjectArray.erase(fd))
	{
		LOG(LOG_ERR, "TcpContextManager::notifyClose erase failed\n");
	}
}

void UserObjectManager::notifyRecv(int fd, const char * pBuffer, unsigned int recvLen)
{
}
