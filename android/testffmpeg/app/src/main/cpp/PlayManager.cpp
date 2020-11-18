//
// Created by chenyue on 2020/8/8.
//

#include "PlayManager.h"
#include <assert.h>
#include <algorithm>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"
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
#include "reverdhelper.h"
#include "BaseTime.h"
#include "sox.h"
#include "reverb.h"
#include "equalizer.h"
//#include "freeverb/myexport.h"

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
		mylog_e("%s", szBuf);
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

void my_reverb_frame(reverb_state_st rv, AVFrame *frame) {
	BaseTime bastTime;
	reverb_frame(rv, frame);
    mylog_i("reverb_frame %lld", bastTime.getCurrentTimeUs());
}

#define REVERB_BUF_LEN 4096

void my_reverb_frame(struct _my_reverb_t *reverb, AVFrame *frame) {
	BaseTime bastTime;
	if (frame->format == AV_SAMPLE_FMT_FLTP) {
		int bytes = frame->nb_samples * sizeof(float);
		float *tmp[10];
		int offset = 0;
		while (bytes > 0)
		{
			for (int c = 0; c < frame->channels; c++) {
				tmp[c] = (float*)(frame->data[c] + offset);
			}
			int len = bytes > REVERB_BUF_LEN ? REVERB_BUF_LEN : bytes;
			process_reverb(reverb, tmp, tmp, len / sizeof(float));
			offset += len;
			bytes -= len;
		}
	}
	else {
		assert(false);
	}
	mylog_i("reverb_frame2 %lld sampleCount:%d", bastTime.getCurrentTimeUs(), frame->nb_samples);
}
#define EQ_BUFFER_SIZE 2048
std::vector<float> g_buffer;
void my_equalizer_frame(struct _equalizer_t* p, AVFrame *frame) {
	BaseTime bastTime;
	if (frame->format == AV_SAMPLE_FMT_FLTP) {
		g_buffer.resize(EQ_BUFFER_SIZE, 0.0f);
		assert(g_buffer.size() > frame->nb_samples);
		for (int i = 0; i < frame->channels; i++) {
			memcpy(g_buffer.data(), frame->data[i], frame->nb_samples * sizeof(float));
			process_equalizer(p, g_buffer.data(), g_buffer.size());
			memcpy(frame->data[i], g_buffer.data(), frame->nb_samples * sizeof(float));
		}
	}
	else {
		assert(false);
	}
	mylog_i("equalizer_frame %lld sampleCount:%d", bastTime.getCurrentTimeUs(), frame->nb_samples);
}

struct ReverbConfig {
	double room_scale;
	double pre_delay_ms;
	double reverbe_rance;
	double hf_damping;
	double tone_low;
	double tone_high;
	double wet_gain_dB;
	double dry_gain_dB;
	double stereo_depth;
	int wet_only;
};

