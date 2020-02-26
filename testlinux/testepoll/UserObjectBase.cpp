#include "UserObjectBase.h"
#include <type_traits>
#include <assert.h>
#include <memory.h>
#include <list>
#include <string>
#include <unistd.h>
#include "ProtocolBase.h"
#include "Log.h"
#include "SmartPtr.h"
#include "Single.h"
#include "ServerObject.h"
#include "UserObjectBasePrivate.h"

template < typename T, size_t N >
size_t _countof(T(&arr)[N])
{
	return std::extent< T[N] >::value;
}
//m_port = ntohs(addr.sin_port);
//inet_ntop(AF_INET, &addr.sin_addr, m_ipAddress, sizeof(m_ipAddress));
UserObjectBase::UserObjectBase(int fd, const sockaddr_in &addr)
	: m_ulRef(0)
	, m_fd(fd)
	, m_addr(addr)
	, m_pUserObjectBasePrivate(new UserObjectBasePrivate(*this))
{
	LOG(LOG_DBG, "UserObjectBase::UserObjectBase\n");
}


UserObjectBase::~UserObjectBase()
{
	LOG(LOG_DBG, "UserObjectBase::~UserObjectBase\n");
	delete m_pUserObjectBasePrivate;
	m_pUserObjectBasePrivate = nullptr;
}

void UserObjectBase::notifyRecv(const char * pBuffer, unsigned int recvLen)
{
	return m_pUserObjectBasePrivate->notifyRecv(pBuffer, recvLen);
}

void UserObjectBase::notifyClose()
{
	return m_pUserObjectBasePrivate->notifyClose();
}

bool UserObjectBase::sendMsg(const char *pBuffer, unsigned int nLen)const
{
	bool bRet = false;

	do
	{
		if (ObjectStatusRecv != m_pUserObjectBasePrivate->getObjectStatus())
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
			//assert(false);
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
		inet_ntop(AF_INET, &m_addr.sin_addr, ack.szIpAddress, sizeof(ack.szIpAddress));
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
		delete pBigData;
		return false;
		break;
	}
	default:
		break;
	}
	return true;
}
