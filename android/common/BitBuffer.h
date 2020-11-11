//
// Created by EDZ on 2020/8/31.
//

#ifndef TESTFFMPEG_BITBUFFER_H
#define TESTFFMPEG_BITBUFFER_H

#include <stdint.h>
#include <vector>

class BitBuffer {
public:
    BitBuffer(bool littleEndian);
    ~BitBuffer();

public:
    void put(uint8_t data, size_t bitSize);
    void put64(uint64_t data, size_t bitSize);
    uint8_t get(size_t bitSize);
    uint64_t get64(size_t bitSize);
    uint8_t peek(size_t bitSize);
    uint64_t peek64(size_t bitSize);
    void skip(size_t bitSize);

private:
    void makeBufferSize(size_t bitSize);
private:
    //LE 先写/读缓冲区低位， BE 先写/读缓冲区高位
    bool mLittleEndian;
    size_t mBitLength;
    size_t mReadBitOffset;
    std::vector<uint8_t> mBuffer;
};


#endif //TESTFFMPEG_BITBUFFER_H
