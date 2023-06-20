#ifndef _simplethread_h_
#define _simplethread_h_

class SimpleThread
{
public:
    typedef void*(*THREADFUN)(void *argument);
public:
	SimpleThread(THREADFUN fun, void *arg);
	~SimpleThread();

public:
	void join();

private:
	struct SimpleThreadData;
	SimpleThreadData *mData;
};

#endif
