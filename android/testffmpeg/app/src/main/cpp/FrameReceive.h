//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_FRAMERECEIVE_H
#define TESTFFMPEG_FRAMERECEIVE_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
#include <stdint.h>
extern "C"{
#include "libavformat/avformat.h"
};
#include "InterfaceDefine.h"


class FrameReceive {
public:
    FrameReceive();
    ~FrameReceive();

public:
    void setMaxFrameCount(unsigned int maxFrameCount);
    void setNotify(IFrameReceiveNotify *notify, int mediaType);
    void setCodecContext(AVCodecContext *codecContext);
    void startReceive();
    AVFrame* popFont();
    int64_t peekPTS();
    bool check();

private:
    void receiveThread();
    bool innerCheck();

private:
    std::mutex mMutex;
    std::condition_variable mCV;
    std::thread mThread;
    AVCodecContext *mCodecContext;
    std::list<AVFrame*> mFrames;
    IFrameReceiveNotify *mNotify;
    int mMediaType;
    unsigned int mMaxFrameCount;
};


#endif //TESTFFMPEG_FRAMERECEIVE_H
