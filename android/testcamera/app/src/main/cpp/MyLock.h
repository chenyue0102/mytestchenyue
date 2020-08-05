//
// Created by chenyue on 2020/8/5.
//

#ifndef TESTCAMERA_MYLOCK_H
#define TESTCAMERA_MYLOCK_H

#include <atomic>

class MyLock {
public:
    MyLock();

public:
    void lock();
    void unlock();

private:
    std::atomic_flag mLock;
};


#endif //TESTCAMERA_MYLOCK_H
