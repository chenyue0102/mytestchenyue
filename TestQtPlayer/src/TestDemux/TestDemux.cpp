// TestDemux.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "swresample.lib")

static double r2d(AVRational r)
{
	return r.den == 0 ? 0.0 : (double)r.num / r.den;
}

int main()
{
	std::cout << "TestDemux" << std::endl;
	//初始化封装
	av_register_all();

	//初始化网络库，可以打开rtsp(网络摄像机)，rtmp(直播)，http(网络直播)协议的流媒体视频
	avformat_network_init();

	//注册解码器
	avcodec_register_all();

	//参数设置，如rtsp延时时间
	AVDictionary *opts = nullptr;
	//设置rtsp流已tcp协议打开
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);
	//网络延时时间
	av_dict_set(&opts, "max_delay", "500", 0);

	AVFormatContext *ic = nullptr;//解封装上下文
#if 1
	const char *path = "C:/Users/chenyue/Desktop/Wildlife.wmv";
#else
	const char *path = "C:/Users/chenyue/Desktop/MOV_1073.mp4";
#endif
	int ret = avformat_open_input(
		&ic, 
		path, 
		nullptr, //自动选择解封器
		&opts	//参数设置
	);

	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}

	//获取流信息
	ret = avformat_find_stream_info(ic, 0);

	//总时长
	int total = ic->duration / AV_TIME_BASE; //单位秒
	std::cout << "total:" << total << std::endl;

	//打印视频流详细信息
	av_dump_format(
		ic, 
		0, 
		nullptr, 
		0  //0输入文件，1输出输出
	);

	//音视频索引
	int videoStream = 0;
	int audioStream = 0;

	//获取音视频流信息，遍历或者函数获取
	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVStream *as = ic->streams[i];
		//视频
		if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			std::cout << "视频" << std::endl;
			//编码,AVCodecID
			std::cout << "codec_id:" << as->codecpar->codec_id << std::endl;
			//帧率
			std::cout << "fps:" << r2d(as->avg_frame_rate) << std::endl;
			//有可能没有
			std::cout << "width:" << as->codecpar->width << std::endl;
			std::cout << "height:" << as->codecpar->height << std::endl;
			
		}
		//音频
		else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			std::cout << "音频" << std::endl;
			//编码,AVCodecID
			std::cout << "codec_id:" << as->codecpar->codec_id << std::endl;
			//帧率,一帧数据存储的是一定量的样本数
			std::cout << "fps:" << r2d(as->avg_frame_rate) << std::endl;
			//一帧数据的单通道的样本数量，frame_size * channel * 一个样本数量 = 一帧大小
			std::cout << "frame_size:" << as->codecpar->frame_size << std::endl;
			std::cout << "sample_rate:" << as->codecpar->sample_rate << std::endl;
			//AVSampleFormat
			std::cout << "format:" << as->codecpar->format << std::endl;
			//通道数
			std::cout << "channel:" << as->codecpar->channels << std::endl;
		}
	}

	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);

	//找到视频解码器
	AVCodec *vcodec = avcodec_find_decoder(ic->streams[videoStream]->codecpar->codec_id);
	if (nullptr == vcodec)
	{
		std::cout << "not find " << ic->streams[videoStream]->codecpar->codec_id << std::endl;
		getchar();
		return -1;
	}
	std::cout << "find " << ic->streams[videoStream]->codecpar->codec_id << std::endl;
	//创建解码器上下文
	AVCodecContext *vcc = avcodec_alloc_context3(vcodec);
	//配置解码器参数
	avcodec_parameters_to_context(vcc, ic->streams[videoStream]->codecpar);
	//设置8线程解码
	vcc->thread_count = 8;
	//打开解码器上下文
	ret = avcodec_open2(vcc, 0, 0);
	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}
	std::cout << "avcodec_open2 success" << std::endl;


	//找到音频解码器
	AVCodec *acodec = avcodec_find_decoder(ic->streams[audioStream]->codecpar->codec_id);
	if (nullptr == acodec)
	{
		std::cout << "not find " << ic->streams[audioStream]->codecpar->codec_id << std::endl;
		getchar();
		return -1;
	}
	std::cout << "find " << ic->streams[audioStream]->codecpar->codec_id << std::endl;
	//创建解码器上下文
	AVCodecContext *acc = avcodec_alloc_context3(acodec);
	//配置解码器参数
	avcodec_parameters_to_context(acc, ic->streams[audioStream]->codecpar);
	//设置8线程解码
	acc->thread_count = 8;
	//打开解码器上下文
	ret = avcodec_open2(acc, 0, 0);
	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}
	std::cout << "avcodec_open2 success" << std::endl;

	//读取帧
	//malloc AVPacket init AVPacket
	AVPacket *pkt = av_packet_alloc();
	AVFrame *frame = av_frame_alloc();//frame占用空间大
	//像素格式与尺寸转换上下文
	SwsContext *vctx = nullptr;
	//格式转换后的缓冲区
	unsigned char *rgb = nullptr;
	//音频重采样与格式转换
	//声道，格式，样本率
	unsigned char *pcm = nullptr;
	SwrContext *actx = swr_alloc();
	actx = swr_alloc_set_opts(
		actx,
		av_get_default_channel_layout(2),//输出格式，2通道
		AV_SAMPLE_FMT_S16,//输出样本格式
		acc->sample_rate,//输出采样率，1秒钟，音频样本数量
		av_get_default_channel_layout(acc->channels),//输入
		acc->sample_fmt,
		acc->sample_rate,
		0,0);
	ret = swr_init(actx);
	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}
	for (;;)
	{

		ret = av_read_frame(ic, pkt);
		if (0 != ret)
		{
			//循环播放
			int ms = 3000;
			long long pos = (double)ms / 1000 * r2d(ic->streams[pkt->stream_index]->time_base);
			av_seek_frame(ic, videoStream, pos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
			break;
		}
		std::cout << "size:" << pkt->size << std::endl;
		//显示时间
		std::cout << "pts:" << pkt->pts << std::endl;
		//毫秒
		std::cout << "pts ms:"
			<< pkt->pts * r2d(ic->streams[pkt->stream_index]->time_base) * 1000
			<< std::endl;
		AVCodecContext *cc = nullptr;
		//解码时间
		std::cout << "dts:" << pkt->dts << std::endl;
		if (pkt->stream_index == videoStream)
		{
			cc = vcc;
			std::cout << "图像" << std::endl;
		}
		else if (pkt->stream_index == audioStream)
		{
			cc = acc;
			std::cout << "音频" << std::endl;
		}
		if (nullptr != cc)
		{
			//解码视频
			//发送packet到解码线程，1次send，可能多次recv
			//获取缓冲剩余数据，取出所有缓冲帧,pkt传null
			ret = avcodec_send_packet(cc, pkt);
			if (0 != ret)
			{
				//引用计数减一，为0，释放数据空间
				av_packet_unref(pkt);
				continue;
			}

			for (;;)
			{
				//从线程中获取解码结果
				ret = avcodec_receive_frame(cc, frame);
				if (0 != ret)
				{
					break;
				}
				std::cout << "frame:"
					<< " format:" << frame->format
					<< " linesize:"<< frame->linesize[0]
					<< std::endl;
				//是视频，进行格式转换，可以用shader转换
				if (cc == vcc)
				{
					vctx = sws_getCachedContext(
						vctx, //传null会新创建
						frame->width,frame->height,//输入的宽高
						(AVPixelFormat)frame->format,//输入的格式
						frame->width, frame->height, //输出宽高
						AV_PIX_FMT_RGBA,//输出格式
						SWS_FAST_BILINEAR,//尺寸插值算法
						0,0,0);
					if (nullptr != vctx)
					{
						if (nullptr == rgb)
						{
							rgb = new unsigned char[frame->width * frame->height * 4];//考虑对齐
						}
						uint8_t *data[2] = { 0 };
						data[0] = rgb;
						int lines[2] = { 0 };
						lines[0] = frame->width * 4;//一行字节数
						int height = sws_scale(
							vctx,
							frame->data,//输入数据
							frame->linesize,//输入行大小，考虑对齐
							0,
							frame->height,//输入高度
							data,		//输出数据
							lines
							);
						std::cout << "sws_scale:" << height << std::endl;
					}
				}
				else if (cc == acc)
				{
					//音频重采样
					if (nullptr == pcm)
					{
						//nb_samples*样本大小*通道数
						pcm = new unsigned char[frame->nb_samples * 2 * 2];
						uint8_t *data[2] = { 0 };
						data[0] = pcm;
						int nb_samples = swr_convert(
							actx,
							data, //输出数据
							frame->nb_samples,
							(const uint8_t **)frame->data,
							frame->nb_samples
						);
						std::cout << "swr_convert:" << nb_samples << std::endl;
					}
				}
			}

		}
		
		//引用计数减一，为0，释放数据空间
		av_packet_unref(pkt);
	}

	sws_freeContext(vctx);
	vctx = nullptr;

	swr_free(&actx);

	av_frame_free(&frame);
	av_packet_free(&pkt);

	//释放封装上下文，并且将ic置空
	avformat_close_input(&ic);

	getchar();
    return 0;
}

