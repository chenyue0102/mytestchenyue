#include "DirectSoundHelper.h"
#include <assert.h>

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

DirectSoundHelper::DirectSoundHelper()
	: mIDirectSound8(nullptr)
{

}


DirectSoundHelper::~DirectSoundHelper()
{
}

bool DirectSoundHelper::init(uint32_t numChannels, int sampleRate)
{
	HRESULT hr = S_OK;
	bool ret = false;

	do
	{
		destroy();
		if (FAILED(hr = DirectSoundCreate8(nullptr, &mIDirectSound8, nullptr))) {
			assert(false);
			break;
		}
		if (FAILED(hr = mIDirectSound8->SetCooperativeLevel(GetDesktopWindow(), DSSCL_PRIORITY))) {
			assert(false);
			break;
		}

		DSBUFFERDESC dsbd;
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
		dsbd.dwBufferBytes = 0;
		dsbd.lpwfxFormat = NULL;

		LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;
		if (FAILED(hr = mIDirectSound8->CreateSoundBuffer(&dsbd, &pDSBPrimary, nullptr))) {
			assert(false);
			break;
		}

		WAVEFORMATEX wfx;
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
		wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
		wfx.nChannels = (WORD)channelCount;
		wfx.nSamplesPerSec = (DWORD)sampleRate;
		wfx.wBitsPerSample = (WORD)dwPrimaryBitRate;
		wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels);
		wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign);

		ret = true;
	} while (false);
	return ret;
}

bool DirectSoundHelper::destroy()
{
	SAFE_RELEASE(mIDirectSound8);
}
