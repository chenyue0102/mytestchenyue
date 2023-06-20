#include "simplemutex.h"
#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

#ifdef WIN32
struct SimpleMutex::SimpleMutexData{
    CRITICAL_SECTION cs;
    SimpleMutexData()
    {
        InitializeCriticalSection(&cs);
    }
    ~SimpleMutexData()
    {
        DeleteCriticalSection(&cs);
    }
    void lock()
    {
        EnterCriticalSection(&cs);
    }
    void unlock()
    {
        LeaveCriticalSection(&cs);
    }
};
#else
struct SimpleMutex::SimpleMutexData
{
    pthread_mutex_t mutex;
    SimpleMutexData(){
        pthread_mutex_init(&mutex, NULL);
    }
    ~SimpleMutexData(){
        pthread_mutex_destroy(&mutex);
    }
    void lock(){
        pthread_mutex_lock(&mutex);
    }
    void unlock(){
        pthread_mutex_unlock(&mutex);
    }
};
#endif

SimpleMutex::SimpleMutex()
    : mData(new SimpleMutexData())
{
}

SimpleMutex::~SimpleMutex()
{
    delete mData;
}

void SimpleMutex::lock()
{
    mData->lock();
}

void SimpleMutex::unlock()
{
    mData->unlock();
}

SimpleMutexLocker::SimpleMutexLocker(SimpleMutex & mutex)
	: mMutex(mutex)
{
	mMutex.lock();
}

SimpleMutexLocker::~SimpleMutexLocker()
{
	mMutex.unlock();
}
