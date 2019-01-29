#ifndef _EPOLLOBJECT_H_
#define _EPOLLOBJECT_H_
#include <map>
#include <functional>
#include <mutex>
#include <pthread.h>

enum EventType
{
	ET_NONE = 0,
	ET_READ,
};
class EPollObject
{
public:
	EPollObject();
	~EPollObject();
public:
	bool open();
	bool close();
	bool updateFun(int fd, EventType eventType, std::function<void()> fun);
	bool removeFun(int fd, EventType eventType);
private:
	bool innerEpollUpdate(int fd, int epoll_op);
private:
	static void* innerStaticWaitThread(void *arg);
	void innerWaitThread();
	//static void* innerCheckThread(void *arg);
private:
	typedef std::map<EventType, std::function<void()>> EVENT_FUN_ARRAY;
	int m_epollfd;
	std::mutex m_mutex;
	pthread_t m_waitThreadId;
	pthread_t m_checkThreadId;
	//key fd
	std::map<int, EVENT_FUN_ARRAY> m_fdEventFun;
};
#endif
