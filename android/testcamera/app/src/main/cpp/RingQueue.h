//
// Created by chenyue on 2020/7/21.
//

#ifndef TESTMEDIA_RINGQUEUE_H
#define TESTMEDIA_RINGQUEUE_H
#include <stdint.h>
#if 1
#include "MyLock.h"
#define RING_MUTEX MyLock
#else
#include <mutex>
#define RING_MUTEX std::mutex
#endif

class RingQueue {
public:
    RingQueue(uint32_t bufSize);
    ~RingQueue();

public:
    //总空间
    uint32_t getBufferSize()const;
    //空闲空间
    uint32_t getFreeSize()const;
    //数据空间
    uint32_t getDataSize()const;
    uint32_t put(const void *data, size_t size);
    uint32_t get(void *data, size_t size);

private:
    uint32_t innerGetDataSize()const;
    uint32_t innerPut(const void *data, size_t size);
    uint32_t innerGet(void *data, size_t size);

private:
    mutable RING_MUTEX mutex;
    uint32_t mask;
    uint32_t readIndex;
    uint32_t writeIndex;
    uint8_t * buffer;
};


#endif //TESTMEDIA_RINGQUEUE_H
