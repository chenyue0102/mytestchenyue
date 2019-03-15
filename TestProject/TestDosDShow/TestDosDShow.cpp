// TestDosDShow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <objbase.h>
#include <atlbase.h>
#include <qedit.h>
#include <strmif.h>
#include <atomic>
#include "DShowHelper.h"
static const GUID CLSID_WavDest =
{ 0x3c78b8e2, 0x6c4d, 0x11d1,{ 0xad, 0xe2, 0x0, 0x0, 0xf8, 0x75, 0x4b, 0x99 } };
void WINAPI FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0) {
		CoTaskMemFree((PVOID)mt.pbFormat);

		// Strictly unnecessary but tidier
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL) {
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}

void WINAPI DeleteMediaType(AM_MEDIA_TYPE *pmt)
{
	// allow NULL pointers for coding simplicity

	if (pmt == NULL) {
		return;
	}

	FreeMediaType(*pmt);
	CoTaskMemFree((PVOID)pmt);
}

bool SaveBitmap(const char *pFileName, int width, int height, int biBitCount, const void *pBuf, int nBufLen)
{
	if (nullptr == pFileName
		|| 0 == width
		|| 0 == height
		|| !(biBitCount == 24 || biBitCount == 32 || biBitCount == 16)
		|| nullptr == pBuf
		|| nBufLen < ((width * height * biBitCount) / 8)
		)
	{
		return false;
	}
	else
	{
		BITMAPFILEHEADER bfh = { 0 };
		bfh.bfType = 'MB';
		bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nBufLen;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		FILE *fp = fopen(pFileName, "wb");
		fwrite(&bfh, 1, sizeof(bfh), fp);

		BITMAPINFOHEADER bih = { 0 };
		bih.biSize = sizeof(bih);
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biPlanes = 1;
		bih.biBitCount = biBitCount;
		fwrite(&bih, 1, sizeof(bih), fp);

		fwrite(pBuf, 1, nBufLen, fp);

		fclose(fp);
		return true;
	}
}

