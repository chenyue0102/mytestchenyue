//
// Created by chenyue on 2020/8/20.
//

#ifndef TESTFFMPEG_OPENSLPLAY_H
#define TESTFFMPEG_OPENSLPLAY_H

#include <vector>
#include <mutex>
#include "InterfaceDefine.h"
#include "OpenSLESHelper.h"
#include "RingQueue.h"

class OpenSLPlay : public IAudioPlay{
    friend void onBufferCallback(SLAndroidSimpleBufferQueueItf audioPlay, void *pContext);
public:
    OpenSLPlay();
    ~OpenSLPlay();
public:
    virtual bool setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat);
    virtual bool open();
    virtual bool setPlayState(uint32_t playState);
    virtual uint32_t putData(const void *data, uint32_t size);
    virtual uint32_t getQueuedAudioSize();
    virtual bool close();

private:
    std::mutex mMutex;
    uint32_t mNumChannels;
    uint32_t mSamplesPerSec;
    uint32_t mAudioFormat;
    OpenSLESHelper mOpenSLHelper;
    RingQueue mRingQueue;
    std::vector<uint8_t> mBuffer;
    bool mHavePutFirst;
};


#endif //TESTFFMPEG_OPENSLPLAY_H
