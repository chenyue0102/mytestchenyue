#ifndef _DIRECT_SOUND_HELPER_H_
#define _DIRECT_SOUND_HELPER_H_
#include <stdint.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <queue>
#include <dsound.h>
#include "InterfaceDefine.h"
#include "RingQueue.h"


class DirectSoundHelper : public IAudioPlay
{
	friend void threadProc(HANDLE hExitEvent, HANDLE hNotifyEvent, DirectSoundHelper *play);
public:
	DirectSoundHelper();
	~DirectSoundHelper();

public:
	virtual bool setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat)override;
	virtual bool open()override;
	virtual bool close()override;
	//EPlayState
	virtual bool setPlayState(uint32_t playState)override;
public:
	virtual uint32_t putData(const void *data, uint32_t size)override;
	virtual uint32_t getQueuedAudioSize()override;
private:
	std::thread mThread;
	HANDLE mNotifyEvent;
	HANDLE mExitEvent;
	std::mutex mMutex;
	IDirectSound8 *mDirectSound8;
	LPDIRECTSOUNDBUFFER8 mDirectSoundBuffer8;
	uint32_t mNumChannels;
	uint32_t mSamplesPerSec;
	uint32_t mBitsPerSample;
	DWORD mOffset;
	uint32_t mPlayState;
	RingQueue mBuffer;
};


#endif