static void audioThread(MediaInfo *pInfo, std::function<void()> notifyReadFrame) {
	auto &info = *pInfo;
	auto &mtx = info.mtx;
	auto &cv = info.cv;
    AVFrame *frame = av_frame_alloc();
	const AVFilter *abuffersrc = avfilter_get_by_name("abuffer");
	const AVFilter *abuffersink = avfilter_get_by_name("abuffersink");
	AVFilterContext *in = nullptr;
	AVFilterContext *out = nullptr;
	AVFilterContext *aecho = nullptr;
	AVFilterGraph *graph = avfilter_graph_alloc();
	const char *args = "0.8:0.88:60:0.4";
	int ret = 0;
	char szBufArg[128] = { 0 };
	AVRational time_base = pInfo->stream->time_base;
	AVCodecContext *dec_ctx = pInfo->codecContext;

	ReverbConfig reverbConfigs[] = {
		{ 70,   20,    40,     99,      100, 50,   -12,  0,    70,    false },//Vocal I
		{ 16,   8,     80,     0,       0,   100,  -6,   0,    100,   false },//Bathroom
		{ 85,   10,    40,     50,      100, 80,    0,   -6,   90,    false },//Large Room
		{ 90,   32,    60,     50,      100, 50,    0,   -12,  100,   false } ,//Church Hall
		{ 60,   0,    40,     90,      50, 100,    1,   0,  80,   false }
	};
	int reverbConfigIndex = 4;
	double sample_rate_Hz = pInfo->codecContext->sample_rate;
	double wet_gain_dB = reverbConfigs[reverbConfigIndex].wet_gain_dB;//湿增益（dB）：对混合物中的混响（“湿”）分量应用音量调整。相对于“干增益”（如下）增加该值，可以增加混响的强度。
	double dry_gain_dB = reverbConfigs[reverbConfigIndex].dry_gain_dB;//干增益（dB）：对混音中的原始（“干”）音频应用音量调整。相对于“湿增益”（如上）增加该值会降低混响的强度。如果“湿增益”和“干增益”值相同，则要输出到音轨的湿效果和干音频的混合将通过此值变得更大或更柔和（假设未选中下面的“仅限湿”选项）。
	double room_scale = reverbConfigs[reverbConfigIndex].room_scale; /* % *///房间大小（%）：设置模拟房间的大小。0%像壁橱，100%像大教堂或大礼堂。高值将模拟大房间的混响效果，低值将模拟小房间的效果。
	double reverberance = reverbConfigs[reverbConfigIndex].reverbe_rance;///* % *///混响（%）：设置混响尾部的长度。这决定了在原始声音被混响结束后，混响持续多久，从而模拟房间声学的“活跃”。对于任何给定的混响值，对于较大的房间尺寸，尾部将更大。
	double hf_damping = reverbConfigs[reverbConfigIndex].hf_damping;/* % *///阻尼（%）：增加阻尼会产生更“静音”的效果。混响没有建立太多，高频衰减比低频快。模拟混响中高频的吸收。
	double pre_delay_ms = reverbConfigs[reverbConfigIndex].pre_delay_ms;//预延迟（ms）：在初始输入开始后，将混响的开始延迟设定的时间。也延迟了混响的开始。最大预延迟为200毫秒。仔细调整此参数可以提高结果的清晰度。
	double stereo_depth = reverbConfigs[reverbConfigIndex].stereo_depth;// 立体声宽度（%）：仅为立体声音轨设置混响效果的明显“宽度”。增加此值会在左右声道之间应用更多变化，从而产生更“宽敞”的效果。设置为零时，效果将独立应用于左侧和右侧通道。
	double tone_low = reverbConfigs[reverbConfigIndex].tone_low;//音调低（%）：将此控件设置为低于100%会降低混响的低频分量，从而产生较少的“隆隆”效果。
	double tone_high = reverbConfigs[reverbConfigIndex].tone_high;//音调高（%）：将此控件设置为低于100%会降低混响的高频分量，从而产生不太“明亮”的效果。
	int wet_only = reverbConfigs[reverbConfigIndex].wet_only;//仅湿式：当选中此控件时，结果输出中将只有湿信号（增加混响），并且原始音频将被删除。这在预览效果时很有用，但在大多数情况下，应用效果时应取消选中此选项。
	double buffer_size = REVERB_BUF_LEN;
	struct _my_reverb_t *reverb = create_reverb(pInfo->codecContext->channels, sample_rate_Hz, wet_gain_dB, dry_gain_dB, room_scale, reverberance, hf_damping, pre_delay_ms, stereo_depth, tone_low, tone_high, wet_only, buffer_size);

	//double hz[] = { 31, 62, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 };
	double hz[] = { 20, 25, 31, 40, 50, 63, 80, 100, 125, 160, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1600, 2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000 };
	struct _equalizer_t *eq = create_equalizer(sample_rate_Hz, EQ_BUFFER_SIZE, hz, _countof(hz));
	double eqs[_countof(hz)] = { 0., 0, 0., 0., 0., 0., 0., -0., -0., -0. };
	set_equalizer_eq(eq, eqs, _countof(eqs));

	//set_wet_only(reverb, 1);
	//my_progenitor_t progenitor = alloc_my_progenitor();
#ifdef _WIN32
	if (!dec_ctx->channel_layout)
		dec_ctx->channel_layout = av_get_default_channel_layout(dec_ctx->channels);
	snprintf(szBufArg, sizeof(szBufArg),
		"time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=%llu",
		time_base.num, time_base.den, dec_ctx->sample_rate,
		av_get_sample_fmt_name(dec_ctx->sample_fmt), dec_ctx->channel_layout);
	if ((ret = avfilter_graph_create_filter(&in, abuffersrc, "in", szBufArg, nullptr, graph)) < 0) {
		LogAvError(ret);
		assert(false);
	}

	if ((ret = avfilter_graph_create_filter(&out, avfilter_get_by_name("abuffersink"), "out", nullptr, nullptr, graph)) < 0) {
		LogAvError(ret);
		assert(false);
	}
	if ((ret = avfilter_graph_create_filter(&aecho, avfilter_get_by_name("aecho"), nullptr, args, nullptr, graph)) < 0) {
		LogAvError(ret);
		assert(false);
	}
	if ((ret = avfilter_link(in, 0, aecho, 0)) < 0) {
		LogAvError(ret);
		assert(false);
	}
	if ((ret = avfilter_link(aecho, 0, out, 0)) < 0) {
		LogAvError(ret);
		assert(false);
	}
	if ((ret = avfilter_graph_config(graph, nullptr)) < 0) {
		LogAvError(ret);
		assert(false);
	}
#endif
	
	reverb_state_st rv = alloc_reverb_state();
	set_reverb(rv, "longreverb1", pInfo->codecContext->sample_rate);

	for (;;) {
		std::unique_lock<std::mutex> lk(info.mtx);
		cv.wait(lk, [&info]()->bool {
			return info.exit || (info.frames.size() < MAX_FRAME_SIZE);
			});

		if (info.exit){
		    break;
		}

		ret = avcodec_receive_frame(info.codecContext, frame);
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
#if 0
			info.receivedFrame = true;
			assert(frame->format == AV_SAMPLE_FMT_FLTP);
			processreplace(progenitor, (float*)frame->data[0], (float*)frame->data[1], (float*)frame->data[0], (float*)frame->data[1], frame->nb_samples);


			AVFrame *tmpFrame = av_frame_alloc();
			av_frame_move_ref(tmpFrame, frame);
			info.frames.push_back(tmpFrame);
			info.cv.notify_all();
#endif
#if 1
			info.receivedFrame = true;
			//my_reverb_frame(rv, frame);
			//my_reverb_frame(reverb, frame);
			my_equalizer_frame(eq, frame);
			AVFrame *tmpFrame = av_frame_alloc();
			av_frame_move_ref(tmpFrame, frame);
			info.frames.push_back(tmpFrame);
			info.cv.notify_all();
#endif
#if 0
			AVFrame *tmpFrame = av_frame_alloc();
			av_frame_move_ref(tmpFrame, frame);
			info.frames.push_back(tmpFrame);
			info.cv.notify_all();
#endif
#if 0
			if ((ret = av_buffersrc_write_frame(in, frame)) < 0) {
				LogAvError(ret);
				assert(false);
			}
			av_frame_unref(frame);
			bool notify = false;
			while (av_buffersink_get_frame(out, frame) >= 0 ){
				AVFrame *tmpFrame = av_frame_alloc();
				av_frame_move_ref(tmpFrame, frame);
				info.frames.push_back(tmpFrame);
				notify = true;
			}
			if (notify) {
				info.cv.notify_all();
			}
#endif
		}
	}
    av_frame_free(&frame);
