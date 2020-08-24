//
// Created by chenyue on 2020/8/8.
//

#include "PlayManager.h"
#include <assert.h>
#include <algorithm>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
}
#include "EnumDefine.h"
#ifdef _WIN32
#include "DirectSoundHelper.h"
#include "SDLAudioHelper.h"
#else
#include "OpenSLPlay.h"
#endif
#include "Log.h"
#include "MacroDefine.h"
#include "Single.h"
#include "TaskPool.h"
#include "EnumDefine.h"
#include "ClockTime.h"
#include "OpenGLPlay.h"

#define MAX_AUDIO_DIFF_MS 5000
#define AUDIO_BITS 16
#define AUDIO_BUFFER_SIZE (1024 * 200)
#define MAX_QUEUE_SIZE (1024)
#define MAX_FRAME_SIZE 100
#define MAX_DECODE_PACKET_COUNT 20

#ifdef _WIN32
class DirectSoundHelper;
class SDLAudioHelper;
typedef SDLAudioHelper PlayHelper;
#else
class OpenSLPlay;
typedef OpenSLPlay PlayHelper;
#endif

typedef OpenGLPlay VideoPlayHelper;

static AVPacket flush_pkt;

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
//second = ts * num / den
int64_t ms2ts(const AVRational &rational, int64_t ms){
	int64_t ts = 0;
	if (rational.num != 0){
		ts = ms * rational.den / rational.num / 1000;
	}
	return ts;
}

int64_t ts2ms(const AVRational &rational, int64_t ts) {
	int64_t ms = 0;
	if (rational.den != 0) {
		ms = ts * rational.num * 1000 / rational.den;
	}
	return ms;
}

int convertPixelFormat(int format){
    int ret = 0;
    switch (format){
        case AV_PIX_FMT_YUV420P:
            ret = EVideoFormatYUV420P;
            break;
        default:
            assert(false);
            break;
    }
    return ret;
}

struct MediaInfo {
	AVStream *stream = nullptr;
	AVCodecContext *codecContext = nullptr;
	int streamIndex = -1;

	mutable std::mutex mtx;
	std::condition_variable cv;
	bool exit = false;
	std::list<AVPacket*> packets;
	std::list<AVFrame*> frames;
	int decodingPacketCount = 0;
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

	void flushPacket() {
		std::lock_guard<std::mutex> lk(mtx);

		while (!packets.empty()){
			AVPacket *pkt = packets.front();
			packets.pop_front();
			if (pkt == &flush_pkt) {
				continue;
			}
			av_packet_unref(pkt);
			av_packet_free(&pkt);
		}
	}

