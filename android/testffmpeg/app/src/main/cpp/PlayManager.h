//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_PLAYMANAGER_H
#define TESTFFMPEG_PLAYMANAGER_H

#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>
extern "C"{
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
}
#include "InterfaceDefine.h"


class Demuxer;
class FrameReceive;
class OpenSLESHelper;
class PlayManager : protected IDemuxerNotify, protected IFrameReceiveNotify{
public:
    PlayManager();
    ~PlayManager();

public:
    bool openFile(const char *filePath);

protected:
    void onReadFrame(int mediaType) override;

    void onFinish() override;

protected:
    void onMoreData(int mediaType) override;

    void onReceiveFrame(int mediaType) override;

public:
    void onBufferQueueCallback();
    FrameReceive* getFrameReceive(int mediaType);
    int64_t getAudioPosition();
private:
    AVFormatContext *mFormatContext;
    AVCodecContext *mVCC;
    AVCodecContext *mACC;
    Demuxer *mDemuxer;
    FrameReceive *mVideoFrameReceive;
    FrameReceive *mAudioFrameReceive;
    OpenSLESHelper *mOpenSLESHelper;
    std::vector<uint8_t> mBuffer;
    SwrContext *mSwrContext;
    enum STATE{
        NONE,

    };
};


#endif //TESTFFMPEG_PLAYMANAGER_H
