//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_PLAYMANAGER_H
#define TESTFFMPEG_PLAYMANAGER_H

#include "libavformat/avformat.h"
#include "InterfaceDefine.h"

class Demuxer;
class FrameReceive;
class PlayManager : protected IDemuxerNotify, protected IFrameReceiveNotify{
public:
    PlayManager();
    ~PlayManager();

public:
    bool openFile(const char *filePath);

protected:
    void onReadFrame(int mediaType) override;

    void onSendPacket(int mediaType) override;

    void onFinish() override;

protected:
    void onMoreData(int mediaType) override;

    void onReceiveFrame(int mediaType) override;

private:
    AVFormatContext *mFormatContext;
    AVCodecContext *mVCC;
    int mVideoIndex;
    AVCodecContext *mACC;
    int mAudioIndex;
    Demuxer *mDemuxer;
    FrameReceive *mVideoFrameReceive;
    FrameReceive *mAudioFrameReceive;
};


#endif //TESTFFMPEG_PLAYMANAGER_H
