#ifndef _simpleringqueue_h_
#define _simpleringqueue_h_
#include <stdint.h>

class SimpleRingQueue {
public:
	SimpleRingQueue(uint32_t bufSize);
    ~SimpleRingQueue();

public:
    //总空间
    uint32_t getBufferSize()const;
    //空闲空间
    uint32_t getFreeSize()const;
    //数据空间
    uint32_t getDataSize()const;
    uint32_t put(const void *data, uint32_t size);
    uint32_t get(void *data, uint32_t size);
    void clear();

private:
    uint32_t innerGetDataSize()const;
    uint32_t innerPut(const void *data, uint32_t size);
    uint32_t innerGet(void *data, uint32_t size);

private:
    uint32_t mask;
    uint32_t readIndex;
    uint32_t writeIndex;
    uint8_t * buffer;
};

#endif
