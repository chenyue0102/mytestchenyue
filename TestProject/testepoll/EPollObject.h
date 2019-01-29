#ifndef _EPOLLOBJECT_H_
#define _EPOLLOBJECT_H_
#include <pthread.h>

class EPollObject
{
public:
	EPollObject();
	~EPollObject();
public:
	bool open();
	bool close();
private:
	static void* innerWaitThread(void *arg);
	static void* innerCheckThread(void *arg);
private:
	int m_epollfd;
	pthread_t m_waitThreadId;
	pthread_t m_checkThreadId;
};
#endif