#ifdef _WIN32
	avfilter_graph_free(&graph);
#endif
	free_reverb_state(rv);
	//free_my_progenitor(progenitor);
	delete_reverb(reverb);
	delete_equalizer(eq);
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
    int64_t lastPts = -1;

    for (;;) {
		{
			std::lock_guard<std::mutex> lk(mediaInfo->mtx);
			if (mediaInfo->exit) {
				break;
			}
		}
		int64_t ms = -1;
        {
            std::lock_guard<std::mutex> lk(aMediaInfo.mtx);
            if (aMediaInfo.streamIndex >= 0){
                while (playHelper.getQueuedAudioSize() < AUDIO_BUFFER_SIZE && !aMediaInfo.frames.empty()) {
                    AVFrame *frame = aMediaInfo.frames.front();
                    aMediaInfo.frames.pop_front();

					lastPts = frame->pts;
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
                if (-1 != lastPts){
                    ms = ts2ms(aMediaInfo.stream->time_base, lastPts);
                    ms -= (int64_t)playHelper.getQueuedAudioSize() * 1000 / bytePerSecond;
                }
                aMediaInfo.cv.notify_all();
            }
        }

        {
            std::lock_guard<std::mutex> lk(vMediaInfo.mtx);
            if (vMediaInfo.streamIndex >= 0 && ms >= 0){
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
			codecContext->thread_count = std::thread::hardware_concurrency();
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
			float xRotate = 180.f, yRotate = 0.f, zRotate = 0.f;
			if (nullptr != stream->metadata) {
				AVDictionaryEntry *entry = av_dict_get(stream->metadata, "rotate", nullptr, AV_DICT_IGNORE_SUFFIX);
				if (nullptr != entry) {
					zRotate = (float)atof(entry->value);
				}
			}
			mediaInfo->mVideoPlayHelper.setRotate(xRotate, yRotate, zRotate);
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
			codecContext->thread_count = std::thread::hardware_concurrency();
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

		mediaInfo->seeking = true;
		mediaInfo->seekMs = 26800;

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
	avformat_close_input(&formatContext);
}

PlayManager::PlayManager()
	: mData(new PlayManagerData())
	, mReadThread()
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

