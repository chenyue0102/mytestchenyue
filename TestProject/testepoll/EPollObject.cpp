#include "EPollObject.h"
#include <assert.h>
#include <sys/epoll.h>
#include "Log.h"

EPollObject::EPollObject()
	: m_epollfd(-1)
	, m_mutex()
	, m_waitThreadId(0)
	, m_checkThreadId(0)
	, m_fdEventFun()
{
}


EPollObject::~EPollObject()
{
}

bool EPollObject::init()
{
	bool bRes = false;

	do
	{
		if ((m_epollfd = epoll_create(1024)) < 0)
		{
			LOG(LOG_ERR, "EPollObject::init epoll_create errno=%d\n", errno);
			assert(false);
			break;
		}
		if (0 != pthread_create(&m_waitThreadId, nullptr, &EPollObject::innerStaticWaitThread, this))
		{
			LOG(LOG_ERR, "EPollObject::init pthread_create errno=%d\n", errno);
			assert(false);
			break;
		}

		bRes = true;
	} while (false);

	if (!bRes)
	{
		destory();
	}
	return bRes;
}

bool EPollObject::destory()
{
	return false;
}

bool EPollObject::updateFun(int fd, EventType eventType, std::function<void()> fun)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	int epoll_op = (m_fdEventFun.find(fd) == m_fdEventFun.end()) ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;
	m_fdEventFun[fd][eventType] = fun;
	return innerEpollUpdate(fd, epoll_op);
}

bool EPollObject::removeFun(int fd, EventType eventType)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		auto iter = m_fdEventFun.find(fd);
		if (iter == m_fdEventFun.end())
		{
			LOG(LOG_DEBUG, "EPollObject::removeFun iter == m_fdEventFun.end() failed");
			assert(false);
			break;
		}
		EVENT_FUN_ARRAY &eventFunArray = iter->second;
		if (0 == eventFunArray.erase(eventType))
		{
			LOG(LOG_DEBUG, "EPollObject::removeFun 0 == eventFunArray.erase(eventType) failed");
			assert(false);
			break;
		}
		if (0 == eventFunArray.size())
		{
			m_fdEventFun.erase(iter);
			if (epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, 0) < 0)
			{
				LOG(LOG_ERR, "EPollObject::removeFun epoll_ctl errno=%d\n", errno);
				assert(false);
				break;
			}
		}
		else
		{
			if (!innerEpollUpdate(fd, EPOLL_CTL_MOD))
			{
				LOG(LOG_ERR, "EPollObject::removeFun !innerEpollUpdate failed");
				assert(false);
				break;
			}
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool EPollObject::removeFun(int fd)
{
	std::lock_guard<std::mutex> lk(m_mutex);

	bool bRet = false;

	do
	{
		auto iter = m_fdEventFun.find(fd);
		if (iter == m_fdEventFun.end())
		{
			LOG(LOG_ERR, "EPollObject::removeFun iter == m_fdEventFun.end() failed");
			assert(false);
			break;
		}
		m_fdEventFun.erase(iter);
		if (epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, 0) < 0)
		{
			LOG(LOG_ERR, "EPollObject::removeFun epoll_ctl errno=%d\n", errno);
			assert(false);
			break;
		}
		bRet = true;
	} while (false);
	
	return bRet;
}

bool EPollObject::innerEpollUpdate(int fd, int epoll_op)
{
	epoll_event ev = { 0 };
	ev.data.fd = fd;
	for (auto &eventPair : m_fdEventFun[fd])
	{
		switch (eventPair.first)
		{
		case ET_READ:
			ev.events |= EPOLLIN;
			break;
		case ET_WRITE:
			ev.events |= EPOLLOUT;
			break;
		default:
			LOG(LOG_ERR, "EPollObject::innerEpollUpdate event=%d failed", eventPair.first);
			assert(false);
			break;
		}
	}
	ev.events |= EPOLLET;
	return (epoll_ctl(m_epollfd, epoll_op, fd, &ev) == 0);
}

void * EPollObject::innerStaticWaitThread(void * arg)
{
	EPollObject *pObject = reinterpret_cast<EPollObject*>(arg);
	if (nullptr != pObject)
	{
		pObject->innerWaitThread();
	}
	else
	{
		LOG(LOG_ERR, "EPollObject::innerWaitThread nullptr != pObject");
	}
	return nullptr;
}

void EPollObject::innerWaitThread()
{
	const int MaxEvents = 32;
	const int Timeout = 10000;
	epoll_event events[MaxEvents];
	bool bContinue = true;
	int ret = -1;

	while (bContinue)
	{
		ret = epoll_wait(m_epollfd, events, MaxEvents, Timeout);
		if (ret < 0)
		{
			if (EINTR != errno)
			{
				LOG(LOG_ERR, "EPollObject::innerWaitThread epoll_wait errno=%d\n", errno);
			}
			continue;
		}
		else if (0 == ret)
		{
			LOG(LOG_DEBUG, "EPollObject::innerWaitThread epoll_wait timeout");
			continue;
		}
		std::unique_lock<std::mutex> lk(m_mutex);
		for (int i = 0; i < ret; i++)
		{
			int fd = events[i].data.fd;
			//m_fdEventFun内容，在循环中，有可能被修改，随时使用，随时查找
			int flags = events[i].events;
			if ((flags | EPOLLIN)
				&& m_fdEventFun.find(fd) != m_fdEventFun.end()
				&& m_fdEventFun[fd].find(ET_READ) != m_fdEventFun[fd].end())
			{
				std::function<void()> f = m_fdEventFun[fd][ET_READ];
				lk.unlock();
				f();
				lk.lock();
			}
			if ((flags | EPOLLOUT)
				&& m_fdEventFun.find(fd) != m_fdEventFun.end()
				&& m_fdEventFun[fd].find(ET_WRITE) != m_fdEventFun[fd].end())
			{
				std::function<void()> f = m_fdEventFun[fd][ET_WRITE];
				lk.unlock();
				f();
				lk.lock();
			}
			if (flags | EPOLLHUP | EPOLLRDHUP)
			{

			}
		}
	}
}

//void * EPollObject::innerCheckThread(void * arg)
//{
//	return nullptr;
//}