class CSampleGrabberCB : public ISampleGrabberCB
{
public:
	CSampleGrabberCB()
		: m_nRef(0)
	{

	}
	virtual ~CSampleGrabberCB()
	{

	}
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)override
	{
		return E_NOTIMPL;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef(void)override
	{
		return ++m_nRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release(void)override
	{
		ULONG nRef = --m_nRef;
		if (0 == nRef)
		{
			delete this;
		}
		return nRef;
	}
public:
	virtual HRESULT STDMETHODCALLTYPE SampleCB(
		double SampleTime,
		IMediaSample *pSample)override
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE BufferCB(
		double SampleTime,
		BYTE *pBuffer,
		long BufferLen)override
	{
		//SaveBitmap("d:/1.bmp", 1920, 1080, 16, pBuffer, BufferLen);
		if (bvideo)
		{
			
			return S_OK;
		}
		return S_OK;
	}
private:
	std::atomic_ulong m_nRef;
public:
	bool bvideo = false;
};
const char* GetFormatTypeName(REFGUID formattype)
{
	if (FORMAT_None == formattype)
	{
		return "FORMAT_None";
	}
	else if (FORMAT_VideoInfo == formattype)
	{
		return "FORMAT_VideoInfo";
	}
	else if (FORMAT_VideoInfo2 == formattype)
	{
		return "FORMAT_VideoInfo2";
	}
	else if (FORMAT_WaveFormatEx == formattype)
	{
		return "FORMAT_WaveFormatEx";
	}
	else if (FORMAT_MPEGVideo == formattype)
	{
		return "FORMAT_MPEGVideo";
	}
	else if (FORMAT_MPEGStreams == formattype)
	{
		return "FORMAT_MPEGStreams";
	}
	else if (FORMAT_DvInfo == formattype)
	{
		return "FORMAT_DvInfo";
	}
	else
	{
		assert(false);
		return "";
	}
}
const char* GetSubTypeName(REFGUID subtype)
{
	if (subtype == MEDIASUBTYPE_PCM)
	{
		return "MEDIASUBTYPE_PCM";
	}
	else
	{
		assert(false);
		return "";
	}
}
HRESULT hr = S_OK;
void testAudio()
{
	CComPtr<ICaptureGraphBuilder2> pCaptureGraphBuilder2;
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCaptureGraphBuilder2);
	CComPtr<IGraphBuilder> pGraphBuilder;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pGraphBuilder);
	hr = pCaptureGraphBuilder2->SetFiltergraph(pGraphBuilder);

	//获取音频输入
	std::vector<std::wstring> friendlyNames;
	DShowHelper::GetFriendlyNames(CLSID_AudioInputDeviceCategory, friendlyNames);
	CComPtr<IBaseFilter> pDeviceFilter;
	hr = DShowHelper::BindFilter(CLSID_AudioInputDeviceCategory, friendlyNames[0].c_str(), &pDeviceFilter);
	hr = pGraphBuilder->AddFilter(pDeviceFilter, L"Audio Capture");

	CComPtr<IPin> pPin;
	hr = DShowHelper::GetPin(pDeviceFilter, PINDIR_OUTPUT, 0, &pPin);

	CComPtr<IEnumMediaTypes> pEnumMediaTypes;
	hr = pPin->EnumMediaTypes(&pEnumMediaTypes);
	AM_MEDIA_TYPE *pMediaType = nullptr;

	while (pEnumMediaTypes->Next(1, &pMediaType, nullptr) == S_OK)
	{
		auto name = GetFormatTypeName(pMediaType->formattype);
		auto subtypename = GetSubTypeName(pMediaType->subtype);
		LPWAVEFORMATEX pWaveFormatMaxtex = (LPWAVEFORMATEX)pMediaType->pbFormat;
		DeleteMediaType(pMediaType);
		pMediaType = nullptr;
	}
