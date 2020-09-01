//
// Created by chenyue on 2020/8/26.
//

#include "EncodeHelper.h"
#include <assert.h>
#include <map>
#include <algorithm>
#include "MacroDefine.h"
#include "Single.h"
#include "Log.h"
extern "C" {
#include "libavutil/opt.h"
}

#define MAX_SEND_FRAME_COUNT 40

#define LOGAVERROR(err) \
    LogAvError(err)

extern void LogAvError(int err);

static const int64_t MAX_MS = std::numeric_limits<int64_t>::max();
static const int64_t MIN_MS = std::numeric_limits<int64_t>::min();

struct PacketInfo{
    std::list<AVPacket*> packets;
	AVRational streamTimeBase;
    bool receivePacketEnd = false;
    int64_t lastWriteMS = MIN_MS;
};

struct WriteThreadInfo{
    std::mutex mtx;
    std::condition_variable cv;
    bool exit = false;
    bool running = false;
    AVFormatContext *formatContext;
    std::vector<PacketInfo> packetInfo;
};

extern int64_t ts2ms(const AVRational &rational, int64_t ts);

//获取可以写入的最大毫秒值
int64_t getMaxWriteMS(const std::vector<PacketInfo> &packetInfo){
    int64_t ms = MAX_MS;
    for (auto &info : packetInfo){
		if (info.receivePacketEnd) {
			continue;
		}
        if (info.packets.empty()){
			ms = (std::min)(ms, info.lastWriteMS);
        }else{
			ms = (std::min)(ms, ts2ms(info.streamTimeBase, info.packets.back()->pts));
        }
    }
    return ms;
}

void writeThread(WriteThreadInfo *pInfo){
    int err = 0;
    for(;;){
        std::unique_lock<std::mutex> lk(pInfo->mtx);
        pInfo->cv.wait(lk, [pInfo]()->bool{
			if (pInfo->exit) {
				return true;
			}
			else {
				for (auto &pkt : pInfo->packetInfo) {
					if (!pkt.packets.empty()) {
						return true;
					}
				}
				return false;
			}
        });
        if (pInfo->exit){
            break;
        }

        auto &packetInfo = pInfo->packetInfo;
        std::multimap<int64_t, AVPacket*> writePacket;
        int64_t maxMS = getMaxWriteMS(packetInfo);
		bool allFinished = true;
        for (auto &info : packetInfo){
			if (!info.receivePacketEnd) {
				allFinished = false;
			}
            auto iter = info.packets.begin();
            while ( iter != info.packets.end()){
                AVPacket *pkt = (*iter);
                int64_t curMS = ts2ms(info.streamTimeBase, pkt->pts);
                if (curMS <= maxMS){
                    writePacket.insert(std::make_pair(pkt->dts, pkt));
                    info.lastWriteMS = curMS;
                    iter = info.packets.erase(iter);
                }else{
                    break;
                }
            }
        }
        AVFormatContext *formatContext = pInfo->formatContext;
        lk.unlock();

        for (auto iter = writePacket.begin(); iter != writePacket.end(); ++iter){
            AVPacket *pkt = iter->second;
            if ((err = av_write_frame(formatContext, pkt)) < 0){
                LOGAVERROR(err);
                assert(false);
            }
			SC(Log).d("write frame stream:%d dts:%lld", pkt->stream_index, pkt->dts);
            av_packet_unref(pkt);
            av_packet_free(&pkt);
        }
		if (allFinished) {
			if ((err = av_write_trailer(formatContext)) < 0) {
				LOGAVERROR(err);
				assert(false);
			}
			break;
		}
    }

    std::lock_guard<std::mutex> lk(pInfo->mtx);
    pInfo->running = false;
}

