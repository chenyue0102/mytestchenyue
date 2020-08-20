#ifndef _SDL_AUDIO_HELPER_H_
#define _SDL_AUDIO_HELPER_H_
#include <stdint.h>
#include "SDL.h"
#include "InterfaceDefine.h"

class SDLAudioHelper : public IAudioPlay
{
public:
	SDLAudioHelper();
	~SDLAudioHelper();
public:
	bool setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat);
	bool open();
	virtual bool setPlayState(uint32_t playState)override;
	uint32_t putData(const void *data, uint32_t size);
	virtual uint32_t getQueuedAudioSize()override;
	bool close();
private:
	uint32_t mNumChannels;
	uint32_t mSamplesPerSec;
	uint32_t mAudioFormat;
	SDL_AudioDeviceID mDeviceId;
};

#endif