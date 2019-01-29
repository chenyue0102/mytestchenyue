#include "UserObjectBase.h"
#include "Log.h"


UserObjectBase::UserObjectBase()
	: m_fd(-1)
	, m_addr()
	, m_recvBuffer()
{
}


UserObjectBase::~UserObjectBase()
{
}

void UserObjectBase::setSockInfo(int fd, const sockaddr_in & addr)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	m_fd = fd;
	m_addr = addr;
}

void UserObjectBase::notifyRecv(int fd, const char * pBuffer, unsigned int recvLen)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	if (nullptr != pBuffer && 0 != recvLen)
	{
		m_recvBuffer.append(pBuffer, recvLen);
	}
	else
	{
		LOG(LOG_ERR, "UserObjectBase::notifyRecv pBuffer failed");
	}
}
