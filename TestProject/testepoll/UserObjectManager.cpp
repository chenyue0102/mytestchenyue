#include "UserObjectManager.h"
#include <assert.h>
#include "ServerObject.h"
#include "UserObjectBase.h"
#include "Log.h"
#include "Single.h"
#include "TaskPool.h"

//检查第一个包接收超时，单位秒
#define CHECK_RECV_FIRST_MSG 5
#define CHECK_HEART_BEAT (60 * 1)
#define HEART_BEAT_MOD 10

UserObjectManager::UserObjectInfo::UserObjectInfo()
	: status(FirstMsgStatusAccept)
	, tLastMsgTime(time(nullptr))
	, pUserObject()
{

}

UserObjectManager::UserObjectManager()
	: m_mutex()
	, m_timerThead()
	, m_cv()
	, m_fdObjectArray()
	, m_waitFirstMsgFD()
	, m_recvMsgFD()
{
}


UserObjectManager::~UserObjectManager()
{
}

bool UserObjectManager::init()
{
	m_timerThead = std::thread(&UserObjectManager::timerProc, this);
	return true;
}

bool UserObjectManager::destroy()
{
	if (m_timerThead.joinable())
	{
		m_timerThead.join();
	}
	return true;
}

void UserObjectManager::notifyAccept(int fd, sockaddr_in & addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	if (m_fdObjectArray.find(fd) == m_fdObjectArray.end())
	{
		SmartPtr<UserObjectBase> pUserObject(new UserObjectBase(fd, addr));
		UserObjectInfo objInfo;
		objInfo.status = FirstMsgStatusAccept;
		objInfo.tLastMsgTime = time(nullptr);
		objInfo.pUserObject = pUserObject;
		m_fdObjectArray.insert(std::make_pair(fd, objInfo));

		m_waitFirstMsgFD[objInfo.tLastMsgTime].insert(fd);
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyAccept fd failed\n");
		assert(false);
	}
}

void UserObjectManager::notifyClose(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	auto iter = m_fdObjectArray.find(fd);
	if (iter != m_fdObjectArray.end())
	{
		UserObjectInfo &objInfo = iter->second;
		if (FirstMsgStatusAccept == objInfo.status)
		{
			innerClearWaitFD(objInfo.tLastMsgTime, fd);
		}
		else if (FirstMsgStatusRecv == objInfo.status)
		{
			innerClearRecvFD(objInfo.tLastMsgTime, fd);
		}

		CTaskPool &taskPool = Single<CTaskPool>::Instance();
		SmartPtr<UserObjectBase> pTempObject = objInfo.pUserObject;
		auto processFun = [pTempObject]()mutable->void
			{
				pTempObject->notifyClose();
			};
		taskPool.AddOrderTask(processFun, pTempObject->getTaskGroupId());

		m_fdObjectArray.erase(iter);
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyClose erase failed\n");
		assert(false);
	}
}

void UserObjectManager::notifyRecv(int fd, const char * pBuffer, unsigned int recvLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	auto iter = m_fdObjectArray.find(fd);
	if (iter != m_fdObjectArray.end())
	{
		time_t tCur = time(nullptr);
		tCur -= (tCur % HEART_BEAT_MOD);
		UserObjectInfo &objInfo = iter->second;
		if (FirstMsgStatusAccept == objInfo.status)
		{
			objInfo.status = FirstMsgStatusRecv;
			innerClearWaitFD(objInfo.tLastMsgTime, fd);
			objInfo.tLastMsgTime = tCur;
			m_recvMsgFD[tCur].insert(fd);
		}

		if (FirstMsgStatusRecv == objInfo.status
			&& tCur != objInfo.tLastMsgTime)
		{
			innerClearRecvFD(objInfo.tLastMsgTime, fd);
			objInfo.tLastMsgTime = tCur;
			m_recvMsgFD[objInfo.tLastMsgTime].insert(fd);
		}

		std::string strTempData(pBuffer, recvLen);
		CTaskPool &taskPool = Single<CTaskPool>::Instance();
		SmartPtr<UserObjectBase> pTempObject = objInfo.pUserObject;
		auto processFun = [pTempObject, strTempData]()mutable->void
		{
			pTempObject->notifyRecv(strTempData.data(), strTempData.size());
		};
		taskPool.AddOrderTask(processFun, pTempObject->getTaskGroupId());
	}
	else
	{
		LOG(LOG_ERR, "TcpContextManager::notifyRecv find failed\n");
		assert(false);
	}
}

