#include "simplethread.h"
#include <assert.h>
#ifdef WIN32
#include <thread>
#else
#include <pthread.h>
#endif


struct SimpleThread::SimpleThreadData
{
#ifdef WIN32
	SimpleThreadData(SimpleThread::THREADFUN fun, void *arg)
		: mThread(fun, arg)
	{

	}

	void join() {
		if (mThread.joinable()) {
			mThread.join();
		}
	}
	std::thread mThread;
#else
	SimpleThreadData(SimpleThread::THREADFUN fun, void *arg)
        : mThread()
	{
		int ret = pthread_create(&mThread, NULL, fun, arg);
		assert(0 == ret);
	}
	
	void join() {
		if (0 != mThread) {
			void *v = NULL;
			int ret = pthread_join(mThread, &v);
			assert(0 == ret);
			mThread = 0;
		}
	}
	pthread_t mThread;
#endif
};
SimpleThread::SimpleThread(THREADFUN fun, void * arg)
	: mData(new SimpleThreadData(fun, arg))
{
}

SimpleThread::~SimpleThread()
{
	join();
	delete mData;
	mData = NULL;
}

void SimpleThread::join()
{
	mData->join();
}
