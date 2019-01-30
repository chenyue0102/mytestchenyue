#include "UserObjectBase.h"
#include <assert.h>
#include <memory.h>
#include <list>
#include <string>
#include <unistd.h>
#include "../include/ProtocolBase.h"
#include "Log.h"
#include "TaskPool.h"
#include "Single.h"
#include "SmartPtr.h"



UserObjectBase::UserObjectBase()
	: m_mutex()
	, m_objectStatus(ObjectStatusAccept)
	, m_ulRef(0)
	, m_fd(-1)
	, m_addr()
	, m_recvBuffer()
	, m_tLastMsgTime(time(nullptr))
{
	LOG(LOG_DBG, "UserObjectBase::UserObjectBase\n");
}


UserObjectBase::~UserObjectBase()
{
	LOG(LOG_DBG, "UserObjectBase::~UserObjectBase\n");
}

void UserObjectBase::setSockInfo(int fd, const sockaddr_in & addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_fd = fd;
	m_addr = addr;
}

void UserObjectBase::notifyRecv(const char * pBuffer, unsigned int recvLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	
	if (ObjectStatusAccept == m_objectStatus)
	{
		m_objectStatus = ObjectStatusRecv;
	}
	if (ObjectStatusRecv != m_objectStatus)
	{
		LOG(LOG_ERR, "UserObjectBase::notifyRecv m_objectStatus=%d failed", m_objectStatus);
		assert(false);
		return;
	}

	m_tLastMsgTime = time(nullptr);

	if (nullptr != pBuffer && 0 != recvLen)
	{
		m_recvBuffer.append(pBuffer, recvLen);

		if (m_recvBuffer.size() >= sizeof(MSGHEADERNET))
		{
			MSGHEADERNET net = { 0 };
			memcpy(&net, m_recvBuffer.data(), sizeof(MSGHEADERNET));
			MSGHEADERLOCAL local = Net2Local(net);
			if (m_recvBuffer.size() >= local.dwMsgLen)
			{
				SmartPtr<UserObjectBase> pTempObject(this);
				auto processRecvFun = [pTempObject]()mutable->void
				{
					if (pTempObject)
					{
						pTempObject->InnerDoRecvMsg();
					}
				};
				CTaskPool &taskPool = Single<CTaskPool>::Instance();
				taskPool.AddOrderTask(processRecvFun, getTaskGroupId());
			}
		}
	}
	else
	{
		LOG(LOG_ERR, "UserObjectBase::notifyRecv pBuffer failed");
	}
}

void UserObjectBase::notifyClose()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_objectStatus = ObjectStatusClose;
}

int UserObjectBase::getSocket() const
{
	std::lock_guard<std::mutex> lk(m_mutex);

	return m_fd;
}

bool UserObjectBase::sendMsg(MSGHEADERLOCAL * pHeader)
{
	bool bRet = false;


	return bRet;
}

std::size_t UserObjectBase::getTaskGroupId() const
{
	return reinterpret_cast<std::size_t>(this);
}

void UserObjectBase::InnerDoRecvMsg()
{
	std::list<std::string> tempMsgArray;
	{
		std::lock_guard<std::mutex> lk(m_mutex);

		if (ObjectStatusRecv == m_objectStatus)
		{
			while (m_recvBuffer.size() >= sizeof(MSGHEADERNET))
			{
				MSGHEADERNET net = { 0 };
				memcpy(&net, m_recvBuffer.data(), sizeof(MSGHEADERNET));
				MSGHEADERLOCAL local = Net2Local(net);
				if (m_recvBuffer.size() >= local.dwMsgLen)
				{
					memcpy(&*m_recvBuffer.begin(), &local, sizeof(MSGHEADERLOCAL));//包头转换成本地结构体
					if (0 != local.dwMsgID)//msgid为0，表示心跳
					{
						tempMsgArray.push_back(std::string(m_recvBuffer.data(), local.dwMsgLen));
					}
					m_recvBuffer.erase(0, local.dwMsgLen);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			return;
		}
	}
	bool bError = false;
	for (auto &oneMsg : tempMsgArray)
	{
		if (!onMsg((MSGHEADERLOCAL*)oneMsg.data()))
		{
			bError = true;
			break;
		}
	}
	if (bError)
	{
		int fd = getSocket();
		if (close(fd) < 0)
		{
			LOG(LOG_ERR, "UserObjectBase::InnerDoRecvMsg close errno=%d\n", errno);
		}
	}
}

unsigned long UserObjectBase::AddRef(void)
{
	return ++m_ulRef;
}

unsigned long UserObjectBase::Release(void)
{
	unsigned long ulResult = --m_ulRef;
	if (0 == ulResult)
	{
		delete this;
	}
	return ulResult;
}

bool UserObjectBase::onMsg(MSGHEADERLOCAL *pHeader)
{
	switch (pHeader->dwMsgID)
	{
	case 1:
		break;
	default:
		break;
	}
	return true;
}
