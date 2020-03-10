#include "EPollObject.h"
#include <assert.h>
#include <sys/epoll.h>
#include <unistd.h>	//pipe
#include "Log.h"
#include "typedef.h"


#define PIPE_READ_INDEX 0
#define PIPE_WRITE_INDEX 1
#define EPOLL_WAIT_MS -1
#define EPOLL_WAIT_EVENT_MAX_COUNT 32
EPollObject::EPollObject()
	: m_epollfd(INVALID_HANDLE_VALUE)
	, m_pipe({ INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE })
	, m_mutex()
	, m_epollSize(1024)
	, m_bExit(false)
	, m_waitThread()
	, m_fdEventFun()
{
}


EPollObject::~EPollObject()
{
}

void EPollObject::setEpollSize(int size)
{
	m_epollSize = size;
}

bool EPollObject::init()
{
	bool bRes = false;

	do
	{
		destroy();
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = false;
		if (pipe(m_pipe) < 0){
			LOG(LOG_ERR, "EPollObject::init init pipe errno=%d", errno);
			assert(false);
			break;
		}
		if ((m_epollfd = epoll_create(m_epollSize)) < 0)
		{
			LOG(LOG_ERR, "EPollObject::init epoll_create errno=%d", errno);
			assert(false);
			break;
		}
		m_waitThread = std::thread(&EPollObject::innerWaitThread, this, m_epollSize);

		bRes = true;
	} while (false);

	if (!bRes)
	{
		destroy();
	}
	return bRes;
}

bool EPollObject::destroy()
{
	bool ret = false;

	do{
		{
			std::lock_guard<std::mutex> lk(m_mutex);
			m_bExit = true;
		}
		//管道中,写入1字节,通知epoll_wait退出
		if (m_pipe[PIPE_WRITE_INDEX] >= 0)
		{
			if (write(m_pipe[PIPE_WRITE_INDEX], "0", 1) < 0)
			{
				LOG(LOG_ERR, "EPollObject::destroy write pipe errno=%d", errno);
				assert(false);
			}
		}
		if (m_waitThread.joinable())
		{
			m_waitThread.join();
			std::thread().swap(m_waitThread);
		}
		std::lock_guard<std::mutex> lk(m_mutex);
		if (m_pipe[PIPE_READ_INDEX] >= 0)
		{
			if (close(m_pipe[PIPE_READ_INDEX]) < 0)
			{
				LOG(LOG_ERR, "EPollObject::destroy close pipe errno=%d", errno);
				assert(false);
			}
			if (close(m_pipe[PIPE_WRITE_INDEX]) < 0)
			{
				LOG(LOG_ERR, "EPollObject::destroy close pipe errno=%d", errno);
				assert(false);
			}
			m_pipe[PIPE_READ_INDEX] = m_pipe[PIPE_WRITE_INDEX] = INVALID_HANDLE_VALUE;
		}
		if (m_epollfd >= 0)
		{
			if (close(m_epollfd) < 0)
			{
				LOG(LOG_ERR, "EPollObject::destroy close epoll errno=%d", errno);
				assert(false);
			}
			m_epollfd = INVALID_HANDLE_VALUE;
		}
		m_fdEventFun.clear();
		ret = true;
	}while(false);

	return ret;
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
				LOG(LOG_ERR, "EPollObject::removeFun epoll_ctl errno=%d", errno);
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
			LOG(LOG_ERR, "EPollObject::removeFun epoll_ctl errno=%d", errno);
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
		case ET_ERROR:
			ev.events |= EPOLLRDHUP | EPOLLHUP | EPOLLERR;
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

void EPollObject::innerWaitThread(int epollSize)
{
	const int MaxEvents = std::min(EPOLL_WAIT_EVENT_MAX_COUNT, epollSize);
	epoll_event events[MaxEvents];
	bool bContinue = true;
	int ret = -1;

	while (bContinue)
	{
		ret = epoll_wait(m_epollfd, events, MaxEvents, EPOLL_WAIT_MS);
		std::unique_lock<std::mutex> lk(m_mutex);
		if (m_bExit)
		{
			bContinue = false;
			break;
		}
		if (ret < 0)
		{
			if (EINTR != errno)
			{
				LOG(LOG_ERR, "EPollObject::innerWaitThread epoll_wait errno=%d", errno);
			}
			continue;
		}
		else if (0 == ret)
		{
			LOG(LOG_DEBUG, "EPollObject::innerWaitThread epoll_wait timeout");
			continue;
		}
		for (int i = 0; i < ret; i++)
		{
			int fd = events[i].data.fd;
			if (fd == m_pipe[PIPE_READ_INDEX])
			{
				bContinue = false;
				break;
			}
			//m_fdEventFun内容，在循环中，有可能被修改，随时使用，随时查找
			int flags = events[i].events;
			if ((flags & EPOLLIN)
				&& m_fdEventFun.find(fd) != m_fdEventFun.end()
				&& m_fdEventFun[fd].find(ET_READ) != m_fdEventFun[fd].end())
			{
				std::function<void()> f = m_fdEventFun[fd][ET_READ];
				lk.unlock();
				f();
				lk.lock();
			}
			if ((flags & EPOLLOUT)
				&& m_fdEventFun.find(fd) != m_fdEventFun.end()
				&& m_fdEventFun[fd].find(ET_WRITE) != m_fdEventFun[fd].end())
			{
				std::function<void()> f = m_fdEventFun[fd][ET_WRITE];
				lk.unlock();
				f();
				lk.lock();
			}
			bool bError = (!(events[i].events & EPOLLIN)) && ((flags & EPOLLHUP) || (flags & EPOLLRDHUP) || (flags & EPOLLERR));
			if (bError
				&& m_fdEventFun.find(fd) != m_fdEventFun.end()
				&& m_fdEventFun[fd].find(ET_ERROR) != m_fdEventFun[fd].end())
			{
				bool bEpollHup = flags & EPOLLHUP;
				bool bEopllRDHup = flags & EPOLLRDHUP;
				bool bEopollErr = flags & EPOLLERR;
				std::function<void()> f = m_fdEventFun[fd][ET_ERROR];
				lk.unlock();
				f();
				lk.lock();
			}
		}
	}
}