#define DEFAULT_BUFFER_TIME 0.05 //50ms
	int nChannels = 1;//1,2
	int nBytesPerSample = 1;//1,2
	int nFrequency = 11025;//11025,22050,44100
	long lBytesPerSecond = (nBytesPerSample * nFrequency * nChannels);
	long lBufferSize = (float)lBytesPerSecond * DEFAULT_BUFFER_TIME;

	for (int i = 0; i < 2; i++)
	{
		pPin = nullptr;
		if (FAILED(DShowHelper::GetPin(pDeviceFilter, PINDIR_OUTPUT, i, &pPin)))
		{
			continue;
		}
		CComQIPtr<IAMBufferNegotiation, &IID_IAMBufferNegotiation> pAMBufferNegotiation(pPin);
		// Set the buffer size based on selected settings
		ALLOCATOR_PROPERTIES prop = { 0 };
		prop.cbBuffer = lBufferSize;
		prop.cBuffers = 6;
		prop.cbAlign = nBytesPerSample * nChannels;
		hr = pAMBufferNegotiation->SuggestAllocatorProperties(&prop);

		// Now set the actual format of the audio data
		CComQIPtr<IAMStreamConfig, &IID_IAMStreamConfig> pAMStreamConfig(pPin);
		AM_MEDIA_TYPE *pmt = nullptr;
		hr = pAMStreamConfig->GetFormat(&pmt);
		if (SUCCEEDED(hr))
		{
			WAVEFORMATEX *pWF = (WAVEFORMATEX *)pmt->pbFormat;
			pWF->nChannels = nChannels;
			pWF->nSamplesPerSec = nFrequency;
			pWF->nAvgBytesPerSec = lBytesPerSecond;
			pWF->wBitsPerSample = nBytesPerSample * 8;
			pWF->nBlockAlign = (nBytesPerSample * nChannels);
			hr = pAMStreamConfig->SetFormat(pmt);
		}


		FreeMediaType(*pmt);
		CoTaskMemFree(pmt);
		pmt = nullptr;
	}

	bool bMpeg2 = false;

	//音频编码
	std::vector<std::wstring> friendlyNamesLegacyAmFilterCategory;
	DShowHelper::GetFriendlyNames(CLSID_LegacyAmFilterCategory, friendlyNamesLegacyAmFilterCategory);
	CComPtr<IBaseFilter> pMpeg2Filter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"Microsoft MPEG-2 Audio Encoder", &pMpeg2Filter);
	if (bMpeg2)
		hr = pGraphBuilder->AddFilter(pMpeg2Filter, L"Microsoft MPEG-2 Audio Encoder");

	CComPtr<IBaseFilter> pWavFilter;
	hr = CoCreateInstance(CLSID_WavDest, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pWavFilter);
	if (!bMpeg2)
	{
		hr = pGraphBuilder->AddFilter(pWavFilter, L"WAV Dest");
	}
	/*
	CComPtr<IBaseFilter> pMp3Filter;
	hr = DShowHelper::BindFilter(CLSID_AudioCompressorCategory, L"MPEG Layer-3", &pMp3Filter);
	hr = pGraphBuilder->AddFilter(pMp3Filter, L"MPEG Layer-3");
	hr = DShowHelper::ConnectFilters(pGraphBuilder, pDeviceFilter, pMp3Filter);
	*/
	//音频输出到文件
	CComPtr<IBaseFilter> pFilewriterFilter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"File writer", &pFilewriterFilter);
	CComQIPtr<IFileSinkFilter, &IID_IFileSinkFilter> pFileSinkFilter(pFilewriterFilter);
	hr = pFileSinkFilter->SetFileName(L"d:/test.mp2", nullptr);
	hr = pGraphBuilder->AddFilter(pFilewriterFilter, L"File writer");

	pPin = nullptr;
	hr = DShowHelper::GetPin(pFilewriterFilter, PINDIR_INPUT, 0, &pPin);

	pEnumMediaTypes = nullptr;
	hr = pPin->EnumMediaTypes(&pEnumMediaTypes);
	pMediaType = nullptr;

	while (pEnumMediaTypes->Next(1, &pMediaType, nullptr) == S_OK)
	{
		auto name = GetFormatTypeName(pMediaType->formattype);
		auto subtypename = GetSubTypeName(pMediaType->subtype);
		LPWAVEFORMATEX pWaveFormatMaxtex = (LPWAVEFORMATEX)pMediaType->pbFormat;
		DeleteMediaType(pMediaType);
		pMediaType = nullptr;
	}

	//获取音频数据
	CComPtr<IBaseFilter> pSampleGrabberFilter;
	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pSampleGrabberFilter);
	CComQIPtr<ISampleGrabber, &IID_ISampleGrabber> pSampleGrabber(pSampleGrabberFilter);
	CComPtr<ISampleGrabberCB> pSampleGrabberCB(new CSampleGrabberCB);
	hr = pSampleGrabber->SetCallback(pSampleGrabberCB, 1);
	if (!bMpeg2)
	{
		AM_MEDIA_TYPE mediaType = { 0 };
		mediaType.majortype = FORMAT_WaveFormatEx;
		mediaType.subtype = MEDIASUBTYPE_PCM;
		mediaType.lSampleSize = 1;
		mediaType.bFixedSizeSamples = TRUE;
		//hr = pSampleGrabber->SetMediaType(&mediaType);
	}
	hr = pGraphBuilder->AddFilter(pSampleGrabberFilter, L"SampleGrabberFilter");

	if (bMpeg2)
	{
		hr = DShowHelper::ConnectFilters(pGraphBuilder, pDeviceFilter, pMpeg2Filter);
		hr = DShowHelper::ConnectFilters(pGraphBuilder, pMpeg2Filter, pFilewriterFilter);
		//hr = DShowHelper::ConnectFilters(pGraphBuilder, pSampleGrabberFilter, pFilewriterFilter);
	}
	else
	{
		hr = DShowHelper::ConnectFilters(pGraphBuilder, pDeviceFilter, pWavFilter);
		hr = DShowHelper::ConnectFilters(pGraphBuilder, pWavFilter, pFilewriterFilter);
	}

	//获取音频输出
	std::vector<std::wstring> friendlyNamesAudioRendererCategory;
	DShowHelper::GetFriendlyNames(CLSID_AudioRendererCategory, friendlyNamesAudioRendererCategory);


	CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
	hr = pMediaControl->Run();

	getchar();
}

