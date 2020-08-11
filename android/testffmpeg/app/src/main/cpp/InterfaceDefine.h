//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_INTERFACEDEFINE_H
#define TESTFFMPEG_INTERFACEDEFINE_H


struct IDemuxerNotify{
    virtual void onFinish() = 0;
    virtual void onReadFrame(int meidaType) = 0;
    virtual void onSendPacket(int mediaType) = 0;
};

struct IFrameReceiveNotify{
    virtual void onMoreData(int mediaType) = 0;
    virtual void onReceiveFrame(int mediaType) = 0;
};

#endif //TESTFFMPEG_INTERFACEDEFINE_H
