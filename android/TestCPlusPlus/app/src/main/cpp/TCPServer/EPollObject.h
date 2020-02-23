#ifndef _EPOLLOBJECT_H_
#define _EPOLLOBJECT_H_
#include <map>
#include <functional>
#include <mutex>
#include <thread>

enum EventType
{
	ET_READ,
	ET_WRITE,
	ET_ERROR,
};
class EPollObject
{
public:
	EPollObject();
	~EPollObject();
public:
	void setEpollSize(int size);
	bool init();
	bool destroy();
	bool updateFun(int fd, EventType eventType, std::function<void()> fun);
	bool removeFun(int fd, EventType eventType);
	bool removeFun(int fd);
private:
	bool innerEpollUpdate(int fd, int epoll_op);
private:
	void innerWaitThread(int epollSize);
private:
	typedef std::map<EventType, std::function<void()>> EVENT_FUN_ARRAY;
	int m_epollfd;
	int m_pipe[2];				//关闭的时候,给这个pipe写入数据通知推出
	std::mutex m_mutex;
	int m_epollSize;
	volatile bool m_bExit;
	std::thread m_waitThread;
	//key fd
	std::map<int, EVENT_FUN_ARRAY> m_fdEventFun;
};
#endif
