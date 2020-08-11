//
// Created by chenyue on 2020/8/8.
//

#include "PlayManager.h"
#include <assert.h>
#include "Demuxer.h"
#include "FrameReceive.h"

extern void LogAvError(int err);
PlayManager::PlayManager()
:mFormatContext(nullptr),
mVCC(nullptr),
mVideoIndex(-1),
mACC(nullptr),
mAudioIndex(-1),
mDemuxer(new Demuxer()),
mVideoFrameReceive(new FrameReceive()),
mAudioFrameReceive(new FrameReceive()){
    mDemuxer->setNotify(this);
    mVideoFrameReceive->setNotify(this, (void*)AVMEDIA_TYPE_VIDEO);
    mAudioFrameReceive->setNotify(this, (void*)AVMEDIA_TYPE_AUDIO);
}

PlayManager::~PlayManager() {
    delete mDemuxer;
    mDemuxer = nullptr;

    delete mVideoFrameReceive;
    mVideoFrameReceive = nullptr;

    delete mAudioFrameReceive;
    mAudioFrameReceive = nullptr;
}

bool PlayManager::openFile(const char *filePath) {
    bool ret = false;
    int err = 0;

    do{
        if (nullptr == filePath){
            assert(false);
            break;
        }
        if (0 != (err = avformat_open_input(&mFormatContext, filePath, nullptr, nullptr))){
            LogAvError(err);
            assert(false);
            break;
        }
        if (0 != (err = avformat_find_stream_info(mFormatContext, nullptr))){
            LogAvError(err);
            assert(false);
            break;
        }
        mVideoIndex = av_find_best_stream(mFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        mAudioIndex = av_find_best_stream(mFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
        if (mVideoIndex < 0 && mAudioIndex < 0){
            assert(false);
            break;
        }
        if (mVideoIndex >= 0){
            AVCodec *vcodec = avcodec_find_decoder(mFormatContext->streams[mVideoIndex]->codecpar->codec_id);
            if (nullptr == vcodec){
                assert(false);
                break;
            }
            mVCC = avcodec_alloc_context3(vcodec);
            if (nullptr == mVCC){
                assert(false);
                break;
            }
            if (0 != (err = avcodec_parameters_to_context(mVCC, mFormatContext->streams[mVideoIndex]->codecpar))){
                LogAvError(err);
                assert(false);
                break;
            }
            mDemuxer->setVideoInfo(mVCC, mVideoIndex);
        }

        if (mAudioIndex >= 0){
            AVCodec *acodec = avcodec_find_decoder(mFormatContext->streams[mAudioIndex]->codecpar->codec_id);
            if (nullptr == acodec){
                assert(false);
                break;
            }
            mACC = avcodec_alloc_context3(acodec);
            if (0 != (err = avcodec_parameters_to_context(mACC, mFormatContext->streams[mAudioIndex]->codecpar)));{
                LogAvError(err);
                assert(false);
                break;
            }
            mDemuxer->setAudioInfo(mACC, mAudioIndex);
        }

        mDemuxer->setFormatContext(mFormatContext);
        mDemuxer->startDemuxer();
        ret = true;
    }while(false);
    return ret;
}

void PlayManager::onFinish() {

}

void PlayManager::onReadFrame(int mediaType) {
    if (AVMEDIA_TYPE_VIDEO == mediaType){

    }
}

void PlayManager::onSendPacket(int mediaType) {

}

void PlayManager::onMoreData(int mediaType) {
    mDemuxer->sendPacket(mediaType);
}

void PlayManager::onReceiveFrame(int mediaType) {

}
