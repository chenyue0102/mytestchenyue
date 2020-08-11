//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_DEMUX_H
#define TESTFFMPEG_DEMUX_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
extern "C"{
#include "libavformat/avformat.h"
}

class Demux {
public:
    Demux();
    ~Demux();

public:
    void setFormatContext(AVFormatContext *formatContext);
    void startDemutex();
    void stopDemutex();

private:
    void demutexThread();
private:
    std::mutex mMutex;
    std::condition_variable mCV;
    std::thread mThread;
    AVFormatContext *mFormatContext;
    std::list<AVPacket*> mPacket;
};


#endif //TESTFFMPEG_DEMUX_H
