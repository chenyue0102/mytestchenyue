//
// Created by chenyue on 2020/8/8.
//

#include "PlayManager.h"
#include <assert.h>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
}
#include "Demuxer.h"
#include "FrameReceive.h"
#ifdef _WIN32
#else
#include "OpenSLESHelper.h"
#endif
#include "Log.h"
#include "MacroDefine.h"
#include "Single.h"
#include "TaskPool.h"

#define MAX_AUDIO_DIFF_MS 5000

void LogAvError(int err) {
	if (0 != err) {
		const int BUF_SIZE = 128;
		char szBuf[BUF_SIZE] = { 0 };
		av_make_error_string(szBuf, BUF_SIZE, err);
		szBuf[BUF_SIZE - 1] = '\0';
		SC(Log).e("%s", szBuf);
		assert(false);
	}
}

#ifdef _WIN32
#else
static void bufferQueueCallback(SLAndroidSimpleBufferQueueItf caller, void *pContext){
    PlayManager *playManager = reinterpret_cast<PlayManager*>(pContext);
    if (nullptr != playManager){
        playManager->onBufferQueueCallback();
    }
}
#endif
PlayManager::PlayManager()
        : mFormatContext(nullptr),
          mVCC(nullptr),
          mACC(nullptr),
          mDemuxer(new Demuxer()),
          mVideoFrameReceive(new FrameReceive()),
          mAudioFrameReceive(new FrameReceive()),
#ifdef _WIN32
#else
          mOpenSLESHelper(new OpenSLESHelper()),
#endif
          mSwrContext(nullptr){
    mDemuxer->setNotify(this);
    mVideoFrameReceive->setNotify(this, AVMEDIA_TYPE_VIDEO);
    mAudioFrameReceive->setNotify(this, AVMEDIA_TYPE_AUDIO);
}

PlayManager::~PlayManager() {
    delete mDemuxer;
    mDemuxer = nullptr;

    delete mVideoFrameReceive;
    mVideoFrameReceive = nullptr;

    delete mAudioFrameReceive;
    mAudioFrameReceive = nullptr;

#ifdef _WIN32
#else
    delete mOpenSLESHelper;
    mOpenSLESHelper = nullptr;
#endif
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
        int videoIndex = av_find_best_stream(mFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        int audioIndex = av_find_best_stream(mFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
        if (videoIndex < 0 && audioIndex < 0){
            assert(false);
            break;
        }
        if (videoIndex >= 0){
            AVCodec *vcodec = avcodec_find_decoder(mFormatContext->streams[videoIndex]->codecpar->codec_id);
            if (nullptr == vcodec){
                assert(false);
                break;
            }
            mVCC = avcodec_alloc_context3(vcodec);
            if (nullptr == mVCC){
                assert(false);
                break;
            }
            if (0 != (err = avcodec_parameters_to_context(mVCC, mFormatContext->streams[videoIndex]->codecpar))){
                LogAvError(err);
                assert(false);
                break;
            }
            if (0 != (err = avcodec_open2(mVCC, nullptr, nullptr))){
                LogAvError(err);
                assert(false);
                break;
            }
            mDemuxer->setDemuxerInfo(AVMEDIA_TYPE_VIDEO, mVCC, videoIndex, 10);
            mVideoFrameReceive->setCodecContext(mVCC);
            mVideoFrameReceive->startReceive();
        }

        if (audioIndex >= 0){
            AVCodec *acodec = avcodec_find_decoder(mFormatContext->streams[audioIndex]->codecpar->codec_id);
            if (nullptr == acodec){
                assert(false);
                break;
            }
            mACC = avcodec_alloc_context3(acodec);
            if (0 != (err = avcodec_parameters_to_context(mACC, mFormatContext->streams[audioIndex]->codecpar))){
                LogAvError(err);
                assert(false);
                break;
            }
            if (0 != (err = avcodec_open2(mACC, nullptr, nullptr))){
                LogAvError(err);
                assert(false);
                break;
            }
            mDemuxer->setDemuxerInfo(AVMEDIA_TYPE_AUDIO, mACC, audioIndex, 10);
            mAudioFrameReceive->setCodecContext(mACC);
            mAudioFrameReceive->startReceive();
        }

        mDemuxer->setFormatContext(mFormatContext);
        mDemuxer->startDemuxer();

#ifdef _WIN32
#else
        mOpenSLESHelper->createEngine();
        mOpenSLESHelper->createOutputMix();

        SLDataLocator_AndroidSimpleBufferQueue bufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
        SLDataFormat_PCM pcm = {
                SL_DATAFORMAT_PCM,
                2,
                SL_SAMPLINGRATE_44_1,
                SL_PCMSAMPLEFORMAT_FIXED_16,
                SL_PCMSAMPLEFORMAT_FIXED_16,
                SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
                SL_BYTEORDER_LITTLEENDIAN,
        };
        SLDataSource slDataSource = {&bufferQueue, &pcm};
        SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, mOpenSLESHelper->getOutputMixObject()};
        SLDataSink slDataSink = {&outputMix, nullptr};
        const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
        const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
        mOpenSLESHelper->createPlayer(slDataSource, slDataSink, 3, ids, req);
        mOpenSLESHelper->registerPlayBufferQueueCallback(&bufferQueueCallback, this);
#endif
        ret = true;
    }while(false);
    return ret;
}