void UserObjectManager::innerClearWaitFD(time_t tLastMsgTime, int fd)
{
	do
	{
		auto iterWait = m_waitFirstMsgFD.find(tLastMsgTime);
		if (iterWait == m_waitFirstMsgFD.end())
		{
			LOG(LOG_ERR, "UserObjectManager::notifyRecv iterWait == m_waitFirstMsgFD.end()\n");
			assert(false);
			break;
		}
		std::set<int> &waitFDArray = iterWait->second;
		if (0 == waitFDArray.erase(fd))
		{
			LOG(LOG_ERR, "UserObjectManager::notifyRecv 0 == waitFDArray.erase(fd)\n");
			assert(false);
		}
		if (waitFDArray.empty())
		{
			m_waitFirstMsgFD.erase(iterWait);
		}
	} while (false);
}

void UserObjectManager::innerClearRecvFD(time_t tLastMsgTime, int fd)
{
	do
	{
		auto iterRecv = m_recvMsgFD.find(tLastMsgTime);
		if (iterRecv == m_recvMsgFD.end())
		{
			LOG(LOG_ERR, "UserObjectManager::innerClearRecvFD iterWait == m_recvMsgFD.end()\n");
			assert(false);
			break;
		}
		std::set<int> &recvFDArray = iterRecv->second;
		if (0 == recvFDArray.erase(fd))
		{
			LOG(LOG_ERR, "UserObjectManager::innerClearRecvFD 0 == recvFDArray.erase(fd)\n");
			assert(false);
		}
		if (recvFDArray.empty())
		{
			m_recvMsgFD.erase(iterRecv);
		}
	} while (false);
}

void UserObjectManager::timerProc()
{
	ServerObject &serverObject = Single<ServerObject>::Instance();
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		std::cv_status ret = m_cv.wait_for(lk, std::chrono::seconds(1));
		if (std::cv_status::no_timeout == ret)
		{
			break;
		}
		std::set<int> closefd;
		time_t tCur = time(nullptr);
		{
			time_t tWaitFirst = tCur - CHECK_RECV_FIRST_MSG;
			auto iterWait = m_waitFirstMsgFD.begin();
			while (iterWait != m_waitFirstMsgFD.end())
			{
				if (iterWait->first < tWaitFirst)
				{
					for (auto &onefd : iterWait->second)
					{
						auto iter = m_fdObjectArray.find(onefd);
						if (iter != m_fdObjectArray.end())
						{
							iter->second.status = FirstMsgStatusClosing;
						}
						else
						{
							assert(false);
							LOG(LOG_ERR, "UserObjectManager::timerProc iter == m_fdObjectArray.end()\n");
						}
						closefd.insert(onefd);
					}
					iterWait = m_waitFirstMsgFD.erase(iterWait);
				}
				else
				{
					break;
				}
			}
		}
		
		{
			time_t tRecv = tCur - (tCur % HEART_BEAT_MOD) - CHECK_HEART_BEAT;
			auto iterRecv = m_recvMsgFD.begin();
			while (iterRecv != m_recvMsgFD.end())
			{
				if (iterRecv->first < tRecv)
				{
					for (auto &onefd : iterRecv->second)
					{
						auto iter = m_fdObjectArray.find(onefd);
						if (iter != m_fdObjectArray.end())
						{
							iter->second.status = FirstMsgStatusClosing;
						}
						else
						{
							assert(false);
							LOG(LOG_ERR, "UserObjectManager::timerProc iter == m_fdObjectArray.end()\n");
						}
						closefd.insert(onefd);
					}
					iterRecv = m_recvMsgFD.erase(iterRecv);
				}
				else
				{
					break;
				}
			}
		}

		lk.unlock();
		for (auto onefd : closefd)
		{
			serverObject.closeSocket(onefd, true);
		}
	}
}

