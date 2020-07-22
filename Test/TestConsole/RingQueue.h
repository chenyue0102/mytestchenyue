//
// Created by chenyue on 2020/7/21.
//

#ifndef TESTMEDIA_RINGQUEUE_H
#define TESTMEDIA_RINGQUEUE_H
#include <stddef.h>

struct RingQueueData;
class RingQueue {
public:
    RingQueue(size_t bufSize);
    ~RingQueue();

public:
    //总空间
    size_t getBufferSize()const;
    //空闲空间
    size_t getFreeSize()const;
    //数据空间
    size_t getDataSize()const;
    size_t put(const void *data, size_t dataLen);
    size_t get(void *data, size_t dataLen);

private:
    size_t innerGetFreeSize()const;
    size_t innerPut(const void *data, size_t dataLen);
    size_t innerGet(void *data, size_t dataLen);

private:
    mutable RingQueueData *mData;
};


#endif //TESTMEDIA_RINGQUEUE_H
