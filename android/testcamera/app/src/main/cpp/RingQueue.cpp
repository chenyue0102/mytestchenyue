//
// Created by chenyue on 2020/7/21.
//

#include "RingQueue.h"
#include <stdlib.h>
#include <algorithm>
#include <assert.h>

#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
RingQueue::RingQueue(uint32_t bufSize) :mutex(), bufferLen(bufSize), readIndex(0), writeIndex(0), buffer(nullptr){
    assert(is_power_of_2(bufSize));
    buffer = new uint8_t[bufSize];
}

RingQueue::~RingQueue() {
    delete []buffer;
}

uint32_t RingQueue::getBufferSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return bufferLen;
}

uint32_t RingQueue::getFreeSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return bufferLen - innerGetDataSize();
}

uint32_t RingQueue::getDataSize() const {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerGetDataSize();
}

uint32_t RingQueue::put(const void *data, uint32_t dataLen) {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerPut(data, dataLen);
}

uint32_t RingQueue::get(void *data, uint32_t dataLen) {
    std::lock_guard<RING_MUTEX> lk(mutex);

    return innerGet(data, dataLen);
}

uint32_t RingQueue::innerGetDataSize() const {
    return (writeIndex - readIndex);
}

uint32_t RingQueue::innerPut(const void *data, uint32_t dataLen) {
    assert(nullptr != data && dataLen > 0);
    dataLen = (std::min)(dataLen, bufferLen - writeIndex + readIndex);
    uint32_t len = (std::min)(dataLen, bufferLen - (writeIndex & (bufferLen - 1)));
    memcpy(buffer + (writeIndex & (writeIndex - 1)), data, len);
    memcpy(buffer, reinterpret_cast<const uint8_t*>(data) + len, dataLen - len);
    return dataLen;
}

uint32_t RingQueue::innerGet(void *data, uint32_t dataLen) {
    assert(nullptr != data && dataLen > 0);
    dataLen = (std::min)(dataLen, writeIndex - readIndex);
    uint32_t  len = (std::min)(dataLen, bufferLen - (readIndex & (bufferLen - 1)));
    memcpy(data, buffer + (readIndex & (readIndex - 1)), len);
    memcpy(reinterpret_cast<uint8_t*>(data) + len, buffer, dataLen - len);
    readIndex += dataLen;
    return dataLen;
}