void encodeThread(EncodeHelper::EncodeThreadInfo *pInfo) {
    WriteThreadInfo writeInfo;
    writeInfo.exit = false;
    writeInfo.running = true;
    {
        std::lock_guard<std::mutex> lk(pInfo->mtx);
        writeInfo.packetInfo.resize(pInfo->streamInfo.size());
		for (size_t i = 0; i < pInfo->streamInfo.size(); i++) {
			writeInfo.packetInfo[i].streamTimeBase = pInfo->streamInfo[i].streamTimeBase;
		}
        writeInfo.formatContext = pInfo->formatContext;
    }
    std::thread thread = std::thread(&writeThread, &writeInfo);

    int err = 0;
    AVPacket *pkt = av_packet_alloc();
    auto &mtx = pInfo->mtx;
    auto &cv = pInfo->cv;

    for (;;){
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [pInfo]()->bool {
            if (pInfo->exit){
                return true;
            }else{
                for (auto &streamInfo : pInfo->streamInfo){
                    if (!streamInfo.frames.empty()){
                        return true;
                    }
                }
                return false;
            }
        });
        if (pInfo->exit){
            break;
        }
        for (auto &streamInfo : pInfo->streamInfo){
            if (streamInfo.frames.empty()){
                continue;
            }
            /*if (streamInfo.sendFrameCount > MAX_SEND_FRAME_COUNT){
                continue;
            }*/
            AVFrame *frame = streamInfo.frames.front();
            streamInfo.frames.pop_front();
            if ((err = avcodec_send_frame(streamInfo.stream->codec, frame)) == 0){
                streamInfo.sendFrameCount++;
                if (nullptr != frame){
                    av_frame_unref(frame);
                    av_frame_free(&frame);
                }
            }else{
                LOGAVERROR(err);
                assert(false);
                goto ERROR;
            }
        }

        for (auto &streamInfo : pInfo->streamInfo){
            while (!streamInfo.receivePacketEnd){
                if ((err = avcodec_receive_packet(streamInfo.stream->codec, pkt)) == 0) {
                    if (nullptr == streamInfo.bsfContext){
                        AVPacket *tmpPacket = av_packet_alloc();
                        av_packet_move_ref(tmpPacket, pkt);
                        tmpPacket->stream_index = streamInfo.streamIndex;
                        streamInfo.sendFrameCount = 0;

                        std::lock_guard<std::mutex> lkWrite(writeInfo.mtx);
                        writeInfo.packetInfo[streamInfo.streamIndex].packets.push_back(tmpPacket);
                        writeInfo.cv.notify_one();
                    } else{
                        if ((err = av_bsf_send_packet(streamInfo.bsfContext, pkt)) < 0){
                            LogAvError(err);
                            assert(false);
                            goto ERROR;
                        }
                    }
                }else if (err == AVERROR_EOF){
                    streamInfo.receivePacketEnd = true;
                    if (nullptr == streamInfo.bsfContext){
                        std::lock_guard<std::mutex> lkWrite(writeInfo.mtx);
                        writeInfo.packetInfo[streamInfo.streamIndex].receivePacketEnd = true;
                        writeInfo.cv.notify_one();
                    }else{
                        if ((err = av_bsf_send_packet(streamInfo.bsfContext, nullptr)) < 0){
                            LogAvError(err);
                            assert(false);
                            goto ERROR;
                        }
                    }
                }else if (AVERROR(EAGAIN) == err){
                    break;
                }else{
                    LogAvError(err);
                    assert(false);
                    goto ERROR;
                }
            }
        }

        for (auto &streamInfo : pInfo->streamInfo){
            while (!streamInfo.bsfPacketEnd){
                if ((err = av_bsf_receive_packet(streamInfo.bsfContext, pkt)) == 0){
                    AVPacket *tmpPacket = av_packet_alloc();
                    av_packet_move_ref(tmpPacket, pkt);
                    tmpPacket->stream_index = streamInfo.streamIndex;
                    streamInfo.sendFrameCount = 0;

                    std::lock_guard<std::mutex> lkWrite(writeInfo.mtx);
                    writeInfo.packetInfo[streamInfo.streamIndex].packets.push_back(tmpPacket);
                    writeInfo.cv.notify_one();
                }else if (err == AVERROR_EOF){
                    streamInfo.bsfPacketEnd = true;
                    std::lock_guard<std::mutex> lkWrite(writeInfo.mtx);
                    writeInfo.packetInfo[streamInfo.streamIndex].receivePacketEnd = true;
                    writeInfo.cv.notify_one();
                }else if (AVERROR(EAGAIN) == err){
                    break;
                }else{
                    LogAvError(err);
                    assert(false);
                    goto ERROR;
                }
            }
        }

        bool allFinished = true;
        for (auto &streamInfo : pInfo->streamInfo){
            if (streamInfo.receivePacketEnd && streamInfo.bsfPacketEnd){
                continue;
            }
            allFinished = false;
            break;
        }
        if (allFinished){
            break;
        }
    }

    if (thread.joinable()){
        for (;;){
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait_for(lk, std::chrono::milliseconds(1), [pInfo](){
                return pInfo->exit;
            });
            if (pInfo->exit){
                break;
            }
            lk.unlock();
            
            std::lock_guard<std::mutex> lkWrite(writeInfo.mtx);
            if (!writeInfo.running){
                break;
            }
        }
    }

    ERROR:
    av_packet_free(&pkt);
    {
        std::lock_guard<std::mutex> lk(writeInfo.mtx);
        writeInfo.exit = true;
        writeInfo.cv.notify_one();
    }
    if (thread.joinable()){
		thread.join();
    }
    avformat_close_input(&pInfo->formatContext);
	SC(Log).d("write packet finished");
    return;
}

