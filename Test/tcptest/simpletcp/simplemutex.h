#ifndef _simplemutex_h_
#define _simplemutex_h_

class SimpleMutex {
public:
	SimpleMutex();
	~SimpleMutex();

public:
	void lock();
	void unlock();

    struct SimpleMutexData;
    SimpleMutexData *mData;
};

class SimpleMutexLocker
{
public:
	SimpleMutexLocker(SimpleMutex &mutex);
	~SimpleMutexLocker();

private:
	SimpleMutex &mMutex;
};

#endif
