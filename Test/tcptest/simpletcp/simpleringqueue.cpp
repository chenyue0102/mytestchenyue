#include "simpleringqueue.h"
#include <string.h>
#include <assert.h>
#include <algorithm>

#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
SimpleRingQueue::SimpleRingQueue(uint32_t bufSize) : mask(bufSize - 1), readIndex(0), writeIndex(0), buffer(NULL){
    assert(is_power_of_2(bufSize));
    buffer = new uint8_t[bufSize];
}

SimpleRingQueue::~SimpleRingQueue() {
    delete []buffer;
}

uint32_t SimpleRingQueue::getBufferSize() const {
    return (mask + 1);
}

uint32_t SimpleRingQueue::getFreeSize() const {
    return (mask + 1) - innerGetDataSize();
}

uint32_t SimpleRingQueue::getDataSize() const {
    return innerGetDataSize();
}

uint32_t SimpleRingQueue::put(const void *data, uint32_t size) {
    return innerPut(data, size);
}

uint32_t SimpleRingQueue::get(void *data, uint32_t size) {
    return innerGet(data, size);
}

void SimpleRingQueue::clear() {
    readIndex = writeIndex = 0;
}

uint32_t SimpleRingQueue::innerGetDataSize() const {
    return (writeIndex - readIndex);
}

uint32_t SimpleRingQueue::innerPut(const void *data, uint32_t size) {
    assert(NULL != data && size > 0);
	uint32_t bufferLen = mask + 1;
	size = (std::min)(size, bufferLen - writeIndex + readIndex);
    uint32_t len = (std::min)(size, bufferLen - (writeIndex & mask));
    memcpy(buffer + (writeIndex & mask), data, len);
    memcpy(buffer, reinterpret_cast<const uint8_t*>(data) + len, size - len);
	writeIndex += size;
    return size;
}

uint32_t SimpleRingQueue::innerGet(void *data, uint32_t size) {
    assert(NULL != data && size > 0);
	uint32_t bufferLen = mask + 1;
	size = (std::min)(size, writeIndex - readIndex);
    uint32_t  len = (std::min)(size, bufferLen - (readIndex & mask));
    memcpy(data, buffer + (readIndex & mask), len);
    memcpy(reinterpret_cast<uint8_t*>(data) + len, buffer, size - len);
    readIndex += size;
    return size;
}
