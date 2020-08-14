//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_INTERFACEDEFINE_H
#define TESTFFMPEG_INTERFACEDEFINE_H
#include <stdint.h>

struct IDemuxerNotify{
    virtual void onDemuxerEnd() = 0;
    virtual void onReadFrame(int mediaType) = 0;
};

struct IFrameReceiveNotify{
    virtual void onMoreData(int mediaType) = 0;
    virtual void onReceiveFrame(int mediaType) = 0;
};
struct IAudioPlay;
typedef void(*DSBufferQueueCallback)(IAudioPlay *pDirectSoundHelper, void *pContext);
struct IAudioPlay{
	virtual bool setBufferQueueCallback(DSBufferQueueCallback callback, void *pContext) = 0;
	virtual bool setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t bitsPerSample) = 0;
	virtual bool setUpdateBufferLength(uint32_t updateBufferBytes) = 0;
	virtual bool init() = 0;
	virtual bool setPlayState(uint32_t playState) = 0;
	virtual bool destroy() = 0;
	virtual void putData(const void *data, uint32_t size) = 0;
};

struct IAudioPlayCallback {
	virtual void onBufferCallback(IAudioPlay *audioPlay, void *pContext) = 0;
};

#endif //TESTFFMPEG_INTERFACEDEFINE_H
