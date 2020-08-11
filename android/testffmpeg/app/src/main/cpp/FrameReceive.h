//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_VIDEORECEIVE_H
#define TESTFFMPEG_VIDEORECEIVE_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
#include "libavformat/avformat.h"

struct IFrameReceiveNotify{
    virtual void onMoreData() = 0;
    virtual void onReceiveFrame() = 0;
};

class VideoReceive {
public:
    VideoReceive();
    ~VideoReceive();

public:
    void setVideoInfo(AVCodecContext *vcc);
    void startReceive();

private:
    void receiveThread();
    bool innerCheck();

private:
    std::mutex mMutex;
    std::condition_variable mCV;
    std::thread mThread;
    AVCodecContext *mVCC;
    std::list<AVFrame*> mFrames;
    IFrameReceiveNotify *mNotify;

};


#endif //TESTFFMPEG_VIDEORECEIVE_H
