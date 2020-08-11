//
// Created by chenyue on 2020/8/8.
//

#include "VideoReceive.h"

#define FRAME_COUNT 10

VideoReceive::VideoReceive():mVCC(nullptr), mNotify(nullptr) {

}

VideoReceive::~VideoReceive() {

}

void VideoReceive::setVideoInfo(AVCodecContext *vcc) {
    std::lock_guard<std::mutex> lk(mMutex);

    mVCC = vcc;
}

void VideoReceive::startReceive() {

}

void VideoReceive::receiveThread() {
    while(true){
        std::unique_lock<std::mutex> lk(mMutex);
        mCV.wait_for(lk, std::chrono::milliseconds (1), [this](){return innerCheck();});
        AVFrame *frame = av_frame_alloc();
        int ret = avcodec_receive_frame(mVCC, frame);
        if (0 != ret){
            if (AVERROR_EOF == ret){
                av_frame_free(&frame);
                break;
            }else if (AVERROR(EAGAIN) == ret){
                av_frame_free(&frame);
                if (nullptr != mNotify){
                    mNotify->onMoreData();
                }
                continue;
            }else{
                av_frame_free(&frame);
                assert(false);
                break;
            }
        }
        mFrames.push_back(frame);
        if (nullptr != mNotify){
            mNotify->onReceiveFrame();
        }
    }
}

bool VideoReceive::innerCheck() {
    return mFrames.size() < FRAME_COUNT;
}
