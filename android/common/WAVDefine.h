//
// Created by chenyue on 2020/8/4.
//

#ifndef TESTCAMERA_WAVDEFINE_H
#define TESTCAMERA_WAVDEFINE_H

#include <stdint.h>

//小端对齐
struct wav_fmt_header_t{
    char chunkID[4]; //"fmt " = 0x20746D66
    uint32_t chunkSize; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};
//Wav Header
struct wav_header_t
{
    char chunkID[4]; //"RIFF" = 0x46464952
    uint32_t chunkSize; //文件长度-8
    char format[4]; //"WAVE" = 0x45564157
    wav_fmt_header_t fmt;
};

//Chunks
struct chunk_t
{
    char chunkID[4];        //"data" = 0x61746164
    uint32_t chunkSize;     //Chunk data bytes
};

#endif //TESTCAMERA_WAVDEFINE_H
