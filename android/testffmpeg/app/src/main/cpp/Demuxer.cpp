//
// Created by chenyue on 2020/8/8.
//

#include "Demuxer.h"
#include <assert.h>

#define PACKET_COUNT 10
Demuxer::Demuxer(): mMutex(), mCV(), mThread(), mFormatContext(nullptr), mNotify(nullptr),
mVcc(nullptr), mVideoStreamIndex(-1), mAcc(nullptr), mAudioStreamIndex(-1) {

}

Demuxer::~Demuxer() {

}

void Demuxer::setFormatContext(AVFormatContext *formatContext) {
    std::lock_guard<std::mutex> lk(mMutex);

    mFormatContext = formatContext;
}

void Demuxer::setDemuxerInfo(int mediaType, AVCodecContext *codecContext, int streamIndex){
    std::lock_guard<std::mutex> lk(mMutex);

    mDemuxerInfo[mediaType].streamIndex = streamIndex;
    mDemuxerInfo[mediaType].codecContext = codecContext;
}

void Demuxer::setNotify(IDemuxerNotify *notify) {
    std::lock_guard<std::mutex> lk(mMutex);

    mNotify = notify;
}
bool Demuxer::innerCheckDemuxer() {
    int count = 0;
    for (auto &pair : mDemuxerInfo){
        count += pair.second.packets.size();
    }
    return count < PACKET_COUNT;
}

void Demuxer::demuxerThread() {
    while(true){
        std::unique_lock<std::mutex> lk(mMutex);
        mCV.wait(lk, [this]()->bool{return innerCheckDemuxer();});
        if (nullptr == mFormatContext){
            assert(false);
            break;
        }
        AVPacket *pkt = av_packet_alloc();
        int ret = av_read_frame(mFormatContext, pkt);
        if (0 != ret){
            av_packet_free(&pkt);
            if (nullptr != mNotify){
                mNotify->onFinish();
            }
            break;
        }
        bool bFind = false;
        for (auto &pair : mDemuxerInfo){
            if (pkt->stream_index == pair.second.streamIndex){
                bFind = true;
                pair.second.packets.push_back(pkt);
                if (nullptr != mNotify){
                    mNotify->onReadFrame(pair.first);
                }
                break;
            }
        }
        if (!bFind){
            av_packet_unref(pkt);
            av_packet_free(&pkt);
        }
    }
}

void Demuxer::startDemuxer() {
    std::lock_guard<std::mutex> lk(mMutex);

    mThread = std::thread(&Demuxer::demuxerThread, this);
}

void Demuxer::stopDemuxer() {

}

void Demuxer::sendPacket(int mediaType) {
    std::lock_guard<std::mutex> lk(mMutex);

    auto iter = mDemuxerInfo.find(mediaType);
    if (iter != mDemuxerInfo.end()){
        auto &packets = iter->second.packets;
        AVPacket *packet = packets.front();
        packets.pop_front();
        avcodec_send_packet(iter->second.codecContext, packet);
        av_packet_unref(packet);
        av_packet_free(&packet);

        if (nullptr != mNotify){
            mNotify->onSendPacket(iter->first);
        }
    }
}