void testVideo()
{
	//视频
	CComPtr<ICaptureGraphBuilder2> pVCaptureGraphBuilder;
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pVCaptureGraphBuilder);
	CComPtr<IGraphBuilder> pVGraphBuilder;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pVGraphBuilder);
	hr = pVCaptureGraphBuilder->SetFiltergraph(pVGraphBuilder);

	std::vector<std::wstring> vfriendlyNames;
	DShowHelper::GetFriendlyNames(CLSID_VideoInputDeviceCategory, vfriendlyNames);
	CComPtr<IBaseFilter> pVDeviceFilter;
	hr = DShowHelper::BindFilter(CLSID_VideoInputDeviceCategory, L"screen-capture-recorder", &pVDeviceFilter);
	hr = pVGraphBuilder->AddFilter(pVDeviceFilter, L"Video Capture");

	/*CComPtr<IBaseFilter> pVMpeg2Filter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"Microsoft MPEG-2 Video Encoder", &pVMpeg2Filter);
	hr = pVGraphBuilder->AddFilter(pVMpeg2Filter, L"Microsoft MPEG-2 Video Encoder");*/

	HDC hdc = GetDC(NULL);
	int iBitDepth = GetDeviceCaps(hdc, BITSPIXEL);
	ReleaseDC(NULL, hdc);
	AM_MEDIA_TYPE mediaType = { 0 };
	mediaType.majortype = MEDIATYPE_Video;
	switch (iBitDepth)
	{
	case 8:
	{
		mediaType.subtype = MEDIASUBTYPE_RGB8;
		break;
	}
	case 16:
	{
		mediaType.subtype = MEDIASUBTYPE_RGB555;
		break;
	}
	case 24:
	{
		mediaType.subtype = MEDIASUBTYPE_RGB24;
		break;
	}
	case 32:
	{
		mediaType.subtype = MEDIASUBTYPE_RGB32;
		break;
	}
	default:
	{
		assert(false);
		break;
	}
	}
	mediaType.formattype = FORMAT_VideoInfo;
	CComPtr<IBaseFilter> pVSampleGrabberFilter;
	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pVSampleGrabberFilter);
	CComQIPtr<ISampleGrabber, &IID_ISampleGrabber> pVSampleGrabber(pVSampleGrabberFilter);
	CComPtr<CSampleGrabberCB> pVSampleGrabberCB(new CSampleGrabberCB);
	pVSampleGrabberCB->bvideo = true;
	hr = pVSampleGrabber->SetCallback(pVSampleGrabberCB, 1);
	hr = pVGraphBuilder->AddFilter(pVSampleGrabberFilter, L"VSampleGrabberFilter");


	hr = pVSampleGrabber->SetMediaType(&mediaType);
	hr = pVCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pVDeviceFilter, pVSampleGrabberFilter, NULL);
	hr = pVSampleGrabber->GetConnectedMediaType(&mediaType);
	VIDEOINFOHEADER *vih = (VIDEOINFOHEADER*)mediaType.pbFormat;
	int width = vih->bmiHeader.biWidth;
	int height = vih->bmiHeader.biHeight;
	hr = pVSampleGrabber->SetOneShot(FALSE);
	hr = pVSampleGrabber->SetBufferSamples(TRUE);

	CComPtr<IBaseFilter> pVFilewriterFilter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"File writer", &pVFilewriterFilter);
	CComQIPtr<IFileSinkFilter, &IID_IFileSinkFilter> pVFileSinkFilter(pVFilewriterFilter);
	hr = pVFileSinkFilter->SetFileName(L"d:/test.bmp", nullptr);
	hr = pVGraphBuilder->AddFilter(pVFilewriterFilter, L"File writer");

	//hr = DShowHelper::ConnectFilters(pVGraphBuilder, pVDeviceFilter, pVSampleGrabberFilter);
	//hr = DShowHelper::ConnectFilters(pVGraphBuilder, pVSampleGrabberFilter, pVFilewriterFilter);

	CComQIPtr<IVideoWindow, &IID_IVideoWindow> pVVideoWindow(pVGraphBuilder);
	pVVideoWindow->put_Owner((OAHWND)GetDesktopWindow());
	pVVideoWindow->put_Width(400);
	pVVideoWindow->put_Height(400);
	pVVideoWindow->put_Visible(OATRUE);
	CComQIPtr<IMediaControl, &IID_IMediaControl> pVMediaControl(pVGraphBuilder);
	hr = pVMediaControl->Run();
}

