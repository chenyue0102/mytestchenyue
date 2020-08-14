#define INITGUID
#include "DirectSoundHelper.h"
#include <assert.h>
#include <cguid.h>
#include "EnumDefine.h"

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define MAX_AUDIO_BUF 10
//#define BUFFERNOTIFYSIZE 19200
//#define BUFFER_LENGTH (MAX_AUDIO_BUF * BUFFERNOTIFYSIZE)

static void threadProc(HANDLE hExitEvent, HANDLE hNotifyEvent, LPDIRECTSOUNDBUFFER8 lpDirectSoundBuffer, IAudioPlay *play, DSBufferQueueCallback callback, void *pContext) {
	assert(nullptr != hExitEvent && nullptr != hNotifyEvent && nullptr != lpDirectSoundBuffer 
		&& nullptr != play && nullptr != callback);
	const DWORD dwCount = 2;
	HANDLE hEvents[] = { hExitEvent, hNotifyEvent };
	for (;;) {
		DWORD dwWaitResult = WaitForMultipleObjects(dwCount, hEvents, FALSE, INFINITE);
		if (WAIT_OBJECT_0 + 0 == dwWaitResult) {
			break;
		}
		else if (WAIT_OBJECT_0 + 1 == dwWaitResult) {
			ResetEvent(hEvents[1]);
			callback(play, pContext);
		}
		else {
			assert(false);
			break;
		}
	}
}

DirectSoundHelper::DirectSoundHelper()
	: mThread()
	, mNotifyEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mExitEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mMutex()
	, mDirectSound8(nullptr)
	, mDirectSoundBuffer8(nullptr)
	, mCallback(nullptr)
	, mContext(nullptr)
	, mNumChannels(0)
	, mSamplesPerSec(0)
	, mBitsPerSample(0)
	, mUpdateBufferBytes(0)
	, mOffset(0)
	, mPlayState(0)
{

}


DirectSoundHelper::~DirectSoundHelper(){
	destroy();
	CloseHandle(mExitEvent);
	mExitEvent = nullptr;
	CloseHandle(mNotifyEvent);
	mNotifyEvent = nullptr;
}

bool DirectSoundHelper::setBufferQueueCallback(DSBufferQueueCallback callback, void *pContext) {
	std::lock_guard<std::mutex> lk(mMutex);
	assert(!mThread.joinable());
	mCallback = callback;
	mContext = pContext;
	return true;
}

bool DirectSoundHelper::setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t bitsPerSample) {
	std::lock_guard<std::mutex> lk(mMutex);
	assert(!mThread.joinable());
	mNumChannels = numChannels;
	mSamplesPerSec = samplesPerSec;
	mBitsPerSample = bitsPerSample;
	return true;
}

bool DirectSoundHelper::setUpdateBufferLength(uint32_t updateBufferBytes) {
	std::lock_guard<std::mutex> lk(mMutex);
	assert(!mThread.joinable());
	mUpdateBufferBytes = updateBufferBytes;
	return true;
}

