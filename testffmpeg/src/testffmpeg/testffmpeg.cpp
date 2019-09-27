// testffmpeg.cpp : 定义控制台应用程序的入口点。
//
#include <assert.h>
#include "stdafx.h"
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil\error.h>
}

int main()
{
	char szError[128] = { 0 };
	AVFormatContext *pFormatCtx = 0;
	av_register_all();
	int ret = avformat_network_init();
	assert(0 == ret);
	ret = avformat_open_input(&pFormatCtx, "./v1080.mp4", nullptr, nullptr);
	if (0 != ret)
	{
		printf("%s", av_make_error_string(szError, _countof(szError), ret));
	}
    return 0;
}