EncodeHelper::EncodeHelper()
{

}

EncodeHelper::~EncodeHelper() {

}

bool EncodeHelper::addStreamInfo(AVCodecParameters *parameters, AVRational encoderTimeBase, AVRational streamTimeBase) {
    std::lock_guard<std::mutex> lk(mEncodeThreadInfo.mtx);

    int err = 0;
    StreamInfo streamInfo;
    //AVCodecContext *codecContext = nullptr;
    AVCodecParameters *codecParameters = avcodec_parameters_alloc();
    //AVCodec *codec = avcodec_find_encoder(parameters->codec_id);

    if (/*nullptr == codec || */nullptr == codecParameters){
        assert(false);
        goto ERROR;
    }
    if ((err = avcodec_parameters_copy(codecParameters, parameters)) < 0){
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }
    /*if (nullptr == (codecContext = avcodec_alloc_context3(codec))){
        assert(false);
        goto ERROR;
    }*/
   /* if ((err = avcodec_parameters_to_context(codecContext, codecParameters)) < 0){
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }
    codecContext->thread_count = std::thread::hardware_concurrency();
    codecContext->time_base = encoderTimeBase;
    if ((err = avcodec_open2(codecContext, codec, nullptr)) < 0){
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }*/
    streamInfo.codecParameters = codecParameters;
    //streamInfo.codecContext = codecContext;
    streamInfo.streamTimeBase = streamTimeBase;
	streamInfo.encoderTimeBase = encoderTimeBase;
    streamInfo.streamIndex = mEncodeThreadInfo.streamInfo.size();
    mEncodeThreadInfo.streamInfo.push_back(streamInfo);
    return true;

ERROR:
    avcodec_parameters_free(&codecParameters);
    //avcodec_free_context(&codecContext);
    return false;
}

