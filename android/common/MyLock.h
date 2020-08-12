//
// Created by chenyue on 2020/8/5.
//

#ifndef TESTCAMERA_MYLOCK_H
#define TESTCAMERA_MYLOCK_H

#include <atomic>

class MyLock {

public:
	void lock() {
		while (mLock.test_and_set());
	}
	void unlock() {
		mLock.clear();
	}

private:
    std::atomic_flag mLock = ATOMIC_FLAG_INIT;
};


#endif //TESTCAMERA_MYLOCK_H
