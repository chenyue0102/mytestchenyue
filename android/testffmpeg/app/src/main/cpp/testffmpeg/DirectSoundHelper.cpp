#define INITGUID
#include "DirectSoundHelper.h"
#include <assert.h>
#include <cguid.h>
#include "EnumDefine.h"

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define MAX_AUDIO_BUF 10
#define BUFFERNOTIFYSIZE 1920
#define BUFFER_LENGTH (MAX_AUDIO_BUF * BUFFERNOTIFYSIZE)


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

static uint32_t writeToDirectSound(LPDIRECTSOUNDBUFFER8 directSoundBuffer8, DWORD &offset, const void *data, uint32_t size) {
	uint32_t writeTotalSize = 0;
	if (nullptr != directSoundBuffer8) {
		DWORD dwMinLength = min(BUFFER_LENGTH, offset + size);
		DWORD tmpSize = dwMinLength - offset;
		DWORD dwWriteBytes = writeBuffer(directSoundBuffer8, offset, data, tmpSize);
		offset += dwWriteBytes;
		writeTotalSize += dwWriteBytes;
		offset %= BUFFER_LENGTH;
		if (tmpSize < size) {
			dwWriteBytes = writeBuffer(directSoundBuffer8, offset, reinterpret_cast<const uint8_t*>(data) + tmpSize, size - tmpSize);
			offset += dwWriteBytes;
			writeTotalSize += dwWriteBytes;
			offset %= BUFFER_LENGTH;
		}
	}
	return writeTotalSize;
}

void threadProc(HANDLE hExitEvent, HANDLE hNotifyEvent, DirectSoundHelper *play) {
	assert(nullptr != hExitEvent && nullptr != hNotifyEvent && nullptr != play);
	const DWORD dwCount = 2;
	uint8_t *buf = new uint8_t[BUFFERNOTIFYSIZE];
	HANDLE hEvents[] = { hExitEvent, hNotifyEvent };
	for (;;) {
		DWORD dwWaitResult = WaitForMultipleObjects(dwCount, hEvents, FALSE, INFINITE);
		if (WAIT_OBJECT_0 + 0 == dwWaitResult) {
			break;
		}
		else if (WAIT_OBJECT_0 + 1 == dwWaitResult) {
			ResetEvent(hEvents[1]);

			std::lock_guard<std::mutex> lk(play->mMutex);
			uint32_t len = play->mBuffer.get(buf, BUFFERNOTIFYSIZE);
			assert(len == BUFFERNOTIFYSIZE);
			writeToDirectSound(play->mDirectSoundBuffer8, play->mOffset, buf, len);
		}
		else {
			assert(false);
			break;
		}
	}
	delete[]buf;
}

DirectSoundHelper::DirectSoundHelper()
	: mThread()
	, mNotifyEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mExitEvent(CreateEvent(nullptr, TRUE, FALSE, nullptr))
	, mMutex()
	, mDirectSound8(nullptr)
	, mDirectSoundBuffer8(nullptr)
	, mNumChannels(0)
	, mSamplesPerSec(0)
	, mBitsPerSample(0)
	, mOffset(0)
	, mPlayState(0)
	, mBuffer(1024 * 1024 * 2)
{

}


DirectSoundHelper::~DirectSoundHelper(){
	close();
	CloseHandle(mExitEvent);
	mExitEvent = nullptr;
	CloseHandle(mNotifyEvent);
	mNotifyEvent = nullptr;
}

bool DirectSoundHelper::setSampleInfo(uint32_t numChannels, uint32_t samplesPerSec, uint32_t audioFormat) {
	std::lock_guard<std::mutex> lk(mMutex);
	assert(!mThread.joinable());
	mNumChannels = numChannels;
	mSamplesPerSec = samplesPerSec;
	switch (audioFormat) {
	case EAudioFormatS16LE:
		mBitsPerSample = 16;
		break;
	default:
		assert(false);
		break;
	}
	return true;
}

bool DirectSoundHelper::open()
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
		dsbd.dwBufferBytes = BUFFER_LENGTH;
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
			notifys[i].dwOffset = i * BUFFERNOTIFYSIZE;
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
		mPlayState = 0;
		mThread = std::thread(&threadProc, mExitEvent, mNotifyEvent, this);
		ret = true;
	} while (false);

	if (!ret) {
		close();
	}
	return ret;
}

bool DirectSoundHelper::close() {
	SetEvent(mExitEvent);
	if (mThread.joinable()) {
		mThread.join();
	}

	std::lock_guard<std::mutex> lk(mMutex);
	SAFE_RELEASE(mDirectSoundBuffer8);
	SAFE_RELEASE(mDirectSound8);
	mPlayState = 0;
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

uint32_t DirectSoundHelper::putData(const void * data, uint32_t size){
	std::lock_guard<std::mutex> lk(mMutex);

	return mBuffer.put(data, size);
}

uint32_t DirectSoundHelper::getQueuedAudioSize()
{
	uint32_t bufByte = 0;

	do
	{
		std::lock_guard<std::mutex> lk(mMutex);
		if (nullptr == mDirectSoundBuffer8) {
			assert(false);
			break;
		}
		HRESULT hr = S_OK;
		DWORD dwPlayPos = 0, dwWritePos = 0;
		if (FAILED(hr = mDirectSoundBuffer8->GetCurrentPosition(&dwPlayPos, &dwWritePos))) {
			assert(false);
			break;
		}
		if (dwWritePos >= dwPlayPos) {
			bufByte = (dwWritePos - dwPlayPos) + mBuffer.getDataSize();
		}
		else {
			bufByte = dwWritePos + (BUFFER_LENGTH - dwPlayPos) + mBuffer.getDataSize();
		}
	} while (false);
	

	return bufByte;
}
