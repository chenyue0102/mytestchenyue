#define INITGUID
#include "DirectSoundHelper.h"
#include <assert.h>
#include <cguid.h>
#include "EnumDefine.h"

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define MAX_AUDIO_BUF 10

static void threadProc(HANDLE hExitEvent, HANDLE hNotifyEvent, LPDIRECTSOUNDBUFFER8 lpDirectSoundBuffer, IAudioPlay *play, IAudioPlayCallback *pCallback, void *pContext) {
	assert(nullptr != hExitEvent && nullptr != hNotifyEvent && nullptr != lpDirectSoundBuffer 
		&& nullptr != play && nullptr != pCallback);
	const DWORD dwCount = 2;
	HANDLE hEvents[] = { hExitEvent, hNotifyEvent };
	for (;;) {
		DWORD dwWaitResult = WaitForMultipleObjects(dwCount, hEvents, FALSE, INFINITE);
		if (WAIT_OBJECT_0 + 0 == dwWaitResult) {
			break;
		}
		else if (WAIT_OBJECT_0 + 1 == dwWaitResult) {
			ResetEvent(hEvents[1]);
			pCallback->onBufferCallback(play, pContext);
		}
		else {
			assert(false);
			break;
		}
	}
}

DirectSoundHelper::DirectSoundHelper()
	: mDirectSound8(nullptr)
	, mDirectSoundBuffer8(nullptr)
	, mNotifyEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mExitEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mThread()
	, mOffset(0)
	, mBufferUpdateSize(0)
{

}


DirectSoundHelper::~DirectSoundHelper(){
	destroy();
	CloseHandle(mExitEvent);
	mExitEvent = nullptr;
	CloseHandle(mNotifyEvent);
	mNotifyEvent = nullptr;
}

bool DirectSoundHelper::init(uint32_t numChannels, uint32_t samplesPerSec, uint32_t bitsPerSample, uint32_t bufUpdateSize, IAudioPlayCallback *pCallback, void *pContext)
{
	HRESULT hr = S_OK;
	bool ret = false;

	do
	{
		destroy();
		mBufferUpdateSize = bufUpdateSize;
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
			wfx.nChannels = (WORD)numChannels;
			wfx.nSamplesPerSec = (DWORD)samplesPerSec;
			wfx.wBitsPerSample = (WORD)bitsPerSample;
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
		wfx.nChannels = (WORD)numChannels;
		wfx.nSamplesPerSec = (DWORD)samplesPerSec;
		wfx.wBitsPerSample = (WORD)bitsPerSample;
		wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
		wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);
		wfx.cbSize = 0;

		DSBUFFERDESC dsbd;
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
		dsbd.dwBufferBytes = bufUpdateSize * MAX_AUDIO_BUF;
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
			notifys[i].dwOffset = i * bufUpdateSize;
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
		mThread = std::thread(&threadProc, mExitEvent, mNotifyEvent, mDirectSoundBuffer8, static_cast<IAudioPlay*>(this), pCallback, pContext);
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
	SAFE_RELEASE(mDirectSoundBuffer8);
	SAFE_RELEASE(mDirectSound8);

	return true;
}

bool DirectSoundHelper::setPlayState(int playState) {
	bool ret = false;
	if (nullptr != mDirectSoundBuffer8) {
		switch (playState) {
		case EPlayStatePlaying: {
			mDirectSoundBuffer8->SetCurrentPosition(0);
			if (SUCCEEDED(mDirectSoundBuffer8->Play(0, 0, DSBPLAY_LOOPING))) {
				ret = true;
			}
			break;
		}
		case EPlayStatePause: {
			if (SUCCEEDED(mDirectSoundBuffer8->Stop())) {
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
	if (nullptr != mDirectSoundBuffer8) {
		const DWORD BUFFER_LENGTH = mBufferUpdateSize * MAX_AUDIO_BUF;
		DWORD dwMinLength = min(BUFFER_LENGTH, mOffset + size);
		DWORD tmpSize = dwMinLength - mOffset;
		mOffset += writeBuffer(mDirectSoundBuffer8, mOffset, data, tmpSize);
		mOffset %= BUFFER_LENGTH;
		if (tmpSize < size) {
			mOffset += writeBuffer(mDirectSoundBuffer8, mOffset, reinterpret_cast<const uint8_t*>(data) + tmpSize, size - tmpSize);
			mOffset %= BUFFER_LENGTH;
		}
	}
}
