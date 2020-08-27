//
// Created by chenyue on 2020/8/25.
//

#include "FFMPEGTest.h"
#include <assert.h>
#include <thread>
#include <map>
#include <list>
#include <vector>
extern "C" {
#include "libavformat/avformat.h"
}

#include "EncodeHelper.h"

extern void LogAvError(int err);
namespace FFMPEGTest{
    void dump_format(AVFormatContext *formatContext, const char *filename){
        for (int i = 0; i < formatContext->nb_streams; i++){
            av_dump_format(formatContext, i, filename, 0);
        }
    }

    void test_demux_mux(const char *inputfile, const char *outputfile){
        AVFormatContext *formatContext = nullptr, *outputFormatContext = nullptr;
        AVCodecContext *codecContext = nullptr;
        AVPacket *pkt = av_packet_alloc();
        AVFrame *frame = av_frame_alloc();
        int err = 0;

        do
        {
            if ((err = avformat_open_input(&formatContext, inputfile, nullptr, nullptr)) < 0) {
                LogAvError(err);
                assert(false);
                break;
            }
            if (0 != (err = avformat_find_stream_info(formatContext, nullptr))) {
                LogAvError(err);
                assert(false);
                break;
            }
            if ((err = avformat_alloc_output_context2(&outputFormatContext, nullptr, nullptr, outputfile)) < 0){
                LogAvError(err);
                assert(false);
                break;
            }
            for (int i = 0; i < formatContext->nb_streams; i++){
                AVStream *stream = formatContext->streams[i];
                AVStream *outputStream = avformat_new_stream(outputFormatContext, stream->codec->codec);
                if ((err = avcodec_copy_context(outputStream->codec, stream->codec)) < 0){
                    LogAvError(err);
                    assert(false);
                    break;
                }
                outputStream->codec->codec_tag = 0;
                if (outputFormatContext->oformat->flags & AVFMT_GLOBALHEADER){
                    outputStream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
                }
            }
			dump_format(formatContext, inputfile);
			//dump_format(outputFormatContext, outputfile);
			if ((err = avio_open(&outputFormatContext->pb, outputfile, AVIO_FLAG_WRITE)) < 0) {
				LogAvError(err);
				assert(false);
				break;
			}
			if ((err = avformat_write_header(outputFormatContext, nullptr)) < 0) {
				LogAvError(err);
				assert(false);
				break;
			}
            for (;;) {
                if ((err = av_read_frame(formatContext, pkt)) < 0) {
                    if (AVERROR_EOF == err) {
                        break;
                    } else {
                        LogAvError(err);
                        assert(false);
                        break;
                    }
                } else {
                    AVRational inputRational = formatContext->streams[pkt->stream_index]->time_base;
                    AVRational outputRational = outputFormatContext->streams[pkt->stream_index]->time_base;
                    pkt->pts = av_rescale_q_rnd(pkt->pts, inputRational, outputRational, (AVRounding) (AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
                    pkt->dts = av_rescale_q_rnd(pkt->dts, inputRational, outputRational, (AVRounding) (AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
                    pkt->duration = av_rescale_q(pkt->duration, inputRational, outputRational);
                    if ((err = av_write_frame(outputFormatContext, pkt)) < 0) {
                        LogAvError(err);
                        assert(false);
                        break;
                    }
                    av_packet_unref(pkt);
                }
            }
			if ((err = av_write_trailer(outputFormatContext)) < 0) {
				LogAvError(err);
				assert(false);
				break;
			}
        } while (false);

        av_packet_free(&pkt);
        av_frame_free(&frame);

        avcodec_close(codecContext);
        avcodec_free_context(&codecContext);

        avformat_close_input(&formatContext);
        avformat_close_input(&outputFormatContext);
    }
    struct DecodeInfo{
        bool receiveFrameEnd = false;
        AVCodecContext *codecContext = nullptr;
    };

    void test_decode_encode(const char *inputfile, const char *outputfile){
        AVFormatContext *formatContext = nullptr;
        AVPacket *pkt = av_packet_alloc();
        AVFrame *frame = av_frame_alloc();
        int err = 0;
        bool readPacketEnd = false;
        EncodeHelper encodeHelper;
        std::vector<DecodeInfo>  decodeInfo;
        AVCodecParameters *codecParameters = avcodec_parameters_alloc();

        if ((err = avformat_open_input(&formatContext, inputfile, nullptr, nullptr)) < 0) {
            LogAvError(err);
            assert(false);
            goto ERROR;
        }
        if (0 != (err = avformat_find_stream_info(formatContext, nullptr))) {
            LogAvError(err);
            assert(false);
            goto ERROR;
        }
        decodeInfo.resize(formatContext->nb_streams);
        for (int i = 0; i < formatContext->nb_streams; i++){
            auto &info = decodeInfo[i];
            AVStream *stream = formatContext->streams[i];
            AVCodecParameters *codecpar = stream->codecpar;
            AVCodec *decodec = avcodec_find_decoder(codecpar->codec_id);
            if (nullptr == decodec){
                assert(false);
                goto ERROR;
            }
            info.codecContext = avcodec_alloc_context3(decodec);
            if ((err = avcodec_parameters_to_context(info.codecContext, codecpar)) < 0){
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            if ((err = avcodec_open2(info.codecContext, nullptr, nullptr)) < 0){
                LogAvError(err);
                assert(false);
                goto ERROR;
            }
            if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO || codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
                codecParameters->codec_type = codecpar->codec_type;
                codecParameters->codec_id = codecpar->codec_id;
                codecParameters->bit_rate = codecpar->bit_rate;
                codecParameters->format = codecpar->format;
                if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
                    codecParameters->height = codecpar->height;
                    codecParameters->width = codecpar->width;
                    codecParameters->sample_aspect_ratio = codecpar->sample_aspect_ratio;
                }else{
                    codecParameters->sample_rate = codecpar->sample_rate;
                    codecParameters->channel_layout = codecpar->channel_layout;
                    codecParameters->channels = codecpar->channels;
                }
            }else{
                if ((err = avcodec_parameters_copy(codecParameters, codecpar)) < 0){
                    LogAvError(err);
                    assert(false);
                    goto ERROR;
                }
            }
            if (!encodeHelper.addStreamInfo(codecParameters, stream->time_base)){
                assert(false);
                goto ERROR;
            }
        }
        if (!encodeHelper.open(outputfile)){
            assert(false);
            goto ERROR;
        }
        decodeInfo.resize(formatContext->nb_streams);
        for (;;) {
            if (!readPacketEnd) {
                if ((err = av_read_frame(formatContext, pkt)) == 0) {
                    AVCodecContext *codecContext = decodeInfo[pkt->stream_index].codecContext;
                    if ((err = avcodec_send_packet(codecContext, pkt)) < 0) {
                        LogAvError(err);
                        av_packet_unref(pkt);
                        assert(false);
                        goto ERROR;
                    }
                    av_packet_unref(pkt);
                }
                else {
                    if (AVERROR_EOF == err) {
                        //读取packet完毕了，每个stream发送一个null frame，刷新剩余的缓存
                        readPacketEnd = true;
                        for (size_t i = 0; i < formatContext->nb_streams; i++){
                            AVCodecContext *codecContext = decodeInfo[i].codecContext;
                            if ((err = avcodec_send_packet(codecContext, nullptr)) < 0) {
                                LogAvError(err);
                                assert(false);
                                goto ERROR;
                            }
                        }
                    }
                    else {
                        LogAvError(err);
                        assert(false);
                        goto ERROR;
                    }
                }
            }

            for (size_t i = 0; i < formatContext->nb_streams; i++){
                if (decodeInfo[i].receiveFrameEnd) {
                    continue;
                }
                for (;;) {
                    AVCodecContext *codecContext = decodeInfo[i].codecContext;
                    if ((err = avcodec_receive_frame(codecContext, frame)) == 0) {
						if (!encodeHelper.addFrame(i, frame)) {
							assert(false);
						}
                        av_frame_unref(frame);
                    }
                    else {
                        if (AVERROR_EOF == err) {
                            decodeInfo[i].receiveFrameEnd = true;
                            encodeHelper.addFrame(i, nullptr);
                            break;
                        }
                        else if (AVERROR(EAGAIN) == err) {
                            break;
                        }
                        else {
                            LogAvError(err);
                            assert(false);
                            break;
                        }
                    }
                }
            }
            bool receivePacketEnd = true;
            for (auto &info : decodeInfo){
                if (!info.receiveFrameEnd){
                    receivePacketEnd = false;
                    break;
                }
            }
            if (receivePacketEnd) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        ERROR:
        avcodec_parameters_free(&codecParameters);
        av_packet_free(&pkt);
        av_frame_free(&frame);
        avformat_close_input(&formatContext);

		getchar();
    }
}