bool DirectSoundHelper::init()
{
	std::lock_guard<std::mutex> lk(mMutex);

	HRESULT hr = S_OK;
	bool ret = false;

	do
	{
		if (FAILED(hr = DirectSoundCreate8(nullptr, &mDirectSound8, nullptr))) {
			assert(false);
			break;
		}
		if (FAILED(hr = mDirectSound8->SetCooperativeLevel(GetDesktopWindow(), DSSCL_PRIORITY))) {
			assert(false);
			break;
		}
		
		{
			DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
			dsbd.dwSize = sizeof(DSBUFFERDESC);
			dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
			dsbd.dwBufferBytes = 0;
			dsbd.lpwfxFormat = NULL;
			dsbd.guid3DAlgorithm = GUID_NULL;

			LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;
			if (FAILED(hr = mDirectSound8->CreateSoundBuffer(&dsbd, &pDSBPrimary, NULL))) {
				assert(false);
				break;
			}
			WAVEFORMATEX wfx;
			ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
			wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
			wfx.nChannels = (WORD)mNumChannels;
			wfx.nSamplesPerSec = (DWORD)mSamplesPerSec;
			wfx.wBitsPerSample = (WORD)mBitsPerSample;
			wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
			wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);
			wfx.cbSize = 0;

			if (FAILED(hr = pDSBPrimary->SetFormat(&wfx))) {
				SAFE_RELEASE(pDSBPrimary);
				assert(false);
				break;
			}
			SAFE_RELEASE(pDSBPrimary);
		}

		WAVEFORMATEX wfx;
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
		wfx.nChannels = (WORD)mNumChannels;
		wfx.nSamplesPerSec = (DWORD)mSamplesPerSec;
		wfx.wBitsPerSample = (WORD)mBitsPerSample;
		wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
		wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);
		wfx.cbSize = 0;

		DSBUFFERDESC dsbd;
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
		dsbd.dwBufferBytes = MAX_AUDIO_BUF * mUpdateBufferBytes;
		dsbd.dwReserved = 0;
		dsbd.lpwfxFormat = &wfx;
		dsbd.guid3DAlgorithm = GUID_NULL;

		LPDIRECTSOUNDBUFFER lpbuffer = nullptr;
		if (FAILED(hr = mDirectSound8->CreateSoundBuffer(&dsbd, &lpbuffer, nullptr))) {
			assert(false);
			break;
		}
		
		if (FAILED(hr = lpbuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&mDirectSoundBuffer8))) {
			SAFE_RELEASE(lpbuffer);
			assert(false);
			break;
		}
		SAFE_RELEASE(lpbuffer);

		ResetEvent(mExitEvent);
		ResetEvent(mNotifyEvent);
		DSBPOSITIONNOTIFY notifys[MAX_AUDIO_BUF] = { 0 };
		for (int i = 0; i < MAX_AUDIO_BUF; i++) {
			notifys[i].dwOffset = i * mUpdateBufferBytes;
			notifys[i].hEventNotify = mNotifyEvent;
		}
		LPDIRECTSOUNDNOTIFY8 lpDirectSoundNotify8 = nullptr;
		if (FAILED(hr = mDirectSoundBuffer8->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&lpDirectSoundNotify8))) {
			assert(false);
			break;
		}
		if (FAILED(hr = lpDirectSoundNotify8->SetNotificationPositions(MAX_AUDIO_BUF, notifys))) {
			SAFE_RELEASE(lpDirectSoundNotify8);
			assert(false);
			break;
		}
		SAFE_RELEASE(lpDirectSoundNotify8);
		
		mDirectSoundBuffer8->SetVolume(DSBVOLUME_MAX);
		mTotalWriteBytes = 0;
		mPlayState = 0;
		mThread = std::thread(&threadProc, mExitEvent, mNotifyEvent, mDirectSoundBuffer8, static_cast<IAudioPlay*>(this), mCallback, mContext);
		ret = true;
	} while (false);

	if (!ret) {
		destroy();
	}
	return ret;
}

bool DirectSoundHelper::destroy() {
	SetEvent(mExitEvent);
	if (mThread.joinable()) {
		mThread.join();
	}

	std::lock_guard<std::mutex> lk(mMutex);
	SAFE_RELEASE(mDirectSoundBuffer8);
	SAFE_RELEASE(mDirectSound8);
	mPlayState = 0;
	mTotalWriteBytes = 0;
	mOffset = 0;

	return true;
}

bool DirectSoundHelper::setPlayState(uint32_t playState) {
	std::lock_guard<std::mutex> lk(mMutex);

	bool ret = false;
	if (nullptr != mDirectSoundBuffer8 && nullptr != mDirectSoundBuffer8) {
		switch (playState) {
		case EPlayStatePlaying: {
			if (SUCCEEDED(mDirectSoundBuffer8->Play(0, 0, DSBPLAY_LOOPING))) {
				mPlayState = playState;
				ret = true;
			}
			break;
		}
		case EPlayStatePause: {
			if (SUCCEEDED(mDirectSoundBuffer8->Stop())) {
				mPlayState = playState;
				ret = true;
			}
			break;
		}
		case EPlayStateStopped: {
			if (SUCCEEDED(mDirectSoundBuffer8->Stop())) {
				mPlayState = playState;
				mDirectSoundBuffer8->SetCurrentPosition(0);
				ret = true;
			}
			break;
		}
		default: {
			assert(false);
			break;
		}
		}	
	}
	return ret;
}

