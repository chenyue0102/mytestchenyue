#include "UserObjectBasePrivate.h"
#include <assert.h>
#include <memory>
#include <string.h>
#include "Log.h"
#include "../include/ProtocolBase.h"
#include "UserObjectBase.h"
#include "ServerObject.h"
#include "SmartPtr.h"
#include "TaskPool.h"
#include "Single.h"


UserObjectBasePrivate::UserObjectBasePrivate(UserObjectBase &userObjectBase)
	: m_userObjectBase(userObjectBase)
	, m_mutex()
	, m_objectStatus(ObjectStatusAccept)
	, m_recvBuffer()
{
}


UserObjectBasePrivate::~UserObjectBasePrivate()
{
}

void UserObjectBasePrivate::notifyRecv(const char * pBuffer, unsigned int recvLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	innerNotifyRecv(pBuffer, recvLen);
}

void UserObjectBasePrivate::notifyClose()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_objectStatus = ObjectStatusClose;
}

void UserObjectBasePrivate::asyncDoRecvMsg()
{
	std::list<std::string> tempMsgArray;
	if (!getMsgArray(tempMsgArray))
	{
		return;
	}
	if (tempMsgArray.empty())
	{
		return;
	}

	bool bError = false;
	for (auto &oneMsg : tempMsgArray)
	{
		if (!m_userObjectBase.onMsg(oneMsg.data(), static_cast<unsigned int>(oneMsg.size())))
		{
			bError = true;
			break;
		}
	}
	if (bError)
	{
		ServerObject &serverObject = Single<ServerObject>::Instance();
		serverObject.closeSocket(m_userObjectBase.m_fd, true);
		stopRecv();
	}
}

ObjectStatus UserObjectBasePrivate::getObjectStatus() const
{
	std::lock_guard<std::mutex> lk(m_mutex);

	return m_objectStatus;
}

bool UserObjectBasePrivate::getMsgArray(std::list<std::string>& msgArray)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	if (ObjectStatusRecv == m_objectStatus)
	{
		while (m_recvBuffer.size() >= sizeof(MSGHEADER))
		{
			MSGHEADER header = { 0 };
			memcpy(&header, m_recvBuffer.data(), sizeof(MSGHEADER));
			header = Net2Host(header);
			if (m_recvBuffer.size() >= header.dwMsgLen)
			{
				memcpy(&*m_recvBuffer.begin(), &header, sizeof(MSGHEADER));//包头转换成本地结构体
				if (0 != header.dwMsgID)//msgid为0，表示心跳
				{
					msgArray.push_back(std::string(m_recvBuffer.data(), header.dwMsgLen));
				}
				m_recvBuffer.erase(0, header.dwMsgLen);
			}
			else
			{
				break;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void UserObjectBasePrivate::stopRecv()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_objectStatus = ObjectStatusClose;
}

void UserObjectBasePrivate::innerNotifyRecv(const char * pBuffer, unsigned int recvLen)
{
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

	if (nullptr != pBuffer && 0 != recvLen)
	{
		m_recvBuffer.append(pBuffer, recvLen);

		if (m_recvBuffer.size() >= sizeof(MSGHEADER))
		{
			MSGHEADER header = { 0 };
			memcpy(&header, m_recvBuffer.data(), sizeof(MSGHEADER));
			header = Net2Host(header);
			if (m_recvBuffer.size() >= header.dwMsgLen)
			{
				SmartPtr<UserObjectBase> pTempObject(&m_userObjectBase);
				auto processRecvFun = [pTempObject, this]()mutable->void
				{
					pTempObject->AddRef();//使得UserObjectBase容器不被释放，从而保证Private类有效
					pTempObject->Release();
					asyncDoRecvMsg();
				};
				CTaskPool &taskPool = Single<CTaskPool>::Instance();
				taskPool.AddOrderTask(processRecvFun, m_userObjectBase.getTaskGroupId());
			}
		}
	}
	else
	{
		LOG(LOG_ERR, "UserObjectBase::notifyRecv pBuffer failed");
	}
}
