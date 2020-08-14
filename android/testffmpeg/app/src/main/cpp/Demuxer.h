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
    void setDemuxerInfo(uint32_t mediaType, AVCodecContext *codecContext, uint32_t streamIndex, uint32_t maxPacketCount);
    void setNotify(IDemuxerNotify *notify);
    void startDemuxer();
    void stopDemuxer();
    bool sendPacket(uint32_t mediaType);

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
        AVPacket *curPacket;
        AVCodecContext *codecContext;
		uint32_t streamIndex;
        uint32_t maxPacketCount;
    };
    std::map<uint32_t, DemuxerInfo> mDemuxerInfo;
};


#endif //TESTFFMPEG_DEMUXER_H
