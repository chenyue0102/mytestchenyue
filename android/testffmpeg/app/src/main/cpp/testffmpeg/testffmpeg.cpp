// testffmpeg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include "PlayManager.h"
#include "DirectSoundHelper.h"
#include "EnumDefine.h"
#include "RingQueue.h"
#include "SDL.h"
#include "SDLAudioHelper.h"

#define BUFFER_UPDATE_SIZE (1024*4)
struct wav_header_t
{
	char chunkID[4]; //"RIFF" = 0x46464952
	uint32_t chunkSize; //文件长度-8
	char format[4]; //"WAVE" = 0x45564157
	char subchunk1ID[4]; //"fmt " = 0x20746D66
	uint32_t subchunk1Size; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
	uint16_t audioFormat;//数据类型,"01 00"表示 PCM
	uint16_t numChannels;//通道数
	uint32_t sampleRate;//采样率，比如""表示44100采样率
	uint32_t byteRate;//码率： 采样率x位深度x通道数/8 比如双通道的44.1K 16位采样的码率为176400
	uint16_t blockAlign;//采样一次，占内存大小 ： 位深度x通道数/8
	uint16_t bitsPerSample;//采样深度
};

//Chunks
struct chunk_t
{
	char ID[4]; //"data" = 0x61746164
	unsigned long size;  //Chunk data bytes
};

int main()
{
	FILE *file = fopen("d:/test.wav", "rb");
	wav_header_t wavHeader;
	fread(&wavHeader, 1, sizeof(wavHeader), file);
	chunk_t chunk;
	do
	{
		fread(&chunk, 1, sizeof(chunk), file);
		std::string s(chunk.ID, 4);
		printf("chunk:%s size%d\n", s.c_str(), chunk.size);
		if (0 != strncmp(chunk.ID, "data", 4)) {
			fseek(file, chunk.size, SEEK_CUR);
		}
	} while (0 != strncmp(chunk.ID, "data", 4));

	SDL_Init(SDL_INIT_AUDIO);
#if 0
	SDLAudioHelper sdlAudioHelper;
	DirectSoundHelper directSoundHelper;
	IAudioPlay *audioPlay = &directSoundHelper;

	audioPlay->setSampleInfo(2, 44100, EAudioFormatS16LE);
	audioPlay->open();
	audioPlay->setPlayState(EPlayStatePlaying);
	std::thread t = std::thread([audioPlay, file]() {
		uint8_t buf[1024];
		for (;;) {
			uint32_t queueSize = audioPlay->getQueuedAudioSize();
			if (queueSize < 1024 * 200) {
				size_t len = fread(buf, 1, 1024, file);
				if (len > 0) {
					audioPlay->putData(buf, len);
				}
				else {
					printf("finish\n");
					break;
				}
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		});

	t.join();
#endif

	PlayManager playManager;
	playManager.openFile("d:/test.mp3");
	int a = 0; 
	do
	{
		printf("0:exit 1:play 2:pause 3:positon\n");
		scanf("%d", &a);
		switch (a) {
		case 0:
			break;
		case 1:
			playManager.setPlayState(EPlayStatePlaying);
			break;
		case 2:
			playManager.setPlayState(EPlayStatePause);
			break;
		case 3:
			//printf("position:%lld\n", directSoundHelper.getPosition());
			break;
		}
	} while (a != 0);
	playManager.close();

	SDL_Quit();
    return 0;
}

