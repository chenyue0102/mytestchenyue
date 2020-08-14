//
// Created by chenyue on 2020/8/8.
//

#include "PlayManager.h"
#include <assert.h>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
}
#ifdef _WIN32
#include "DirectSoundHelper.h"
#else
#include "OpenSLESHelper.h"
#endif
#include "Log.h"
#include "MacroDefine.h"
#include "Single.h"
#include "TaskPool.h"
#include "EnumDefine.h"
#include "BaseTime.h"

#define MAX_AUDIO_DIFF_MS 5000
#define AUDIO_BITS 16

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

int getAudioBitsPerSample(AVFrame *frame) {
	int bits = 0;
	switch (frame->format) {
	case AV_SAMPLE_FMT_U8:
	case AV_SAMPLE_FMT_U8P:
		bits = 8;
		break;
	case AV_SAMPLE_FMT_S16:
	case AV_SAMPLE_FMT_S16P:
		bits = 16;
		break;
	case AV_SAMPLE_FMT_S32:

		break;
}
	return bits;
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
#define MAX_QUEUE_SIZE (1024)

struct MediaInfo {
	AVCodecContext *codecContext = nullptr;
	int streamIndex = -1;

	mutable std::mutex mtx;
	std::condition_variable cv;
	bool exit = false;
	std::list<AVPacket*> packets;
	std::list<AVFrame*> frames;
	bool packetDecoding = false;
	bool receivedFrame = false;

	void putPacket(AVPacket *packet) {
		std::lock_guard<std::mutex> lk(mtx);
		packets.push_back(packet);
        cv.notify_all();
	}

	size_t getPacketSize()const {
		std::lock_guard<std::mutex> lk(mtx);
		return packets.size();
	}

	void putFrame(AVFrame *frame){
        std::lock_guard<std::mutex> lk(mtx);
        frames.push_back(frame);
        cv.notify_all();
	}

	size_t getFrameSize()const{
        std::lock_guard<std::mutex> lk(mtx);
        return frames.size();
	}
};
#define MAX_FRAME_SIZE 100
struct PlayManagerData {
	std::string fileName;
	std::mutex mtx;
	std::condition_variable cv;
	bool exit = false;
	bool initAudioPlay = false;
	int64_t pausePosition = -1;
	SwrContext *swrContext = nullptr;
	std::vector<uint8_t> swrBuffer;
	void notifyRead(){
	    std::lock_guard<std::mutex> lk(mtx);
	    cv.notify_all();
	}

	MediaInfo aMediaInfo;
	MediaInfo vMediaInfo;
	BaseTime systemTime;
	PlayHelper mPlayHelper;
};

void sendPacket(MediaInfo &info) {
	if (!info.packets.empty()) {
		AVPacket *pkt = info.packets.front();
		info.packets.pop_front();
		avcodec_send_packet(info.codecContext, pkt);
		av_packet_unref(pkt);
		av_packet_free(&pkt);
		info.packetDecoding = true;
		info.receivedFrame = false;
	}
}

void audioThread(MediaInfo *pInfo, std::function<void()> notifyReadFrame) {
	auto &info = *pInfo;
	auto &mtx = info.mtx;
	auto &cv = info.cv;
    AVFrame *frame = av_frame_alloc();
	for (;;) {
		std::unique_lock<std::mutex> lk(info.mtx);
		cv.wait(lk, [&info]()->bool {
			return info.exit || (info.frames.size() < MAX_FRAME_SIZE);
			});

		if (info.exit){
		    break;
		}

        if (info.packetDecoding){
            int ret = avcodec_receive_frame(info.codecContext, frame);
            if (ret < 0){
                if (AVERROR_EOF == ret){
                    break;
                }else if(AVERROR(EAGAIN) == ret){
					if (info.receivedFrame) {
						if (info.packets.empty()) {
							lk.unlock();//解锁audio的锁，防止死锁
							notifyReadFrame();
							std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
						else {
							sendPacket(info);
							lk.unlock();//解锁audio的锁，防止死锁
							notifyReadFrame();
						}
					}
					else {
						//正在解码，等会
						lk.unlock();
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
                    continue;
                }else{
                    assert(false);
                    break;
                }
            }
			info.receivedFrame = true;
            AVFrame *tmpFrame = av_frame_alloc();
            av_frame_move_ref(tmpFrame, frame);
            info.frames.push_back(tmpFrame);
            info.cv.notify_all();
        }else{
            if (info.packets.empty()){
                lk.unlock();//解锁audio的锁，防止死锁
				notifyReadFrame();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }else{
				sendPacket(info);
				lk.unlock();//解锁audio的锁，防止死锁
				notifyReadFrame();
            }
        }
	}
    av_frame_free(&frame);
}

void videoThread(PlayManagerData *mediaInfo) {

}

void readThread(PlayManagerData *mediaInfo) {
	int err = 0;
	AVFormatContext *formatContext = nullptr;
	std::thread aThread, vThread;
	do
	{
		if (0 != (err = avformat_open_input(&formatContext, mediaInfo->fileName.c_str(), nullptr, nullptr))) {
			LogAvError(err);
			assert(false);
			break;
}
		if (0 != (err = avformat_find_stream_info(formatContext, nullptr))) {
			LogAvError(err);
			assert(false);
			break;
		}
		auto &videoIndex = mediaInfo->vMediaInfo.streamIndex;
		auto &audioIndex = mediaInfo->aMediaInfo.streamIndex;
		videoIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
		audioIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
		if (videoIndex < 0 && audioIndex < 0) {
			assert(false);
			break;
		}
		auto notifyReadFrame = [mediaInfo]() {
			std::lock_guard<std::mutex> lk(mediaInfo->mtx);
			mediaInfo->cv.notify_all();
		};
		if (videoIndex >= 0) {
			AVCodec *vcodec = avcodec_find_decoder(formatContext->streams[videoIndex]->codecpar->codec_id);
			if (nullptr == vcodec) {
				assert(false);
				break;
			}
			auto &codecContext = mediaInfo->vMediaInfo.codecContext;
			codecContext = avcodec_alloc_context3(vcodec);
			if (nullptr == codecContext) {
				assert(false);
				break;
			}
			if (0 != (err = avcodec_parameters_to_context(codecContext, formatContext->streams[videoIndex]->codecpar))) {
				LogAvError(err);
				assert(false);
				break;
			}
			if (0 != (err = avcodec_open2(codecContext, nullptr, nullptr))) {
				LogAvError(err);
				assert(false);
				break;
			}
			vThread = std::thread(&videoThread, mediaInfo);
		}

		if (audioIndex >= 0) {
			AVCodecParameters *codecParameters = formatContext->streams[audioIndex]->codecpar;
			AVCodec *acodec = avcodec_find_decoder(codecParameters->codec_id);
			if (nullptr == acodec) {
				assert(false);
				break;
			}
			auto &codecContext = mediaInfo->aMediaInfo.codecContext;
			codecContext = avcodec_alloc_context3(acodec);
			if (0 != (err = avcodec_parameters_to_context(codecContext, codecParameters))) {
				LogAvError(err);
				assert(false);
				break;
			}
			if (0 != (err = avcodec_open2(codecContext, nullptr, nullptr))) {
				LogAvError(err);
				assert(false);
				break;
			}


			aThread = std::thread(&audioThread, &mediaInfo->aMediaInfo, notifyReadFrame);
		}
		
		auto &cv = mediaInfo->cv;
		auto &mtx = mediaInfo->mtx;
		for (;;) {
			std::unique_lock<std::mutex> lk(mtx);
			cv.wait(lk, [mediaInfo]()->bool {
				bool isPacketNotFull = (mediaInfo->aMediaInfo.getPacketSize() + mediaInfo->vMediaInfo.getPacketSize()) < MAX_QUEUE_SIZE;
				if (isPacketNotFull) {
					return true;
				}
				else {
					return mediaInfo->exit;
				}
				});

			if (mediaInfo->exit) {
				break;
			}
			if (!mediaInfo->initAudioPlay) {
				auto &aMediaInfo = mediaInfo->aMediaInfo;
				std::lock_guard<std::mutex> lka(aMediaInfo.mtx);
				if (!aMediaInfo.frames.empty()) {
					AVFrame *frame = aMediaInfo.frames.front();
					int outNumChannel = frame->channels == 1 ? 1 : 2;
					outNumChannel = 2;
					mediaInfo->mPlayHelper.setSampleInfo(outNumChannel, frame->sample_rate, 16);
					
					uint32_t updateBufferBytes = frame->nb_samples * outNumChannel * 16 / 8;
					mediaInfo->mPlayHelper.setUpdateBufferLength(updateBufferBytes);
					mediaInfo->initAudioPlay = true;

					auto &swrContext = mediaInfo->swrContext;
					assert(nullptr == swrContext);
					swrContext = swr_alloc();
					av_opt_set_int(swrContext, "in_channel_layout", frame->channel_layout, 0);
					av_opt_set_int(swrContext, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
					av_opt_set_int(swrContext, "in_channel_count", frame->channels, 0);
					av_opt_set_int(swrContext, "out_channel_count", 2, 0);
					av_opt_set_int(swrContext, "in_sample_rate", frame->sample_rate, 0);
					av_opt_set_int(swrContext, "out_sample_rate", frame->sample_rate, 0);
					av_opt_set_int(swrContext, "in_sample_fmt", frame->format, 0);
					av_opt_set_int(swrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
					swr_init(swrContext);

					mediaInfo->mPlayHelper.init();
					mediaInfo->mPlayHelper.setPlayState(EPlayStatePlaying);
				}
			}

			lk.unlock();
			
			AVPacket *pkt = av_packet_alloc();
			int ret = av_read_frame(formatContext, pkt);
			if (ret < 0) {
				if (AVERROR_EOF == ret) {
					if (mediaInfo->aMediaInfo.streamIndex >= 0) {
						//todo
					}
				}
				//todo free
			}


			if (pkt->stream_index == mediaInfo->aMediaInfo.streamIndex) {
				mediaInfo->aMediaInfo.putPacket(pkt);
			}
			else if (pkt->stream_index == mediaInfo->vMediaInfo.streamIndex) {
				mediaInfo->vMediaInfo.putPacket(pkt);
			}
			else {
				av_packet_unref(pkt);
				av_packet_free(&pkt);
			}
		}
	} while (false);

	if (aThread.joinable()) {
		aThread.join();
	}
	if (vThread.joinable()) {
		vThread.join();
	}
}

void loopThread(PlayManagerData *mediaInfo){
	auto &mtx = mediaInfo->mtx;
	auto &cv = mediaInfo->cv;
	for (;;) {
		std::unique_lock<std::mutex> lk(mtx);
		cv.wait_for(lk, std::chrono::milliseconds(20), [mediaInfo]()->bool {
			return mediaInfo->exit;
			});
		if (mediaInfo->exit) {
			break;
		}

	}
}

PlayManager::PlayManager()
	: mData(new PlayManagerData())
{
 
}

PlayManager::~PlayManager() {
	delete mData;
	mData = nullptr;
}

bool PlayManager::openFile(const char *filePath) {
	assert(!mReadThread.joinable() && !mLoopThread.joinable());

	mData->exit = false;
	mData->fileName = filePath;
	mReadThread = std::thread(&readThread, mData);
    mLoopThread = std::thread(&loopThread, mData);
	mData->mPlayHelper.setCallback(this, nullptr);
	//mData->mPlayHelper.setUpdateBufferLength()
	return true;
}

bool PlayManager::setPlayState(uint32_t playState) {
	//std::lock_guard<std::mutex> lk(mMutex);

	//mPlayState = playState;
	return true;
}

void PlayManager::onBufferCallback(IAudioPlay *audioPlay, void *pContext) {
	auto &aMediaInfo = mData->aMediaInfo;
	std::unique_lock<std::mutex> lk(aMediaInfo.mtx);
	if (!aMediaInfo.frames.empty()) {
		AVFrame *frame = aMediaInfo.frames.front();
		aMediaInfo.frames.pop_front();
		
		//int64_t outputSampleRate = frame->sample_rate;
		//uint32_t outputSamplePerChanel = static_cast<uint32_t>(av_rescale_rnd(frame->nb_samples, outputSampleRate, frame->sample_rate, AV_ROUND_UP));
		auto &swrBuffer = mData->swrBuffer;
		int putSize = frame->nb_samples * 2 * 16 / 8;
		swrBuffer.resize(putSize);
		uint8_t *buffers[] = { swrBuffer.data() };
		uint32_t outputSamplePerChanel = frame->nb_samples;
		int retNumSamplePerChannel = swr_convert(mData->swrContext, buffers, outputSamplePerChanel, (const uint8_t **)frame->extended_data, frame->nb_samples);
		assert(retNumSamplePerChannel > 0);

		av_frame_unref(frame);
		av_frame_free(&frame);
		aMediaInfo.cv.notify_all();
		lk.unlock();
		audioPlay->putData(swrBuffer.data(), putSize);
	}
	else {
		assert(false);//解码没有跟上，
	}
}