void PlayManager::onFinish() {

}

void PlayManager::onReadFrame(int mediaType) {

}

void PlayManager::onMoreData(int mediaType) {
    mDemuxer->sendPacket(mediaType);
}

void PlayManager::onReceiveFrame(int mediaType) {
    if (AVMEDIA_TYPE_AUDIO == mediaType){
        int64_t pts = mAudioFrameReceive->peekPTS();
        int64_t positionMs = pts * 1000 / AV_TIME_BASE;
        int64_t playPositionMs = getAudioPosition();
        if (positionMs - positionMs < MAX_AUDIO_DIFF_MS){
            AVFrame *frame = mAudioFrameReceive->popFont();
            if (nullptr != frame){
                switch (frame->format){
                    case AV_SAMPLE_FMT_FLT:
                        break;
                    case AV_SAMPLE_FMT_FLTP:{
                        const int byteCountPerChannel = frame->linesize[0];
                        int sampleCountPerChannel = frame->nb_samples;
                        assert(sampleCountPerChannel == byteCountPerChannel / (sizeof(float) * 2));
                        const int outputSampleRate = 44100;
                        int outputSamplePerChanel = av_rescale_rnd(sampleCountPerChannel, outputSampleRate, mACC->sample_rate, AV_ROUND_UP);
                        mBuffer.resize(outputSamplePerChanel * 2 * sizeof(int16_t));
                        if (nullptr == mSwrContext){
                            mSwrContext = swr_alloc();
                            av_opt_set_int(mSwrContext, "in_channel_layout", mACC->channel_layout, 0);
                            av_opt_set_int(mSwrContext, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
                            av_opt_set_int(mSwrContext, "in_sample_rate", mACC->sample_rate, 0);
                            av_opt_set_int(mSwrContext, "out_sample_rate", outputSampleRate, 0);
                            av_opt_set_int(mSwrContext, "in_sample_fmt", AV_SAMPLE_FMT_FLTP, 0);
                            av_opt_set_int(mSwrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
                            swr_init(mSwrContext);
                        }
                        uint8_t *buffers[] = {mBuffer.data()};
						uint8_t *d = frame->extended_data[0];
                        int ret = swr_convert(mSwrContext, buffers, outputSamplePerChanel, (const uint8_t **)frame->extended_data, frame->nb_samples);
						assert(ret > 0);
                        break;
                    }
                    default:
                        SC(Log).e("PlayManager::onReceiveFrame not support format:%d failed", frame->format);
                        assert(false);
                        break;
                }
            }
        }
    }
}

void PlayManager::onBufferQueueCallback() {
    AVFrame *frame = mAudioFrameReceive->popFont();
    if (nullptr != frame){
        switch (frame->format){
            case AV_SAMPLE_FMT_FLT:
                break;
            default:
                SC(Log).e("PlayManager::onBufferQueueCallback not support format:%d failed", frame->format);
                assert(false);
                break;
        }
    }
}

FrameReceive* PlayManager::getFrameReceive(int mediaType){
    if (AVMEDIA_TYPE_AUDIO == mediaType){
        return mAudioFrameReceive;
    }else if (AVMEDIA_TYPE_VIDEO == mediaType){
        return mVideoFrameReceive;
    }else{
        assert(false);
        return nullptr;
    }
}

int64_t PlayManager::getAudioPosition() {
    int64_t ret = 0;
#ifdef _WIN32
#else
    SLPlayItf play = mOpenSLESHelper->getPlay();
    if (nullptr != play){
        SLmillisecond position = 0;
        if (SL_RESULT_SUCCESS == (*play)->GetPosition(play, &position)){
            ret = position;
        }
    }
#endif
    return ret;
}