int64_t DirectSoundHelper::getPosition() {
	std::lock_guard<std::mutex> lk(mMutex);

	int64_t ret = -1;
	if (nullptr != mDirectSoundBuffer8) {
		HRESULT hr = S_OK;
		DWORD dwPlayPos = 0, dwWritePos = 0;
		if (SUCCEEDED(hr = mDirectSoundBuffer8->GetCurrentPosition(&dwPlayPos, &dwWritePos))) {
			if (dwWritePos >= dwPlayPos) {
				ret = mTotalWriteBytes - (dwWritePos - dwPlayPos);
			}
			else {
				const DWORD BUFFER_LENGTH = mUpdateBufferBytes * MAX_AUDIO_BUF;
				ret = mTotalWriteBytes - dwWritePos - (BUFFER_LENGTH - dwPlayPos);
			}
			uint32_t bytesPerSec = mSamplesPerSec * mNumChannels * mBitsPerSample / 8;
			ret = ret * 1000 / bytesPerSec;
		}
	}
	return ret;
}

static DWORD writeBuffer(LPDIRECTSOUNDBUFFER8 lpDirectSoundBuffer, DWORD dwOffset, const void *data, uint32_t size) {
	DWORD dwWriteBytes = 0;
	HRESULT hr = S_OK;
	VOID* pDSLockedBuffer = NULL;
	VOID* pDSLockedBuffer2 = NULL;
	DWORD dwDSLockedBufferSize = 0;
	DWORD dwDSLockedBufferSize2 = 0;
	if (SUCCEEDED(hr = lpDirectSoundBuffer->Lock(dwOffset, size, &pDSLockedBuffer, &dwDSLockedBufferSize, &pDSLockedBuffer2, &dwDSLockedBufferSize2, 0))) {
		memcpy(pDSLockedBuffer, data, dwDSLockedBufferSize);
		dwWriteBytes += dwDSLockedBufferSize;
		if (nullptr != pDSLockedBuffer2) {
			memcpy(pDSLockedBuffer2, reinterpret_cast<const uint8_t*>(data) + dwDSLockedBufferSize, dwDSLockedBufferSize2);
			dwWriteBytes += dwDSLockedBufferSize2;
		}
		lpDirectSoundBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, pDSLockedBuffer2, dwDSLockedBufferSize2);
	}
	else {
		assert(false);
	}
	return dwWriteBytes;
}

void DirectSoundHelper::putData(const void * data, uint32_t size){
	std::lock_guard<std::mutex> lk(mMutex);

	if (nullptr != mDirectSoundBuffer8) {
		const DWORD BUFFER_LENGTH = mUpdateBufferBytes * MAX_AUDIO_BUF;
		DWORD dwMinLength = min(BUFFER_LENGTH, mOffset + size);
		DWORD tmpSize = dwMinLength - mOffset;
		DWORD dwWriteBytes = writeBuffer(mDirectSoundBuffer8, mOffset, data, tmpSize);
		mTotalWriteBytes += dwWriteBytes;
		mOffset += dwWriteBytes;
		mOffset %= BUFFER_LENGTH;
		if (tmpSize < size) {
			dwWriteBytes = writeBuffer(mDirectSoundBuffer8, mOffset, reinterpret_cast<const uint8_t*>(data) + tmpSize, size - tmpSize);
			mTotalWriteBytes += dwWriteBytes;
			mOffset += dwWriteBytes;
			mOffset %= BUFFER_LENGTH;
		}
	}
}
