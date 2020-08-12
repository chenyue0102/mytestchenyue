//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_INTERFACEDEFINE_H
#define TESTFFMPEG_INTERFACEDEFINE_H
#include <stdint.h>

struct IDemuxerNotify{
    virtual void onFinish() = 0;
    virtual void onReadFrame(int mediaType) = 0;
};

struct IFrameReceiveNotify{
    virtual void onMoreData(int mediaType) = 0;
    virtual void onReceiveFrame(int mediaType) = 0;
};

struct IAudioPlay{
	virtual void putData(const void *data, uint32_t size) = 0;
};

struct IAudioPlayCallback {
	virtual void onBufferCallback(IAudioPlay *audioPlay, void *pContext) = 0;
};

#endif //TESTFFMPEG_INTERFACEDEFINE_H