	void flushFrame() {
		std::lock_guard<std::mutex> lk(mtx);

		while (!frames.empty()) {
			AVFrame *frame = frames.front();
			frames.pop_front();

			av_frame_unref(frame);
			av_frame_free(&frame);
		}
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

struct PlayManagerData {
	std::string fileName;
	std::mutex mtx;
	std::condition_variable cv;
	bool exit = false;

	ClockTime clockTime;
	bool seeking = false;
	int64_t seekMs = 0;

	int64_t pausePosition = -1;
	std::vector<uint8_t> swrBuffer;
	void notifyRead(){
	    std::lock_guard<std::mutex> lk(mtx);
	    cv.notify_all();
	}

	MediaInfo aMediaInfo;
	MediaInfo vMediaInfo;
	PlayHelper mPlayHelper;
    VideoPlayHelper mVideoPlayHelper;
};

static void sendPacket(MediaInfo &info) {
	if (!info.packets.empty()) {
		AVPacket *pkt = info.packets.front();
		info.packets.pop_front();
		
		if (pkt->data == flush_pkt.data) {
			avcodec_flush_buffers(info.codecContext);
			info.decodingPacketCount = 0;
		}
		else {
			int err = 0;
			if ((err = avcodec_send_packet(info.codecContext, pkt)) < 0) {
				LogAvError(err);
			}
			else {
				info.decodingPacketCount++;
			}
			av_packet_unref(pkt);
			av_packet_free(&pkt);
			
		}
		info.receivedFrame = false;
	}
}

static void audioThread(MediaInfo *pInfo, std::function<void()> notifyReadFrame) {
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

		int ret = avcodec_receive_frame(info.codecContext, frame);
		if (ret < 0) {
			if (AVERROR_EOF == ret) {
				break;
			}
			else if (AVERROR(EAGAIN) == ret) {
				if (info.receivedFrame) {//avcodec_receive_frame成功过，然后出现EAGAIN，表示packet已经解码完了，继续投递新包
					info.decodingPacketCount = 0;
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
				else if (info.decodingPacketCount < MAX_DECODE_PACKET_COUNT && !info.packets.empty()) {
					sendPacket(info);
					lk.unlock();//解锁audio的锁，防止死锁
					notifyReadFrame();
				}
				else {
					//正在解码，等会
					lk.unlock();
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
			else {
				assert(false);
				break;
			}
		}
		else {
			info.receivedFrame = true;
			AVFrame *tmpFrame = av_frame_alloc();
			av_frame_move_ref(tmpFrame, frame);
			info.frames.push_back(tmpFrame);
			info.cv.notify_all();
		}
	}
    av_frame_free(&frame);
}

static void videoThread(MediaInfo *pInfo, std::function<void()> notifyReadFrame) {
    auto &info = *pInfo;
    auto &mtx = info.mtx;
    auto &cv = info.cv;
    AVFrame *frame = av_frame_alloc();

    for (;;) {
        std::unique_lock<std::mutex> lk(info.mtx);
        cv.wait(lk, [&info]() -> bool {
            return info.exit || (info.frames.size() < MAX_FRAME_SIZE);
        });

        if (info.exit) {
            break;
        }

		int ret = avcodec_receive_frame(info.codecContext, frame);
		if (ret < 0) {
			if (AVERROR_EOF == ret) {
				break;
			}
			else if (AVERROR(EAGAIN) == ret) {
				if (info.receivedFrame) {//avcodec_receive_frame成功过，然后出现EAGAIN，表示packet已经解码完了，继续投递新包
					info.decodingPacketCount = 0;
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
				else if (info.decodingPacketCount < MAX_DECODE_PACKET_COUNT && !info.packets.empty()) {
					sendPacket(info);
					lk.unlock();//解锁audio的锁，防止死锁
					notifyReadFrame();
				}
				else {
					//正在解码，等会
					lk.unlock();
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
			else {
				assert(false);
				break;
			}
		}
		else {
			info.receivedFrame = true;
			AVFrame *tmpFrame = av_frame_alloc();
			av_frame_move_ref(tmpFrame, frame);
			info.frames.push_back(tmpFrame);
			info.cv.notify_all();
		}
    }
    av_frame_free(&frame);
}

SwrContext* initSwrContext(AVFrame *frame){
    SwrContext *swrContext = swr_alloc();
    av_opt_set_int(swrContext, "in_channel_layout", frame->channel_layout, 0);
    av_opt_set_int(swrContext, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
    av_opt_set_int(swrContext, "in_channel_count", frame->channels, 0);
    av_opt_set_int(swrContext, "out_channel_count", 2, 0);
    av_opt_set_int(swrContext, "in_sample_rate", frame->sample_rate, 0);
    av_opt_set_int(swrContext, "out_sample_rate", 44100, 0);
    av_opt_set_int(swrContext, "in_sample_fmt", frame->format, 0);
    av_opt_set_int(swrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
    swr_init(swrContext);
    return swrContext;
}

static void loopThread(PlayManagerData *mediaInfo){
    auto &aMediaInfo = mediaInfo->aMediaInfo;
    SwrContext *swrContext = nullptr;
    auto &playHelper = mediaInfo->mPlayHelper;
    int sample_rate = 0;
    uint32_t bytePerSecond = 0;
    std::vector<uint8_t> swrBuffer;
    auto &vMediaInfo = mediaInfo->vMediaInfo;
    auto &videoPlayHelper = mediaInfo->mVideoPlayHelper;
    int64_t ms = 0;

    for (;;) {
		{
			std::lock_guard<std::mutex> lk(mediaInfo->mtx);
			if (mediaInfo->exit) {
				break;
			}
		}
        ms = -1;
        {
            std::lock_guard<std::mutex> lk(aMediaInfo.mtx);
            if (aMediaInfo.streamIndex >= 0){
                int64_t pts = -1;
                while (playHelper.getQueuedAudioSize() < AUDIO_BUFFER_SIZE && !aMediaInfo.frames.empty()) {
                    AVFrame *frame = aMediaInfo.frames.front();
                    aMediaInfo.frames.pop_front();

                    pts = frame->pts;
                    if (nullptr == swrContext || sample_rate != frame->sample_rate){
                        if (nullptr != swrContext){
                            swr_close(swrContext);
                            swr_free(&swrContext);
                        }
                        swrContext = initSwrContext(frame);
                        bytePerSecond = frame->channels * 44100 * 2;
                    }
                    int putSize = frame->nb_samples * 2 * 16 / 8;
                    swrBuffer.resize(putSize);
                    uint8_t *buffers[] = { swrBuffer.data() };
                    uint32_t outputSamplePerChanel = frame->nb_samples;
                    int retNumSamplePerChannel = swr_convert(swrContext, buffers, outputSamplePerChanel, (const uint8_t **)frame->extended_data, frame->nb_samples);
                    assert(retNumSamplePerChannel > 0);
                    playHelper.putData(swrBuffer.data(), putSize);

                    av_frame_unref(frame);
                    av_frame_free(&frame);
                }
                if (-1 != pts){
                    ms = ts2ms(aMediaInfo.stream->time_base, pts);
                    ms -= (int64_t)playHelper.getQueuedAudioSize() * 1000 / bytePerSecond;
                }
                aMediaInfo.cv.notify_all();
            }
        }

        {
            std::lock_guard<std::mutex> lk(vMediaInfo.mtx);
            if (vMediaInfo.streamIndex >= 0){
                while(!vMediaInfo.frames.empty()){
                    AVFrame *frame = vMediaInfo.frames.front();
                    int64_t videoMs = ts2ms(vMediaInfo.stream->time_base, frame->pts);
                    if (videoMs - ms > 21){
                        break;
                    }else if (videoMs < ms){
                        vMediaInfo.frames.pop_front();
                        av_frame_unref(frame);
                        av_frame_free(&frame);
                        continue;
                    }else{
                        vMediaInfo.frames.pop_front();
                        videoPlayHelper.putData(frame->data, frame->linesize);
                        av_frame_unref(frame);
                        av_frame_free(&frame);
                    }
                }
                vMediaInfo.cv.notify_all();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    if (nullptr != swrContext) {
        swr_close(swrContext);
        swr_free(&swrContext);
    }
}

void readThread(PlayManagerData *mediaInfo) {
	int err = 0;
	AVFormatContext *formatContext = nullptr;
	std::thread aThread, vThread, lThread;
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
			AVStream *stream = formatContext->streams[videoIndex];
			AVCodecParameters *codecParameters = stream->codecpar;
			AVCodec *vcodec = avcodec_find_decoder(codecParameters->codec_id);
			if (nullptr == vcodec) {
				assert(false);
				break;
			}
			mediaInfo->vMediaInfo.stream = stream;
			auto &codecContext = mediaInfo->vMediaInfo.codecContext;
			codecContext = avcodec_alloc_context3(vcodec);
			if (nullptr == codecContext) {
				assert(false);
				break;
			}
			//codecContext->thread_count = std::thread::hardware_concurrency();
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
			if (nullptr != stream->metadata) {
				AVDictionaryEntry *entry = av_dict_get(stream->metadata, "rotate", nullptr, AV_DICT_IGNORE_SUFFIX);
				if (nullptr != entry) {
					int rotate = atoi(entry->value);
				}
			}
			mediaInfo->mVideoPlayHelper.setVideoInfo(convertPixelFormat(codecParameters->format), codecParameters->width, codecParameters->height);
			mediaInfo->mVideoPlayHelper.open();
			vThread = std::thread(&videoThread, &mediaInfo->vMediaInfo, notifyReadFrame);
		}

		if (audioIndex >= 0) {
			AVStream *stream = formatContext->streams[audioIndex];
			AVCodecParameters *codecParameters = stream->codecpar;
			AVCodec *acodec = avcodec_find_decoder(codecParameters->codec_id);
			if (nullptr == acodec) {
				assert(false);
				break;
			}
			mediaInfo->aMediaInfo.stream = stream;
			auto &codecContext = mediaInfo->aMediaInfo.codecContext;
			codecContext = avcodec_alloc_context3(acodec);
			//codecContext->thread_count = std::thread::hardware_concurrency();
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

            mediaInfo->mPlayHelper.setSampleInfo(2, 44100, EAudioFormatS16LE);
            mediaInfo->mPlayHelper.open();
            mediaInfo->mPlayHelper.setPlayState(EPlayStatePlaying);
			aThread = std::thread(&audioThread, &mediaInfo->aMediaInfo, notifyReadFrame);
		}
		
		mediaInfo->clockTime.setTimeMs(0);
		mediaInfo->clockTime.resume();

		lThread = std::thread(&loopThread, mediaInfo);
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
					return mediaInfo->exit || mediaInfo->seeking;
				}
				});

			if (mediaInfo->exit) {
				break;
			}
			if (mediaInfo->seeking){
				AVRational rational = { 1, AV_TIME_BASE };
				int64_t ts = ms2ts(rational, mediaInfo->seekMs);
				if ((err = avformat_seek_file(formatContext, -1, INT64_MIN, ts, INT64_MAX, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME)) < 0) {
					LogAvError(err);
					assert(false);
				}
				if (mediaInfo->aMediaInfo.streamIndex >= 0) {
					mediaInfo->aMediaInfo.flushPacket();
					mediaInfo->aMediaInfo.flushFrame();
					mediaInfo->aMediaInfo.putPacket(&flush_pkt);
					mediaInfo->mPlayHelper.flush();
				}
				if (mediaInfo->vMediaInfo.streamIndex >= 0) {
					mediaInfo->vMediaInfo.flushPacket();
					mediaInfo->vMediaInfo.flushFrame();
					mediaInfo->vMediaInfo.putPacket(&flush_pkt);
				}
				mediaInfo->seeking = false;
				mediaInfo->clockTime.setTimeMs(mediaInfo->seekMs);
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

	{
		std::lock_guard<std::mutex> lk(mediaInfo->aMediaInfo.mtx);
		mediaInfo->aMediaInfo.exit = true;
		mediaInfo->aMediaInfo.cv.notify_all();
	}
	{
		std::lock_guard<std::mutex> lk(mediaInfo->vMediaInfo.mtx);
		mediaInfo->vMediaInfo.exit = true;
		mediaInfo->vMediaInfo.cv.notify_all();
	}
	if (aThread.joinable()) {
		aThread.join();
	}
	if (vThread.joinable()) {
		vThread.join();
	}
	if (lThread.joinable()) {
		lThread.join();
	}
	mediaInfo->mPlayHelper.close();
}

PlayManager::PlayManager()
	: mData(new PlayManagerData())
{
	av_init_packet(&flush_pkt);
	flush_pkt.data = (uint8_t*)&flush_pkt;
}

PlayManager::~PlayManager() {
	delete mData;
	mData = nullptr;
}

bool PlayManager::openFile(const char *filePath) {
	assert(!mReadThread.joinable());

	mData->exit = false;
	mData->fileName = filePath;
	mReadThread = std::thread(&readThread, mData);
	return true;
}

bool PlayManager::setPlayState(uint32_t playState) {
	std::lock_guard<std::mutex> lk(mData->mtx);
	if (playState == EPlayStatePlaying) {
		mData->clockTime.resume();
	}
	else {
		mData->clockTime.pause();
	}
	mData->mPlayHelper.setPlayState(playState);
	return true;
}

bool PlayManager::close()
{
	{
		std::lock_guard<std::mutex> lk(mData->mtx);
		mData->exit = true;
		mData->cv.notify_all();
	}
	if (mReadThread.joinable()) {
		mReadThread.join();
	}
	return false;
}

OpenGLPlay & PlayManager::getVideoPlay()
{
	return mData->mVideoPlayHelper;
}

bool PlayManager::seek(int64_t ms) {
	std::lock_guard<std::mutex> lk(mData->mtx);
	mData->seeking = true;
	mData->seekMs = ms;
	mData->cv.notify_all();
	return true;
}

