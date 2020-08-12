//
// Created by chenyue on 2020/8/8.
//

#include "FrameReceive.h"
#include <assert.h>
extern "C"{
#include "libavutil/frame.h"
}
#define MAX_FRAME_COUNT 10

extern void LogAvError(int err);
FrameReceive::FrameReceive()
: mCodecContext(nullptr)
, mNotify(nullptr)
, mMediaType(0)
, mMaxFrameCount(MAX_FRAME_COUNT) {

}

FrameReceive::~FrameReceive() {

}

void FrameReceive::setMaxFrameCount(unsigned int maxFrameCount){
    std::lock_guard<std::mutex> lk(mMutex);

    mMaxFrameCount = maxFrameCount;
}

void FrameReceive::setNotify(IFrameReceiveNotify *notify, int mediaType) {
    std::lock_guard<std::mutex> lk(mMutex);

    mNotify = notify;
    mMediaType = mediaType;
}

void FrameReceive::setCodecContext(AVCodecContext *codecContext) {
    std::lock_guard<std::mutex> lk(mMutex);

    mCodecContext = codecContext;
}

void FrameReceive::startReceive() {
    std::lock_guard<std::mutex> lk(mMutex);

    mThread = std::thread(&FrameReceive::receiveThread, this);
}

AVFrame* FrameReceive::popFont(){
    AVFrame *frame = nullptr;
    {
        std::lock_guard<std::mutex> lk(mMutex);
        if (!mFrames.empty()){
            frame = mFrames.front();
            mFrames.pop_front();
        }
    }
    return frame;
}
int64_t FrameReceive::peekPTS() {
    std::lock_guard<std::mutex> lk(mMutex);
    int64_t pts = -1;
    if (!mFrames.empty()){
        AVFrame *frame = mFrames.front();
        assert(nullptr != frame);
        pts = frame->pts;
    }
    return pts;
}

bool FrameReceive::check() {
    std::lock_guard<std::mutex> lk(mMutex);

    return innerCheck();
}


void FrameReceive::receiveThread() {
    while(true){
        std::unique_lock<std::mutex> lk(mMutex);
        IFrameReceiveNotify *notify = mNotify;
        mCV.wait_for(lk, std::chrono::milliseconds (1), [this](){return innerCheck();});
        AVFrame *frame = av_frame_alloc();
        int ret = avcodec_receive_frame(mCodecContext, frame);
        if (0 != ret){
            if (AVERROR_EOF == ret){
                av_frame_free(&frame);
                break;
            }else if (AVERROR(EAGAIN) == ret){
                av_frame_free(&frame);

                lk.unlock();
                if (nullptr != notify){
                    notify->onMoreData(mMediaType);
                }
                continue;
            }else{
                av_frame_free(&frame);
                LogAvError(ret);
                assert(false);
                break;
            }
        }
        mFrames.push_back(frame);

        lk.unlock();
        if (nullptr != notify){
            notify->onReceiveFrame(mMediaType);
        }
    }
}

bool FrameReceive::innerCheck() {
    return mFrames.size() < mMaxFrameCount;
}
