//
// Created by chenyue on 2020/8/31.
//

#include "BitBuffer.h"
#include <algorithm>
#include <assert.h>

#define MASK_BIT_COUNT 0b00000111

BitBuffer::BitBuffer(bool littleEndian)
    : mLittleEndian(littleEndian)
    , mBitLength(0)
    , mReadBitOffset(0)
    , mBuffer()
{
    
}

BitBuffer::~BitBuffer() {

}

void BitBuffer::put(uint8_t data, size_t bitSize) {
    assert(bitSize <= 8);
    makeBufferSize(mBitLength + bitSize);

    size_t index = mBitLength >> 3;
    size_t curBitCount = mBitLength & MASK_BIT_COUNT;
    uint8_t &n = mBuffer.at(index);
    if (mLittleEndian){
        //先写低位，后写高位
        size_t storeCount = (std::min)(8 - curBitCount, bitSize);
        uint16_t mask = (1 << storeCount) - 1;
        uint8_t storeValue = (mask & data) << curBitCount;
        n |= storeValue;
        if (storeCount != bitSize){
            uint8_t &n2 = mBuffer.at(index + 1);
            data >>= storeCount;
            n2 = data;
        }
        mBitLength += bitSize;
    }else{
        //先写高位，再写低位
        size_t storeCount = (std::min)(8 - curBitCount, bitSize);
        uint16_t mask = (1 << storeCount) - 1;
        uint8_t storeValue = (mask & data) << (8 - curBitCount - storeCount);
        n |= storeValue;
        if (storeCount != bitSize){
            uint8_t &n2 = mBuffer.at(index + 1);
            data >>= storeCount;
            n2 = data << (8 - (bitSize - storeCount));
        }
        mBitLength += bitSize;
    }
}

void BitBuffer::put64(uint64_t data, size_t bitSize) {
    while(bitSize > 0){
        size_t tmpBitSize = (std::min)((size_t)8, bitSize);
        put(data & 0xff, tmpBitSize);
        bitSize -= tmpBitSize;
        data >>= tmpBitSize;
    }
}

uint8_t BitBuffer::get(size_t bitSize) {
    makeBufferSize(mReadBitOffset + bitSize);

    size_t index = mReadBitOffset >> 3;
    size_t curBitCount = mReadBitOffset & MASK_BIT_COUNT;
    uint8_t ret = 0;
    uint8_t n = mBuffer.at(index);

    if (mLittleEndian) {
        //先读低位，后读高位
        size_t readCount = (std::min)(bitSize, 8 - curBitCount);
        uint16_t mask = (1 << readCount) - 1;
        uint8_t readValue = (n >> curBitCount) & mask;
        ret = readValue;
        if (readCount != bitSize) {
            uint8_t n2 = mBuffer.at(index + 1);
            n2 &= (1 << (bitSize - readCount)) - 1;
            ret |= n2 << readCount;
        }
        mReadBitOffset += bitSize;
    }
    else {
        assert(false);
    }
    return ret;
}

uint64_t BitBuffer::get64(size_t bitSize) {
    makeBufferSize(mReadBitOffset + bitSize);
    uint64_t ret = 0;
    size_t surplusSize = bitSize;
    while (surplusSize > 0) {
        size_t tmpBitSize = (std::min)(surplusSize, (size_t)8);
        uint8_t n = get(tmpBitSize);
        uint64_t tmpN = n;
        tmpN <<= (bitSize - surplusSize);
        ret |= tmpN;
        surplusSize -= tmpBitSize;
    }
    return ret;
}

uint8_t BitBuffer::peek(size_t bitSize) {
    uint8_t ret = get(bitSize);
    mReadBitOffset -= bitSize;
    return ret;
}

uint64_t BitBuffer::peek64(size_t bitSize) {
    uint64_t ret = get64(bitSize);
    mReadBitOffset -= bitSize;
    return ret;
}

void BitBuffer::skip(size_t bitSize) {
    mReadBitOffset += bitSize;
}

void BitBuffer::makeBufferSize(size_t bitSize) {
    size_t newCount = bitSize >> 3;
    size_t surplusCount = ((bitSize & MASK_BIT_COUNT) > 0) ? 1 : 0;
    newCount += surplusCount;
    if (mBuffer.size() < newCount){
        mBuffer.resize(newCount, 0);
    }
}
