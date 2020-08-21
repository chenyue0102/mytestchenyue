//
// Created by chenyue on 2020/8/20.
//

#include "OpenSLPlay.h"
#include "EnumDefine.h"

void onBufferCallback(SLAndroidSimpleBufferQueueItf audioPlay, void *pContext){
    OpenSLPlay *play = reinterpret_cast<OpenSLPlay*>(pContext);
    if (nullptr != play){
        std::lock_guard<std::mutex> lk(play->mMutex);
        uint32_t len = play->mRingQueue.get(play->mBuffer.data(), 1024);
        if (len > 0){
            (*audioPlay)->Enqueue(audioPlay, play->mBuffer.data(), len);
        }else{
            play->mHavePutFirst = false;
        }
    }
}
OpenSLPlay::OpenSLPlay()
        : mMutex()
        , mNumChannels(0)
        , mSamplesPerSec(0)
        , mAudioFormat(0)
        , mRingQueue(1024 * 1024 * 2)
        , mBuffer(1024)
        , mHavePutFirst(false)
{

}

OpenSLPlay::~OpenSLPlay() {

}

bool OpenSLPlay::setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat) {
    std::lock_guard<std::mutex> lk(mMutex);

    mNumChannels = numChannels;
    mSamplesPerSec = samplesPerSec;
    mAudioFormat = audioFormat;
    return true;
}

bool OpenSLPlay::open() {
    std::lock_guard<std::mutex> lk(mMutex);

    bool b = mOpenSLHelper.createEngine();
    b = mOpenSLHelper.createOutputMix();
    SLDataLocator_AndroidSimpleBufferQueue bufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};

    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            2,
            (SLuint32)(mSamplesPerSec * 1000),
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN,
    };
    SLDataSource slDataSource = {&bufferQueue, &pcm};
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, mOpenSLHelper.getOutputMixObject()};
    SLDataSink slDataSink = {&outputMix, nullptr};
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    b = mOpenSLHelper.createPlayer(slDataSource, slDataSink, 3, ids, req);
    SLAndroidSimpleBufferQueueItf slBufferQueue = mOpenSLHelper.getPlayBufferQueue();
    mOpenSLHelper.registerPlayBufferQueueCallback(&onBufferCallback, this);
    return true;
}

inline uint32_t convertPlayState(uint32_t playState){
    switch (playState){
        case EPlayStatePlaying:
            return SL_PLAYSTATE_PLAYING;
        case EPlayStatePause:
            return SL_PLAYSTATE_PAUSED;
        case EPlayStateStopped:
            return SL_PLAYSTATE_STOPPED;
        default:
            assert(false);
            return 0;
    }
}

bool OpenSLPlay::setPlayState(uint32_t playState) {
    std::lock_guard<std::mutex> lk(mMutex);

    mOpenSLHelper.setPlayState(convertPlayState(playState));
    return true;
}

uint32_t OpenSLPlay::putData(const void *data, uint32_t size) {
    std::lock_guard<std::mutex> lk(mMutex);

    if (!mHavePutFirst){
        SLAndroidSimpleBufferQueueItf bufferQueue = mOpenSLHelper.getPlayBufferQueue();
        if (nullptr != bufferQueue){
            if (SL_RESULT_SUCCESS == (*bufferQueue)->Enqueue(bufferQueue, data, size)){
                mHavePutFirst = true;
                return size;
            }
        }
    }
    return mRingQueue.put(data, size);
}

uint32_t OpenSLPlay::getQueuedAudioSize() {
    std::lock_guard<std::mutex> lk(mMutex);

    return mRingQueue.getDataSize();
}

bool OpenSLPlay::close() {
    std::lock_guard<std::mutex> lk(mMutex);

    mRingQueue.clear();
    return mOpenSLHelper.destroy();
}
