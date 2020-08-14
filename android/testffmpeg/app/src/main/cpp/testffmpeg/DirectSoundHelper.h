#ifndef _DIRECT_SOUND_HELPER_H_
#define _DIRECT_SOUND_HELPER_H_
#include <stdint.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <dsound.h>
#include "InterfaceDefine.h"

class DirectSoundHelper : public IAudioPlay
{
public:
	DirectSoundHelper();
	~DirectSoundHelper();

public:
	virtual bool setCallback(IAudioPlayCallback *pCallback, void *pContext)override;
	virtual bool setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t bitsPerSample)override;
	//更新的时候，一次更新缓冲区的数据大小
	virtual bool setUpdateBufferLength(uint32_t updateBufferBytes)override;
	virtual bool init()override;
	virtual bool destroy()override;
	
	//EPlayState
	virtual bool setPlayState(uint32_t playState)override;
	//单位毫秒
	virtual int64_t getPosition();
public:
	virtual void putData(const void *data, uint32_t size)override;
private:
	std::thread mThread;
	HANDLE mNotifyEvent;
	HANDLE mExitEvent;
	std::mutex mMutex;
	IDirectSound8 *mDirectSound8;
	LPDIRECTSOUNDBUFFER8 mDirectSoundBuffer8;
	IAudioPlayCallback *mCallback;
	void *mContext;
	uint32_t mNumChannels;
	uint32_t mSamplesPerSec;
	uint32_t mBitsPerSample;
	uint32_t mUpdateBufferBytes;
	DWORD mOffset;
	uint32_t mTotalWriteBytes;
	uint32_t mPlayState;
};


#endif