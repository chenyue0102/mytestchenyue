//
// Created by EDZ on 2020/8/4.
//

#include "AudioRecordLogic.h"
#include <stdio.h>
#include <assert.h>
#include <thread>
#include "RingQueue.h"
#include "WAVDefine.h"
#include "Single.h"
#include "MacroDefine.h"
#include "Log.h"
#include "byteswap.h"

#define RING_BUFFER_SIZE (1024 * 1024 * 2)

struct AudioRecordLogicData{
    int format;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint16_t bitsPerSample;
    std::string filePath;
    RingQueue ringQueue;
    std::mutex mtx;
    std::thread thd;
    std::condition_variable cv;
    volatile bool exit;

    AudioRecordLogicData():format(AudioRecordLogic::NONE), ringQueue(RING_BUFFER_SIZE), exit(false){}
};

static bool adjustPCMWavHeader(FILE *file, size_t dataCount, uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample){
    bool ret = false;

    do{
        if (nullptr == file || 0 == dataCount || 0 == numChannels || 0 == sampleRate || 0 == bitsPerSample){
            SC(Log).e("AudioRecordLogic::adjustPCMWavHeader param failed");
            assert(false);
            break;
        }
        wav_header_t wavHeader = {0};
        memcpy(wavHeader.chunkID, "RIFF", 4);
        wavHeader.chunkSize = ByteSwap::htole32(sizeof(wav_header_t) - 8 + sizeof(chunk_t) + dataCount);
        memcpy(wavHeader.format, "WAVE", 4);
        memcpy(wavHeader.fmt.chunkID, "fmt ", 4);
        wavHeader.fmt.chunkSize = ByteSwap::htole32(sizeof(wav_fmt_header_t) - 8);
        wavHeader.fmt.audioFormat = ByteSwap::htole16(0x0001);
        wavHeader.fmt.numChannels = ByteSwap::htole16(numChannels);
        wavHeader.fmt.sampleRate = ByteSwap::htole32(sampleRate);
        uint32_t byteRate = sampleRate * numChannels * bitsPerSample / 8;
        wavHeader.fmt.byteRate = ByteSwap::htole32(byteRate);
        uint16_t blockAlign = bitsPerSample * numChannels / 8;
        wavHeader.fmt.blockAlign = ByteSwap::htole16(blockAlign);
        wavHeader.fmt.bitsPerSample = ByteSwap::htole16(bitsPerSample);
        if (0 != fseek(file, 0, SEEK_SET)){
            SC(Log).e("AudioRecordLogic::adjustPCMWavHeader fseek failed");
            assert(false);
            break;
        }
        if (fwrite(&wavHeader, 1, sizeof(wavHeader), file) != sizeof(wavHeader)){
            SC(Log).e("AudioRecordLogic::adjustPCMWavHeader fwrite wavHeader failed");
            assert(false);
            break;
        }
        chunk_t chunk = {0};
        memcpy(chunk.chunkID, "data", 4);
        chunk.chunkSize = ByteSwap::htole32(dataCount);
        if (fwrite(&chunk, 1, sizeof(chunk), file) != sizeof(chunk)){
            SC(Log).e("AudioRecordLogic::adjustPCMWavHeader fwrite chunk failed");
            assert(false);
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

static void writeWAVThread(AudioRecordLogicData &data){
    FILE *file = nullptr;
    std::string filePath;
    {
        std::lock_guard<std::mutex> lk(data.mtx);
        filePath = data.filePath;
    }
    if (nullptr == (file = fopen(filePath.c_str(), "wb+"))){
        SC(Log).e("AudioRecordLogic::startRecord fopen failed");
        assert(false);
        return;
    }
    if (0 != fseek(file, sizeof(wav_header_t) + sizeof(chunk_t), SEEK_SET)){
        fclose(file);
        SC(Log).e("AudioRecordLogic::startRecord fseek failed");
        assert(false);
        return;
    }
    char szBuffer[1024] = {0};
    uint32_t totalCount = 0;
    while(true){
        std::unique_lock<std::mutex> lk(data.mtx);
        data.cv.wait(lk, [&data]()->bool{return data.exit || data.ringQueue.getDataSize() > 0;});
        if (data.exit){
            SC(Log).i("AudioRecordLogic::writeWAVThread exit");
            break;
        }
        std::size_t getSize = data.ringQueue.get(szBuffer, sizeof(szBuffer));
        if (fwrite(szBuffer, 1, getSize, file) != getSize){
            SC(Log).e("AudioRecordLogic::writeWAVThread fwrite failed");
            assert(false);
            break;
        }
        totalCount += getSize;
    }
    if (nullptr != file){
        uint16_t numChannels;
        uint32_t sampleRate;
        uint16_t bitsPerSample;
        {
            std::lock_guard<std::mutex> lk(data.mtx);
            numChannels = data.numChannels;
            sampleRate = data.sampleRate;
            bitsPerSample = data.bitsPerSample;
        }
        adjustPCMWavHeader(file, totalCount, numChannels, sampleRate, bitsPerSample);
        fclose(file);
        file = nullptr;
    }
}
AudioRecordLogic::AudioRecordLogic(): mData(new AudioRecordLogicData()) {

}

AudioRecordLogic::~AudioRecordLogic() {
    stopRecord();
    delete mData;
    mData = nullptr;
}

void AudioRecordLogic::setFileFormat(int format, uint16_t numChannels, uint32_t sampleRate,
                                     uint16_t bitsPerSample) {
    mData->format = format;
    mData->numChannels = numChannels;
    mData->sampleRate = sampleRate;
    mData->bitsPerSample = bitsPerSample;
}

bool AudioRecordLogic::startRecord(const char *filePath) {
    bool ret = false;

    do{
        stopRecord();
        if (nullptr == filePath){
            SC(Log).e("AudioRecordLogic::startRecord nullptr == filePath failed");
            assert(false);
            break;
        }
        {
            std::lock_guard<std::mutex> lk(mData->mtx);
            mData->exit = false;
            mData->filePath = filePath;
        }
        if (WAV == mData->format){
            mData->thd = std::thread(&writeWAVThread, std::ref(*mData));
        } else{
            SC(Log).e("AudioRecordLogic::startRecord format:%d failed", mData->format);
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

void AudioRecordLogic::stopRecord() {
    {
        std::lock_guard<std::mutex> lk(mData->mtx);
        mData->exit = true;
        mData->cv.notify_one();
    }
    if (mData->thd.joinable()){
        mData->thd.join();
    }
}

size_t AudioRecordLogic::appendData(const void *data, size_t len) {
    std::lock_guard<std::mutex> lk(mData->mtx);
    size_t putSize = mData->ringQueue.put(data, len);
    mData->cv.notify_one();
    return putSize;
}

