#include "EPollObject.h"
#include <sys/epoll.h>
#include "Log.h"

EPollObject::EPollObject()
	: m_epollfd(-1)
	, m_waitThreadId(0)
	, m_checkThreadId(0)
{
}


EPollObject::~EPollObject()
{
}

bool EPollObject::open()
{
	bool bRes = false;
	int efd = -1;

	do
	{
		if ((efd = epoll_create(1024)) < 0)
		{
			LOG(LOG_ERR, "EPollObject::open epoll_create errno=%d\n", errno);
			break;
		}
		if (0 != pthread_create(&m_waitThreadId, nullptr, &EPollObject::innerWaitThread, this))
		{
			LOG(LOG_ERR, "EPollObject::open pthread_create errno=%d\n", errno);
			break;
		}
		if (0 != pthread_create(&m_checkThreadId, nullptr, &EPollObject::innerWaitThread, this))
		{
			LOG(LOG_ERR, "EPollObject::open pthread_create errno=%d\n", errno);
			break;
		}

		bRes = true;
	} while (false);

	if (!bRes)
	{
		close();
	}
	return bRes;
}

bool EPollObject::close()
{
	return false;
}

void * EPollObject::innerWaitThread(void * arg)
{
	return nullptr;
}

void * EPollObject::innerCheckThread(void * arg)
{
	return nullptr;
}
