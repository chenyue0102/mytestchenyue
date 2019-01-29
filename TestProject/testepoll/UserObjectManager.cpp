#include "UserObjectManager.h"
#include "UserObjectBase.h"
#include "Log.h"
#include "Single.h"
#include "TaskPool.h"


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
		SmartPtr<UserObjectBase> pUserObject(new UserObjectBase);
		pUserObject->setSockInfo(fd, addr);
		m_fdObjectArray.insert(std::make_pair(fd, pUserObject));
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyAccept fd failed\n");
	}
}

void UserObjectManager::notifyClose(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	auto iter = m_fdObjectArray.find(fd);
	if (iter != m_fdObjectArray.end())
	{
		SmartPtr<UserObjectBase> pTempObject = iter->second;
		auto processCloseFun = [pTempObject]()mutable->void
			{
				pTempObject->notifyClose();
			};
		m_fdObjectArray.erase(iter);

		CTaskPool &taskPool = Single<CTaskPool>::Instance();
		taskPool.AddOrderTask(processCloseFun, pTempObject->getTaskGroupId());
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyClose erase failed\n");
	}
}

void UserObjectManager::notifyRecv(int fd, const char * pBuffer, unsigned int recvLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	auto iter = m_fdObjectArray.find(fd);
	if (iter != m_fdObjectArray.end())
	{
		iter->second->notifyRecv(pBuffer, recvLen);
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyRecv find failed\n");
	}
}
