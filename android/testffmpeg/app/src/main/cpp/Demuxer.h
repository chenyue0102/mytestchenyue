//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_DEMUXER_H
#define TESTFFMPEG_DEMUXER_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
#include <map>
extern "C"{
#include "libavformat/avformat.h"
}
#include "InterfaceDefine.h"

class Demuxer {
public:
    Demuxer();
    ~Demuxer();

public:
    void setFormatContext(AVFormatContext *formatContext);
    void setDemuxerInfo(int mediaType, AVCodecContext *codecContext, int streamIndex);
    void setNotify(IDemuxerNotify *notify);
    void startDemuxer();
    void stopDemuxer();
    void sendPacket(int mediaType);

private:
    void demuxerThread();
    bool innerCheckDemuxer();
private:
    std::mutex mMutex;
    std::condition_variable mCV;
    std::thread mThread;
    AVFormatContext *mFormatContext;
    IDemuxerNotify *mNotify;
    struct DemuxerInfo{
        std::list<AVPacket*> packets;
        AVCodecContext *codecContext;
        int streamIndex;
    };
    std::map<int, DemuxerInfo> mDemuxerInfo;
};


#endif //TESTFFMPEG_DEMUXER_H
