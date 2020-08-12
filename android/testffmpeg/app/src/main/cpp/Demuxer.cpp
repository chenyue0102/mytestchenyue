//
// Created by chenyue on 2020/8/8.
//

#include "Demuxer.h"
#include <assert.h>

#define PACKET_COUNT 10
Demuxer::Demuxer(): mMutex(), mCV(), mThread(), mFormatContext(nullptr), mNotify(nullptr), mDemuxerInfo() {

}

Demuxer::~Demuxer() {

}

void Demuxer::setFormatContext(AVFormatContext *formatContext) {
    std::lock_guard<std::mutex> lk(mMutex);

    mFormatContext = formatContext;
}

void Demuxer::setDemuxerInfo(int mediaType, AVCodecContext *codecContext, int streamIndex, int maxPacketCount){
    std::lock_guard<std::mutex> lk(mMutex);

    mDemuxerInfo[mediaType].streamIndex = streamIndex;
    mDemuxerInfo[mediaType].codecContext = codecContext;
    mDemuxerInfo[mediaType].maxPacketCount = maxPacketCount;
    mDemuxerInfo[mediaType].curPacket = nullptr;
}

void Demuxer::setNotify(IDemuxerNotify *notify) {
    std::lock_guard<std::mutex> lk(mMutex);

    mNotify = notify;
}
bool Demuxer::innerCheckDemuxer() {
    bool ret = false;
    for (auto &pair : mDemuxerInfo){
        if (pair.second.packets.size() < pair.second.maxPacketCount){
            ret = true;
            break;
        }
    }
    return ret;
}

void Demuxer::demuxerThread() {
    while(true){
        std::unique_lock<std::mutex> lk(mMutex);
        IDemuxerNotify *notify = mNotify;
        mCV.wait(lk, [this]()->bool{return innerCheckDemuxer();});
        if (nullptr == mFormatContext){
            assert(false);
            break;
        }
        AVPacket *pkt = av_packet_alloc();
        int ret = av_read_frame(mFormatContext, pkt);
        if (0 != ret){
            av_packet_free(&pkt);

            lk.unlock();
            if (nullptr != notify){
                notify->onFinish();
            }
            break;
        }
        bool bFind = false;
        int mediaType = 0;
        for (auto &pair : mDemuxerInfo){
            if (pkt->stream_index == pair.second.streamIndex){
                bFind = true;
                pair.second.packets.push_back(pkt);
                mediaType = pair.first;
                break;
            }
        }
        if (!bFind){
            av_packet_unref(pkt);
            av_packet_free(&pkt);
        }else{
            lk.unlock();
            if (nullptr != notify){
                notify->onReadFrame(mediaType);
            }
        }
    }
}

void Demuxer::startDemuxer() {
    std::lock_guard<std::mutex> lk(mMutex);

    mThread = std::thread(&Demuxer::demuxerThread, this);
}

void Demuxer::stopDemuxer() {

}

bool Demuxer::sendPacket(int mediaType) {
    bool ret = false;
    std::lock_guard<std::mutex> lk(mMutex);

    auto iter = mDemuxerInfo.find(mediaType);
    if (iter != mDemuxerInfo.end()){
        DemuxerInfo &demuxerInfo = iter->second;
        auto &packets = demuxerInfo.packets;
        if (!packets.empty()){
            AVPacket *packet = packets.front();
            packets.pop_front();
            if (nullptr != demuxerInfo.curPacket){
                av_packet_free(&demuxerInfo.curPacket);
            }
            avcodec_send_packet(iter->second.codecContext, packet);
            av_packet_unref(packet);
            demuxerInfo.curPacket = packet;
            ret = true;
        }
    }
    return ret;
}
