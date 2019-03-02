// TestDemux.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")

static double r2d(AVRational r)
{
	return r.den == 0 ? 0.0 : (double)r.num / r.den;
}

int main()
{
	std::cout << "TestDemux" << std::endl;
	//��ʼ����װ
	av_register_all();

	//��ʼ������⣬���Դ�rtsp(���������)��rtmp(ֱ��)��http(����ֱ��)Э�����ý����Ƶ
	avformat_network_init();

	//ע�������
	avcodec_register_all();

	//�������ã���rtsp��ʱʱ��
	AVDictionary *opts = nullptr;
	//����rtsp����tcpЭ���
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);
	//������ʱʱ��
	av_dict_set(&opts, "max_delay", "500", 0);

	AVFormatContext *ic = nullptr;//���װ������
#if 1
	const char *path = "C:/Users/chenyue/Desktop/Wildlife.wmv";
#else
	const char *path = "C:/Users/chenyue/Desktop/MOV_1073.mp4";
#endif
	int ret = avformat_open_input(
		&ic, 
		path, 
		nullptr, //�Զ�ѡ������
		&opts	//��������
	);

	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}

	//��ȡ����Ϣ
	ret = avformat_find_stream_info(ic, 0);

	//��ʱ��
	int total = ic->duration / AV_TIME_BASE; //��λ��
	std::cout << "total:" << total << std::endl;

	//��ӡ��Ƶ����ϸ��Ϣ
	av_dump_format(
		ic, 
		0, 
		nullptr, 
		0  //0�����ļ���1������
	);

	//����Ƶ����
	int videoStream = 0;
	int audioStream = 0;

	//��ȡ����Ƶ����Ϣ���������ߺ�����ȡ
	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVStream *as = ic->streams[i];
		//��Ƶ
		if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			std::cout << "��Ƶ" << std::endl;
			//����,AVCodecID
			std::cout << "codec_id:" << as->codecpar->codec_id << std::endl;
			//֡��
			std::cout << "fps:" << r2d(as->avg_frame_rate) << std::endl;
			//�п���û��
			std::cout << "width:" << as->codecpar->width << std::endl;
			std::cout << "height:" << as->codecpar->height << std::endl;
			
		}
		//��Ƶ
		else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			std::cout << "��Ƶ" << std::endl;
			//����,AVCodecID
			std::cout << "codec_id:" << as->codecpar->codec_id << std::endl;
			//֡��,һ֡���ݴ洢����һ������������
			std::cout << "fps:" << r2d(as->avg_frame_rate) << std::endl;
			//һ֡���ݵĵ�ͨ��������������frame_size * channel * һ���������� = һ֡��С
			std::cout << "frame_size:" << as->codecpar->frame_size << std::endl;
			std::cout << "sample_rate:" << as->codecpar->sample_rate << std::endl;
			//AVSampleFormat
			std::cout << "format:" << as->codecpar->format << std::endl;
			//ͨ����
			std::cout << "channel:" << as->codecpar->channels << std::endl;
		}
	}

	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);

	//�ҵ���Ƶ������
	AVCodec *vcodec = avcodec_find_decoder(ic->streams[videoStream]->codecpar->codec_id);
	if (nullptr == vcodec)
	{
		std::cout << "not find " << ic->streams[videoStream]->codecpar->codec_id << std::endl;
		getchar();
		return -1;
	}
	std::cout << "find " << ic->streams[videoStream]->codecpar->codec_id << std::endl;
	//����������������
	AVCodecContext *vcc = avcodec_alloc_context3(vcodec);
	//���ý���������
	avcodec_parameters_to_context(vcc, ic->streams[videoStream]->codecpar);
	//����8�߳̽���
	vcc->thread_count = 8;
	//�򿪽�����������
	ret = avcodec_open2(vcc, 0, 0);
	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}
	std::cout << "avcodec_open2 success" << std::endl;


	//�ҵ���Ƶ������
	AVCodec *acodec = avcodec_find_decoder(ic->streams[audioStream]->codecpar->codec_id);
	if (nullptr == acodec)
	{
		std::cout << "not find " << ic->streams[audioStream]->codecpar->codec_id << std::endl;
		getchar();
		return -1;
	}
	std::cout << "find " << ic->streams[audioStream]->codecpar->codec_id << std::endl;
	//����������������
	AVCodecContext *acc = avcodec_alloc_context3(acodec);
	//���ý���������
	avcodec_parameters_to_context(acc, ic->streams[audioStream]->codecpar);
	//����8�߳̽���
	acc->thread_count = 8;
	//�򿪽�����������
	ret = avcodec_open2(acc, 0, 0);
	if (0 != ret)
	{
		char buf[1024] = { 0 };
		av_strerror(ret, buf, sizeof(buf) - 1);
		std::cout << buf << std::endl;
		return -1;
	}
	std::cout << "avcodec_open2 success" << std::endl;

	//��ȡ֡
	//malloc AVPacket init AVPacket
	AVPacket *pkt = av_packet_alloc();
	AVFrame *frame = av_frame_alloc();//frameռ�ÿռ��
	for (;;)
	{

		ret = av_read_frame(ic, pkt);
		if (0 != ret)
		{
			//ѭ������
			int ms = 3000;
			long long pos = (double)ms / 1000 * r2d(ic->streams[pkt->stream_index]->time_base);
			av_seek_frame(ic, videoStream, pos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
			break;
		}
		std::cout << "size:" << pkt->size << std::endl;
		//��ʾʱ��
		std::cout << "pts:" << pkt->pts << std::endl;
		//����
		std::cout << "pts ms:"
			<< pkt->pts * r2d(ic->streams[pkt->stream_index]->time_base) * 1000
			<< std::endl;
		AVCodecContext *cc = nullptr;
		//����ʱ��
		std::cout << "dts:" << pkt->dts << std::endl;
		if (pkt->stream_index == videoStream)
		{
			cc = vcc;
			std::cout << "ͼ��" << std::endl;
		}
		else if (pkt->stream_index == audioStream)
		{
			cc = acc;
			std::cout << "��Ƶ" << std::endl;
		}
		if (nullptr != cc)
		{
			//������Ƶ
			//����packet�������̣߳�1��send�����ܶ��recv
			//��ȡ����ʣ�����ݣ�ȡ�����л���֡,pkt��null
			ret = avcodec_send_packet(cc, pkt);
			if (0 != ret)
			{
				//���ü�����һ��Ϊ0���ͷ����ݿռ�
				av_packet_unref(pkt);
				continue;
			}

			for (;;)
			{
				//���߳��л�ȡ������
				ret = avcodec_receive_frame(cc, frame);
				if (0 != ret)
				{
					break;
				}
				std::cout << "frame:"
					<< " format:" << frame->format
					<< " linesize:"<< frame->linesize[0]
					<< std::endl;
			}

		}
		
		//���ü�����һ��Ϊ0���ͷ����ݿռ�
		av_packet_unref(pkt);
	}

	av_frame_free(&frame);
	av_packet_free(&pkt);

	//�ͷŷ�װ�����ģ����ҽ�ic�ÿ�
	avformat_close_input(&ic);

	getchar();
    return 0;
}

