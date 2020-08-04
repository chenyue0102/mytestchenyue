//
// Created by chenyue on 2020/7/21.
//

#include "RingQueue.h"
#include <stdlib.h>
#include <mutex>
#include <algorithm>
#include <assert.h>
#include "MacroDefine.h"

#define REFALL \
    REFM(mutex); \
    REFM(bufferLen); \
    REFM(readIndex); \
    REFM(writeIndex); \
    REFM(buffer); \
    REFM(isFull)

struct RingQueueData{
    mutable std::mutex mutex;
    size_t bufferLen;
    size_t readIndex;
    size_t writeIndex;
    unsigned char * buffer;
    bool isFull;
};
RingQueue::RingQueue(size_t bufSize) :mData(new RingQueueData()){
    mData->bufferLen = bufSize;
    mData->buffer = new unsigned char[bufSize];
}

RingQueue::~RingQueue() {
    delete []mData->buffer;
    delete mData;
    mData = nullptr;
}

size_t RingQueue::getBufferSize() const {
    std::lock_guard<std::mutex> lk(mData->mutex);

    return mData->bufferLen;
}

size_t RingQueue::getFreeSize() const {
    std::lock_guard<std::mutex> lk(mData->mutex);

    return innerGetFreeSize();
}

size_t RingQueue::getDataSize() const {
    std::lock_guard<std::mutex> lk(mData->mutex);

    return mData->bufferLen - innerGetFreeSize();
}

size_t RingQueue::put(const void *data, size_t dataLen) {
    std::lock_guard<std::mutex> lk(mData->mutex);

    return innerPut(data, dataLen);
}

size_t RingQueue::get(void *data, size_t dataLen) {
    std::lock_guard<std::mutex> lk(mData->mutex);

    return innerGet(data, dataLen);
}

size_t RingQueue::innerGetFreeSize() const {
    REFALL;
    size_t freeSize = 0;
    if (!isFull){
        if (writeIndex >= readIndex){
            freeSize = bufferLen - (writeIndex - readIndex);
        }else{
            freeSize = readIndex - writeIndex;
        }
    }
    return freeSize;
}

size_t RingQueue::innerPut(const void *data, size_t dataLen) {
    REFALL;
    size_t putSize = 0;
    if (dataLen > 0 && nullptr != data && !isFull){
        if (writeIndex >= readIndex){
            size_t tmpPutSize = (std::min)(dataLen, bufferLen - writeIndex);
            memcpy(buffer + writeIndex, data, tmpPutSize);
            putSize += tmpPutSize;
            writeIndex += tmpPutSize;
            if (writeIndex >= bufferLen){
                writeIndex = 0;
            }
            if (putSize < dataLen){
                assert(readIndex >= writeIndex);
                tmpPutSize = (std::min)(readIndex - writeIndex, dataLen - putSize);
                memcpy(buffer + writeIndex, reinterpret_cast<const unsigned char*>(data) + putSize, tmpPutSize);
                putSize += tmpPutSize;
                writeIndex += tmpPutSize;
            }
        }else{
            putSize = (std::min)(dataLen, readIndex - writeIndex);
            memcpy(buffer + writeIndex, data, putSize);
            writeIndex += putSize;
        }
        isFull = (writeIndex == readIndex);
    }
    assert(putSize > 0);
    return putSize;
}

size_t RingQueue::innerGet(void *data, size_t dataLen) {
    REFALL;
    size_t getSize = 0;
    if (dataLen > 0 && nullptr != data && (writeIndex != readIndex || isFull)){
        if (readIndex >= writeIndex){
            size_t tmpGetSize = (std::min)(dataLen, bufferLen - readIndex);
            memcpy(data, buffer + readIndex, tmpGetSize);
            getSize += tmpGetSize;
            readIndex += tmpGetSize;
            if (readIndex >= bufferLen){
                readIndex = 0;
            }
            if (getSize < dataLen){
                assert(writeIndex >= readIndex);
                tmpGetSize = (std::min)(dataLen - getSize, writeIndex - readIndex);
                memcpy(reinterpret_cast<unsigned char*>(data) + getSize, buffer + readIndex, tmpGetSize);
                getSize += tmpGetSize;
                readIndex += tmpGetSize;
            }
        }else{
            getSize = (std::min)(dataLen, writeIndex - readIndex);
            memcpy(data, buffer + readIndex, getSize);
            readIndex += getSize;
        }
        isFull = false;
    }
    assert(getSize > 0);
    return getSize;
}