bool EncodeHelper::open(const char *outputFile) {
    assert(!mEncodeThread.joinable());
    int err = 0;

    std::lock_guard<std::mutex> lk(mEncodeThreadInfo.mtx);
    auto &formatContext = mEncodeThreadInfo.formatContext;
    if ((err = avformat_alloc_output_context2(&formatContext, nullptr, nullptr, outputFile)) < 0){
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }
	for (size_t i = 0; i < mEncodeThreadInfo.streamInfo.size(); i++) {
		StreamInfo &streamInfo = mEncodeThreadInfo.streamInfo[i];
        AVCodec* codec = avcodec_find_encoder(streamInfo.codecParameters->codec_id);
        AVStream *stream = avformat_new_stream(formatContext, nullptr);
        AVCodecParameters *codecParameters = stream->codecpar;

        AVRational streamTimeBase = streamInfo.streamTimeBase;
        if (streamInfo.codecParameters->codec_type == AVMEDIA_TYPE_VIDEO && false){
            auto &bsf = streamInfo.bsf;
            auto &bsfContext = streamInfo.bsfContext;
            bsf = av_bsf_get_by_name("h264_mp4toannexb");
            if ((err = av_bsf_alloc(bsf, &bsfContext)) < 0){
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            if ((err = avcodec_parameters_copy(bsfContext->par_in, streamInfo.codecParameters)) < 0) {
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            bsfContext->time_base_in = streamTimeBase;//pkt 的timebase， 是stream的timebase
            if ((err = av_bsf_init(bsfContext)) < 0){
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            if ((err = avcodec_parameters_copy(codecParameters, bsfContext->par_out)) < 0) {
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            streamTimeBase = bsfContext->time_base_out;
            streamInfo.bsfPacketEnd = false;
        }else{
            if ((err = avcodec_parameters_copy(codecParameters, streamInfo.codecParameters)) < 0){
                LOGAVERROR(err);
                assert(false);
                goto ERROR;
            }
            streamInfo.bsfPacketEnd = true;
        }

        stream->time_base = streamTimeBase;
		streamInfo.stream = stream;
		if ((err = avcodec_parameters_to_context(stream->codec, codecParameters)) < 0) {
			LOGAVERROR(err);
			assert(false);
			goto ERROR;
		}
        av_opt_set(stream->codec->priv_data, "preset", "fast", 0);
		stream->codec->time_base = streamInfo.encoderTimeBase;
		stream->codec->thread_count = std::thread::hardware_concurrency();
		stream->codec->qcompress = 0.9f;
		stream->codec->qmin = 30;
		stream->codec->qmax = 50;
		stream->codec->me_range = 16;
		stream->codec->max_qdiff = 4*20;
        
		if (codecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            stream->codec->pix_fmt = AV_PIX_FMT_YUV420P;
//			stream->codec->max_qdiff = 3 * 100;//视频中所有桢（包括i/b/P）的最大Q值差距
//			stream->codec->gop_size = 300;
//			stream->codec->refs = 200;
//			stream->codec->max_b_frames = 200;
//			stream->codec->bit_rate = 1024 * 10;//目标码率，采样码率越大，目标文件越大
//			stream->codec->bit_rate_tolerance = 8000 * 1024;// 码率误差，允许的误差越大，视频越小
//			stream->codec->i_quant_factor = 0.1f / 1000;//i 帧相对p帧的量化系数比，值越小，说明p帧的量化系数越大，视频越小
//			stream->codec->b_quant_factor = 4.9 * 1000;//b 帧相对p帧的量化系数比，值越大，b帧的量化系数越大，视频越小
//			stream->codec->me_pre_cmp = 2 * 10;//运动场景预判功能的力度。数值越大编码时间越长。
//			//B帧量化系数=b_quant_factor* p帧量化系数+b_quant_offset
		}
        if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            stream->codec->bit_rate = 2 * 1000 * 1000;
            stream->codec->rc_buffer_size = 4 * 1000 * 1000;
            stream->codec->rc_max_rate = 2 * 1000 * 1000;
            stream->codec->rc_min_rate = 2.5 * 1000 * 1000;
        }
		stream->codec->codec_tag = 0;
		if ((err = avcodec_open2(stream->codec, codec, nullptr)) < 0) {
			LOGAVERROR(err);
			assert(false);
			goto ERROR;
		}
		
		/*if (formatContext->oformat->flags & AVFMT_GLOBALHEADER) {
			stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
		}*/
		SC(Log).d("stream");
    }
    if (formatContext->oformat->flags & AVFMT_GLOBALHEADER) {
        formatContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    if ((err = avio_open(&formatContext->pb, outputFile, AVIO_FLAG_WRITE)) < 0){
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }
    /*if ((err = avformat_init_output(formatContext, nullptr)) < 0) {
        LOGAVERROR(err);
        assert(false);
        goto ERROR;
    }*/
    AVDictionary* muxer_opts = NULL;
    //if (AVSTREAM_INIT_IN_WRITE_HEADER == err) {
        if ((err = avformat_write_header(formatContext, &muxer_opts)) < 0) {
            LOGAVERROR(err);
            assert(false);
            goto ERROR;
        }
    //}

    mEncodeThreadInfo.exit = false;
    mEncodeThread = std::thread(&encodeThread, &mEncodeThreadInfo);
    return true;

ERROR:
    avformat_free_context(formatContext);
    formatContext = nullptr;
    return false;
}

bool EncodeHelper::addFrame(uint32_t streamIndex, AVFrame *frame) {
    std::lock_guard<std::mutex> lk(mEncodeThreadInfo.mtx);

    if (nullptr != frame){
        AVFrame *clone = av_frame_clone(frame);
        if (nullptr != clone){
            mEncodeThreadInfo.streamInfo[streamIndex].frames.push_back(clone);
            mEncodeThreadInfo.cv.notify_one();
            return true;
        }else{
            assert(false);
            return false;
        }
    }else{
        mEncodeThreadInfo.streamInfo[streamIndex].frames.push_back(nullptr);
        mEncodeThreadInfo.cv.notify_one();
        return true;
    }
}


