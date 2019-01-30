#include "UserObjectBase.h"
#include <type_traits>
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
#include "Single.h"
#include "ServerObject.h"

template < typename T, size_t N >
size_t _countof(T(&arr)[N])
{
	return std::extent< T[N] >::value;
}

UserObjectBase::UserObjectBase()
	: m_mutex()
	, m_objectStatus(ObjectStatusAccept)
	, m_ulRef(0)
	, m_fd(-1)
	, m_port(0)
	, m_ipAddress()
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
	m_port = ntohs(addr.sin_port);
	inet_ntop(AF_INET, &addr.sin_addr, m_ipAddress, sizeof(m_ipAddress));
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

		if (m_recvBuffer.size() >= sizeof(MSGHEADER))
		{
			MSGHEADER header = { 0 };
			memcpy(&header, m_recvBuffer.data(), sizeof(MSGHEADER));
			header = Net2Host(header);
			if (m_recvBuffer.size() >= header.dwMsgLen)
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

bool UserObjectBase::sendMsg(const char *pBuffer, unsigned int nLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		if (ObjectStatusRecv != m_objectStatus)
		{
			LOG(LOG_ERR, "UserObjectBase::sendMsg m_objectStatus failed\n");
			break;
		}
		if (nullptr == pBuffer || nLen < sizeof(MSGHEADER))
		{
			LOG(LOG_ERR, "UserObjectBase::sendMsg param failed\n");
			assert(false);
			break;
		}
		MSGHEADER header = { 0 };
		memcpy(&header, pBuffer, sizeof(header));
		if (header.dwMsgLen != nLen)
		{
			LOG(LOG_ERR, "UserObjectBase::sendMsg len failed\n");
			assert(false);
			break;
		}
		MSGHEADER netHeader = Host2Net(header);
		memcpy(const_cast<char*>(pBuffer), &netHeader, sizeof(netHeader));

		ServerObject &serverObject = Single<ServerObject>::Instance();
		if (!serverObject.send(m_fd, pBuffer, nLen))
		{
			memcpy(const_cast<char*>(pBuffer), &header, sizeof(header));
			LOG(LOG_ERR, "UserObjectBase::sendMsg send failed\n");
			assert(false);
			break;
		}
		memcpy(const_cast<char*>(pBuffer), &header, sizeof(header));

		bRet = true;
	} while (false);
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
						tempMsgArray.push_back(std::string(m_recvBuffer.data(), header.dwMsgLen));
					}
					m_recvBuffer.erase(0, header.dwMsgLen);
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
		if (!onMsg(oneMsg.data(), static_cast<unsigned int>(oneMsg.size())))
		{
			bError = true;
			break;
		}
	}
	if (bError)
	{
		ServerObject &serverObject = Single<ServerObject>::Instance();
		serverObject.closeSocket(getSocket());
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

bool UserObjectBase::onMsg(const char *pBuffer, unsigned int nLen)
{
	if (nullptr == pBuffer || nLen < sizeof(MSGHEADER))
	{
		LOG(LOG_ERR, "UserObjectBase::onMsg param failed\n");
		assert(false);
		return false;
	}
	MSGHEADER header = { 0 };
	memcpy(&header, pBuffer, sizeof(header));
	if (header.dwMsgLen != nLen)
	{
		LOG(LOG_ERR, "UserObjectBase::onMsg dwMsgLen failed\n");
		assert(false);
		return false;
	}
	switch (header.dwMsgID)
	{
	case PID_GET_IPADDRESS:
	{
		MSG_GET_IPADDRESS_ACK ack = { 0 };
		ack.header.dwMsgLen = sizeof(ack);
		ack.header.dwMsgID = PID_GET_IPADDRESS | PID_ACK;
		strncpy(ack.szIpAddress, m_ipAddress, _countof(ack.szIpAddress));
		sendMsg((char*)&ack, sizeof(ack));
		return false;
		break;
	}
	case PID_SEND_BIG_DATA:
	{
		MSG_BIG_DATA_REQ *pBigData = (MSG_BIG_DATA_REQ*)pBuffer;
		assert(pBigData->header.dwMsgLen == sizeof(MSG_BIG_DATA_REQ));
		assert(pBigData->header.dwMsgLen == sizeof(MSG_BIG_DATA_REQ));
		for (auto &x : pBigData->a)
		{
			assert('a' == x);
		}
		for (auto &x : pBigData->b)
		{
			assert('b' == x);
		}
		for (auto &x : pBigData->d)
		{
			assert('d' == x);
		}
		for (auto &x : pBigData->e)
		{
			assert('e' == x);
		}
		for (auto &x : pBigData->f)
		{
			assert('f' == x);
		}

		MSG_BIG_DATA_ACK ack = { 0 };
		ack.header.dwMsgID = PID_SEND_BIG_DATA | PID_ACK;
		ack.header.dwMsgLen = sizeof(ack);
		sendMsg((char*)&ack, sizeof(ack));
		break;
	}
	case PID_GET_BIG_DATA:
	{
		MSG_GET_BIG_DATA_REQ req = { 0 };
		memcpy(&req, pBuffer, sizeof(MSG_GET_BIG_DATA_REQ));

		MSG_GET_BIG_DATA_ACK *pBigData = new MSG_GET_BIG_DATA_ACK();
		pBigData->header.dwMsgLen = sizeof(MSG_GET_BIG_DATA_ACK);
		pBigData->header.dwMsgID = PID_GET_BIG_DATA | PID_ACK;
		memset(pBigData->a, 'a', sizeof(pBigData->a));
		memset(pBigData->b, 'b', sizeof(pBigData->b));
		memset(pBigData->c, 'c', sizeof(pBigData->c));
		memset(pBigData->d, 'd', sizeof(pBigData->d));
		memset(pBigData->e, 'e', sizeof(pBigData->e));
		memset(pBigData->f, 'f', sizeof(pBigData->f));
		sendMsg((char*)pBigData, sizeof(MSG_GET_BIG_DATA_ACK));

		return false;
		break;
	}
	default:
		break;
	}
	return true;
}