void testCaptureVideo()
{
	//视频
	CComPtr<ICaptureGraphBuilder2> pVCaptureGraphBuilder;
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pVCaptureGraphBuilder);
	CComPtr<IGraphBuilder> pVGraphBuilder;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pVGraphBuilder);
	hr = pVCaptureGraphBuilder->SetFiltergraph(pVGraphBuilder);

	std::vector<std::wstring> vfriendlyNames;
	DShowHelper::GetFriendlyNames(CLSID_VideoInputDeviceCategory, vfriendlyNames);
	CComPtr<IBaseFilter> pVDeviceFilter;
	hr = DShowHelper::BindFilter(CLSID_VideoInputDeviceCategory, L"screen-capture-recorder", &pVDeviceFilter);
	hr = pVGraphBuilder->AddFilter(pVDeviceFilter, L"Video Capture");

	AM_MEDIA_TYPE mediaType = { 0 };
	mediaType.majortype = MEDIATYPE_Video;
	mediaType.subtype = MEDIASUBTYPE_RGB555;
	//mediaType.formattype = FORMAT_VideoInfo;
	CComPtr<IBaseFilter> pVSampleGrabberFilter;
	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pVSampleGrabberFilter);
	CComQIPtr<ISampleGrabber, &IID_ISampleGrabber> pVSampleGrabber(pVSampleGrabberFilter);
	hr = pVSampleGrabber->SetMediaType(&mediaType);
	hr = pVSampleGrabber->SetOneShot(TRUE);

	CComPtr<CSampleGrabberCB> pVSampleGrabberCB(new CSampleGrabberCB);
	pVSampleGrabberCB->bvideo = true;
	hr = pVSampleGrabber->SetCallback(pVSampleGrabberCB, 1);
	hr = pVGraphBuilder->AddFilter(pVSampleGrabberFilter, L"VSampleGrabberFilter");
	
	hr = DShowHelper::ConnectFilters(pVGraphBuilder, pVDeviceFilter, pVSampleGrabberFilter);

	CComQIPtr<IMediaControl, &IID_IMediaControl> pVMediaControl(pVGraphBuilder);
	hr = pVMediaControl->Run();

	getchar();
	/*CComQIPtr< IMediaEvent, &IID_IMediaEvent > pEvent(pVGraphBuilder);
	long EvCode = 0;

	hr = pEvent->WaitForCompletion(INFINITE, &EvCode);*/
}

int main()
{
	
	CoInitialize(nullptr);

	testAudio();
	//testVideo();
	//testCaptureVideo();

    return 0;
}

