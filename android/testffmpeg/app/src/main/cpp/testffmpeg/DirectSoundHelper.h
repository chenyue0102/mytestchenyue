#ifndef _DIRECT_SOUND_HELPER_H_
#define _DIRECT_SOUND_HELPER_H_
#include <stdint.h>
#include <thread>
#include <dsound.h>
#include "InterfaceDefine.h"

class DirectSoundHelper : public IAudioPlay
{
public:
	DirectSoundHelper();
	~DirectSoundHelper();

public:
	bool init(uint32_t numChannels, uint32_t samplesPerSec, uint32_t bitsPerSample, uint32_t bufUpdateSize, IAudioPlayCallback *pCallback, void *pContext);
	bool destroy();
	//EPlayState
	bool setPlayState(int playState);
public:
	virtual void putData(const void *data, uint32_t size)override;
private:
	IDirectSound8 *mDirectSound8;
	LPDIRECTSOUNDBUFFER8 mDirectSoundBuffer8;
	HANDLE mNotifyEvent;
	HANDLE mExitEvent;
	std::thread mThread;
	DWORD mOffset;
	DWORD mBufferUpdateSize;
};


#endif