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
#include "lame.h"

#define RING_BUFFER_SIZE (1024 * 1024 * 2)
#define DEFAULT_MP3_BRATE 128

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
    int brate;//mp3 brate

    AudioRecordLogicData():format(AudioRecordLogic::NONE), ringQueue(RING_BUFFER_SIZE), exit(false), brate(DEFAULT_MP3_BRATE){}
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
    const int BUFFER_LENGTH = 1024;
    uint8_t *szBuffer = new uint8_t[BUFFER_LENGTH];
    uint32_t totalCount = 0;
    while(true){
        std::unique_lock<std::mutex> lk(data.mtx);
        data.cv.wait(lk, [&data]()->bool{return data.exit || data.ringQueue.getDataSize() > 0;});
        if (data.exit){
            SC(Log).i("AudioRecordLogic::writeWAVThread exit");
            break;
        }
        std::size_t getSize = data.ringQueue.get(szBuffer, BUFFER_LENGTH);
        lk.unlock();
        if (fwrite(szBuffer, 1, getSize, file) != getSize){
            SC(Log).e("AudioRecordLogic::writeWAVThread fwrite failed");
            assert(false);
            break;
        }
        totalCount += getSize;
    }
    delete []szBuffer;
    szBuffer = nullptr;

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

static void writeMp3Thread(AudioRecordLogicData &data){
    std::string filePath;
    FILE *file = nullptr;
    {
        std::lock_guard<std::mutex> lk(data.mtx);
        filePath = data.filePath;
    }
    if (nullptr == (file = fopen(filePath.c_str(), "wb+"))){
        SC(Log).e("AudioRecordLogic::startRecord fopen failed");
        assert(false);
        return;
    }

    lame_t lameClient = lame_init();

    if (nullptr == lameClient){
        fclose(file);
        SC(Log).e("AudioRecordLogic::writeMp3Thread nullptr == lameClient failed");
        assert(false);
        return;
    }
    uint16_t numChannels = 0;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;
    int brate = 0;
    {
        std::lock_guard<std::mutex> lk(data.mtx);
        numChannels = data.numChannels;
        sampleRate = data.sampleRate;
        bitsPerSample = data.bitsPerSample;
        brate = data.brate;
    }
    lame_set_in_samplerate(lameClient, sampleRate);
    lame_set_out_samplerate(lameClient, sampleRate);
    lame_set_num_channels(lameClient, numChannels);
    lame_set_brate(lameClient, brate);
    lame_set_mode(lameClient, STEREO);
    lame_set_quality(lameClient, 5);
    lame_init_params(lameClient);

    const int CHANNEL_BUFFER_SIZE = 1152 * sizeof(short);
    uint8_t *leftBuffer = nullptr, *rightBuffer = nullptr, *szBuffer = nullptr, *mp3Buffer = nullptr;

    leftBuffer = new uint8_t[CHANNEL_BUFFER_SIZE];
    rightBuffer = new uint8_t[CHANNEL_BUFFER_SIZE];
    szBuffer = new uint8_t[CHANNEL_BUFFER_SIZE * 2];
    mp3Buffer = new uint8_t[CHANNEL_BUFFER_SIZE * 4];
    while(true){
        std::unique_lock<std::mutex> lk(data.mtx);
        data.cv.wait(lk, [&data]()->bool{return data.exit || data.ringQueue.getDataSize() > 0;});
        if (data.exit){
            SC(Log).i("AudioRecordLogic::writeMp3Thread exit");
            break;
        }
        std::size_t getSize = data.ringQueue.get(szBuffer, CHANNEL_BUFFER_SIZE * 2);
        lk.unlock();

        size_t i = 0;
        while (i + sizeof(short) * 2 < getSize){
            memcpy(leftBuffer + i / 2, szBuffer + i, sizeof(short));
            memcpy(rightBuffer + i / 2, szBuffer + i + sizeof(short), sizeof(short));
            i += sizeof(short) * 2;
        }
        int writeSize = lame_encode_buffer(lameClient, (short*)leftBuffer, (short*)rightBuffer, getSize / (2 * sizeof(short)), mp3Buffer, CHANNEL_BUFFER_SIZE * 4);
        if (writeSize > 0){
            if (fwrite(mp3Buffer, 1, writeSize, file) != writeSize){
                SC(Log).e("AudioRecordLogic::writeMp3Thread fwrite failed");
                assert(false);
                break;
            }
        }
    }
    fclose(file);

    delete []leftBuffer;
    delete []rightBuffer;
    delete []szBuffer;
    delete []mp3Buffer;
}
AudioRecordLogic::AudioRecordLogic(): mData(new AudioRecordLogicData()) {

}

AudioRecordLogic::~AudioRecordLogic() {
    stopRecord();
    delete mData;
    mData = nullptr;
}

void AudioRecordLogic::setOutputFormat(int format) {
    std::lock_guard<std::mutex> lk(mData->mtx);

    mData->format = format;
}

void AudioRecordLogic::setMp3BRate(int brate){
    std::lock_guard<std::mutex> lk(mData->mtx);

    mData->brate = brate;
}

void AudioRecordLogic::setInputStreamInfo(uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample){
    std::lock_guard<std::mutex> lk(mData->mtx);

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
        std::lock_guard<std::mutex> lk(mData->mtx);

        mData->exit = false;
        mData->filePath = filePath;
        if (WAV == mData->format){
            mData->thd = std::thread(&writeWAVThread, std::ref(*mData));
        } else if(MP3 == mData->format){
            mData->thd = std::thread(&writeMp3Thread, std::ref(*mData));
        }else{
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

