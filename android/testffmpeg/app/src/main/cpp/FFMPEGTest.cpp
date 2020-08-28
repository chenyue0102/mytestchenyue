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
			AVRational encodeRate = stream->codec->time_base;
            if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO || codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
                codecParameters->codec_type = codecpar->codec_type;
                codecParameters->codec_id = codecpar->codec_id;
				codecParameters->format = codecpar->format;
                codecParameters->bit_rate = codecpar->bit_rate;
                if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
					codecParameters->width = codecpar->width;
                    codecParameters->height = codecpar->height;
                    codecParameters->sample_aspect_ratio = codecpar->sample_aspect_ratio;
					codecParameters->bit_rate = 1024 * 500;
					//codecParameters->field_order = codecpar->field_order;
#if 0
					encodeRate.num = 1;
					encodeRate.den = 25;
					codecParameters->extradata = (uint8_t*)av_mallocz(codecpar->extradata_size);
					memcpy(codecParameters->extradata, codecpar->extradata, codecpar->extradata_size);
					codecParameters->extradata_size = codecpar->extradata_size;
#endif
#if 0
					codecParameters->bits_per_coded_sample = 24;
					codecParameters->bits_per_raw_sample = 8;
					codecParameters->field_order = codecpar->field_order;
					codecParameters->color_primaries = codecpar->color_primaries;
					codecParameters->color_trc = codecpar->color_trc;
					codecParameters->color_space = codecpar->color_space;
					codecParameters->chroma_location = codecpar->chroma_location;
#endif
                }else{
                    codecParameters->sample_rate = codecpar->sample_rate;
                    codecParameters->channel_layout = codecpar->channel_layout;
                    codecParameters->channels = codecpar->channels;
					codecParameters->frame_size = codecpar->frame_size;
#if 0
					codecParameters->extradata = (uint8_t*)av_mallocz(codecpar->extradata_size);
					memcpy(codecParameters->extradata, codecpar->extradata, codecpar->extradata_size);
					codecParameters->extradata_size = codecpar->extradata_size;
#endif
                }
            }else{
                if ((err = avcodec_parameters_copy(codecParameters, codecpar)) < 0){
                    LogAvError(err);
                    assert(false);
                    goto ERROR;
                }
            }
            if (!encodeHelper.addStreamInfo(codecParameters, encodeRate, stream->time_base)){
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

    struct AVCDecoderConfigurationRecord{
        uint8_t configurationVersion;           //0x01
        uint8_t AVCProfileIndication;
        uint8_t profile_compatibility;
        uint8_t AVCLevelIndication;
        uint8_t lengthSizeMinusOne;//0b111111aa
        //uint8_t numOfSequenceParameterSets;//0b111aaaaa
        //uint16_t sequenceParameterSetLength
        //sequenceParameterSetNALUnit
        //uint8_t numOfPictureParameterSets;
        //uint16_t pictureParameterSetLength
        //pictureParameterSetNALUnit
    };

    enum {
        HighProfile = 0x64,
    };
    enum{
        Version1 = 0x01,
    };

    enum{
        Level40 = 40,
    };
    enum NALType{
        NALTypeSPS = 0b00111,//序列参数集SPS
        NALTypePPS = 0b01000,//图像参数集PPS
        NALTypeIDR = 0b00101,//IDR图像中的片(I帧)
    };
    struct SequenceParameterSet{
        uint8_t type;//0b0aabbbbb  aa为参考级别 bbbbb为nal单元类型
        uint8_t profile_idc;
        uint8_t constraint_set_flag; //0babcd0000 0 mean We’re not going to honor constraints.
        uint8_t level_idc;
    };
    /*
    01 64 00 28
    ff
    e1
    00 1b
    67 64 00 28    ac d9 40 78    02 27 e5 c0    44 00 00 03    00 04 00 00   03 00 c8 3c   60 c6 58
    01
    00 06
    68 eb e3 cb 22 c0
     */

    void setExtraData(AVCodecParameters *codecParameters){
        if (codecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
            if (codecParameters->codec_id == AV_CODEC_ID_H264){
                uint16_t sequenceParameterSetLength = 0;
                uint16_t pictureParameterSetLength = 0;
                size_t extraSize = sizeof(AVCDecoderConfigurationRecord) + sizeof(uint8_t) + sizeof(uint16_t) + sequenceParameterSetLength + sizeof(uint8_t) + sizeof(uint16_t) + pictureParameterSetLength;
                codecParameters->extradata = (uint8_t*)av_mallocz(extraSize);
                AVCDecoderConfigurationRecord record;
                record.configurationVersion = Version1;
                record.AVCProfileIndication = HighProfile;
                record.profile_compatibility = 0x00;
                record.AVCLevelIndication = Level40;
                record.lengthSizeMinusOne = 0xff;
                memcpy(codecParameters->extradata, &record, sizeof(record));
                int offset = sizeof(record);
                codecParameters->extradata[offset] =
                codecParameters->extradata_size = extraSize;
            }
        }
    }
}