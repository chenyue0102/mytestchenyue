//
// Created by chenyue on 2020/7/21.
//

#include "RingQueue.h"
#include <stdlib.h>
#include <algorithm>
#include <assert.h>

#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
RingQueue::RingQueue(uint32_t bufSize) :mutex(), mask(bufSize - 1), readIndex(0), writeIndex(0), buffer(nullptr){
    assert(is_power_of_2(bufSize));
    buffer = new uint8_t[bufSize];
}

RingQueue::~RingQueue() {
    delete []buffer;
}

uint32_t RingQueue::getBufferSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return (mask + 1);
}

uint32_t RingQueue::getFreeSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return (mask + 1) - innerGetDataSize();
}

uint32_t RingQueue::getDataSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerGetDataSize();
}

uint32_t RingQueue::put(const void *data, uint32_t size) {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerPut(data, size);
}

uint32_t RingQueue::get(void *data, uint32_t size) {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerGet(data, size);
}

uint32_t RingQueue::innerGetDataSize() const {
    return (writeIndex - readIndex);
}

uint32_t RingQueue::innerPut(const void *data, uint32_t size) {
    assert(nullptr != data && size > 0);
	uint32_t bufferLen = mask + 1;
	size = (std::min)(size, bufferLen - writeIndex + readIndex);
    uint32_t len = (std::min)(size, bufferLen - (writeIndex & mask));
    memcpy(buffer + (writeIndex & mask), data, len);
    memcpy(buffer, reinterpret_cast<const uint8_t*>(data) + len, size - len);
	writeIndex += size;
    return size;
}

uint32_t RingQueue::innerGet(void *data, uint32_t size) {
    assert(nullptr != data && size > 0);
	uint32_t bufferLen = mask + 1;
	size = (std::min)(size, writeIndex - readIndex);
    uint32_t  len = (std::min)(size, bufferLen - (readIndex & mask));
    memcpy(data, buffer + (readIndex & mask), len);
    memcpy(reinterpret_cast<uint8_t*>(data) + len, buffer, size - len);
    readIndex += size;
    return size;
}
