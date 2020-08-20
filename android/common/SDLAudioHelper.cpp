#include "SDLAudioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include "SDL_audio.h"
#include "EnumDefine.h"

#define SPEC_SAMPLES_COUNT (1024)

SDLAudioHelper::SDLAudioHelper()
	: mNumChannels()
	, mSamplesPerSec()
	, mAudioFormat()
	, mDeviceId()
{
}


SDLAudioHelper::~SDLAudioHelper()
{
}

bool SDLAudioHelper::setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat)
{
	mNumChannels = numChannels;
	mSamplesPerSec = samplesPerSec;
	mAudioFormat = audioFormat;
	return true;
}

bool SDLAudioHelper::open()
{
	bool ret = false;
	int err = 0;
	do
	{
		int format = 0;
		if (EAudioFormatS16LE == mAudioFormat) {
			format = AUDIO_S16LSB;
		}
		else {
			assert(false);
			break;
		}
		SDL_AudioSpec audioSpec = { 0 };
		audioSpec.freq = mSamplesPerSec;
		audioSpec.format = format;
		audioSpec.channels = mNumChannels;
		audioSpec.samples = SPEC_SAMPLES_COUNT;
		audioSpec.size = 0;
		audioSpec.callback = 0;
		audioSpec.userdata = 0;
		if (0 != SDL_OpenAudio(&audioSpec, nullptr)) {
			assert(false);
			break;
		}
		mDeviceId = 1;
		ret = true;
	} while (false);
	return ret;
}

bool SDLAudioHelper::setPlayState(uint32_t playState)
{
	switch (playState) {
	case EPlayStatePlaying:
		SDL_PauseAudioDevice(mDeviceId, 0);
		break;
	case EPlayStatePause:
		SDL_PauseAudioDevice(mDeviceId, 1);
		break;
	case EPlayStateStopped:
		SDL_PauseAudioDevice(mDeviceId, 1);
		break;
	default:
		assert(false);
	}
	return true;
}

uint32_t SDLAudioHelper::putData(const void *data, uint32_t size) {
	if (0 == SDL_QueueAudio(mDeviceId, data, size)) {
		return size;
	}
	else {
		assert(false);
		return 0;
	}
}

uint32_t SDLAudioHelper::getQueuedAudioSize()
{
	return SDL_GetQueuedAudioSize(mDeviceId);
}

bool SDLAudioHelper::close()
{
	if (0 != mDeviceId) {
		SDL_PauseAudioDevice(mDeviceId, 1);
		SDL_CloseAudioDevice(mDeviceId);
		mDeviceId = 0;
	}
	
	return true;
}