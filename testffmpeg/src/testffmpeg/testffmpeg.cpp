// testffmpeg.cpp : 定义控制台应用程序的入口点。
//
#include <assert.h>
#include <thread>
#include <Windows.h>
#include "stdafx.h"
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil\error.h>
}

void getCurrentDir(char *str, int len)
{
	GetModuleFileNameA(0, str, len);
	char *f = strrchr(str, '\\');
	if (nullptr != f)
	{
		*f = '\0';
	}
}

int main()
{
	char szError[128] = { 0 };
	getCurrentDir(szError, _countof(szError));
	strcat(szError, "/v1080.mp4");
	AVFormatContext *ic = 0;//解封装上下文
	av_register_all();
	int ret = avformat_network_init();
	assert(0 == ret);
	ret = avformat_open_input(&ic, szError, nullptr, nullptr);
	if (0 != ret)
	{
		printf("%s", av_make_error_string(szError, _countof(szError), ret));
		return 0;
	}
	ret = avformat_find_stream_info(ic, nullptr);
	//assert(0 == ret);
	//查找流id
	int videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	int audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
	//查找解码器
	AVCodec *vcode = avcodec_find_decoder(ic->streams[videoStream]->codecpar->codec_id);
	AVCodec *acode = avcodec_find_decoder(ic->streams[audioStream]->codecpar->codec_id);
	
	//创建解码器上下文
	AVCodecContext *vcc = avcodec_alloc_context3(vcode);
	//配置解码器参数
	avcodec_parameters_to_context(vcc, ic->streams[videoStream]->codecpar);
	//设置解码线程
	vcc->thread_count = std::thread::hardware_concurrency();
	//打开解码器
	ret = avcodec_open2(vcc, 0, 0);

	AVCodecContext *acc = avcodec_alloc_context3(acode);
	avcodec_parameters_to_context(acc, ic->streams[audioStream]->codecpar);
	acc->thread_count = std::thread::hardware_concurrency();
	ret = avcodec_open2(acc, 0, 0);


	avcodec_close(acc);
	avcodec_free_context(&acc);

	avcodec_close(vcc);
	avcodec_free_context(&vcc);
    return 0;
}

