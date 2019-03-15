// TestDosDShow.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <assert.h>
#include <objbase.h>
#include <atlbase.h>
#include <qedit.h>
#include <strmif.h>
#include <atomic>
#include "DShowHelper.h"

bool SaveBitmap(const char *pFileName, int width, int height, int biBitCount, const void *pBuf, int nBufLen)
{
	if (nullptr == pFileName
		|| 0 == width
		|| 0 == height
		|| !(biBitCount == 24 || biBitCount == 32)
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
		SaveBitmap("d:/1.bmp", 1920, 1080, 24, pBuffer, BufferLen);
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
HRESULT hr = S_OK;
void testAudio()
{
	CComPtr<ICaptureGraphBuilder2> pCaptureGraphBuilder2;
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCaptureGraphBuilder2);
	CComPtr<IGraphBuilder> pGraphBuilder;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pGraphBuilder);
	hr = pCaptureGraphBuilder2->SetFiltergraph(pGraphBuilder);

	//��ȡ��Ƶ����
	std::vector<std::wstring> friendlyNames;
	DShowHelper::GetFriendlyNames(CLSID_AudioInputDeviceCategory, friendlyNames);
	CComPtr<IBaseFilter> pDeviceFilter;
	hr = DShowHelper::BindFilter(CLSID_AudioInputDeviceCategory, friendlyNames[0].c_str(), &pDeviceFilter);
	hr = pGraphBuilder->AddFilter(pDeviceFilter, L"Audio Capture");

	//��Ƶ����
	std::vector<std::wstring> friendlyNamesLegacyAmFilterCategory;
	DShowHelper::GetFriendlyNames(CLSID_LegacyAmFilterCategory, friendlyNamesLegacyAmFilterCategory);
	CComPtr<IBaseFilter> pMpeg2Filter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"Microsoft MPEG-2 Audio Encoder", &pMpeg2Filter);
	hr = pGraphBuilder->AddFilter(pMpeg2Filter, L"Microsoft MPEG-2 Audio Encoder");

	/*
	CComPtr<IBaseFilter> pMp3Filter;
	hr = DShowHelper::BindFilter(CLSID_AudioCompressorCategory, L"MPEG Layer-3", &pMp3Filter);
	hr = pGraphBuilder->AddFilter(pMp3Filter, L"MPEG Layer-3");
	hr = DShowHelper::ConnectFilters(pGraphBuilder, pDeviceFilter, pMp3Filter);
	*/
	//��Ƶ������ļ�
	CComPtr<IBaseFilter> pFilewriterFilter;
	hr = DShowHelper::BindFilter(CLSID_LegacyAmFilterCategory, L"File writer", &pFilewriterFilter);
	CComQIPtr<IFileSinkFilter, &IID_IFileSinkFilter> pFileSinkFilter(pFilewriterFilter);
	hr = pFileSinkFilter->SetFileName(L"d:/test.mp2", nullptr);
	hr = pGraphBuilder->AddFilter(pFilewriterFilter, L"File writer");

	//��ȡ��Ƶ����
	CComPtr<IBaseFilter> pSampleGrabberFilter;
	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pSampleGrabberFilter);
	CComQIPtr<ISampleGrabber, &IID_ISampleGrabber> pSampleGrabber(pSampleGrabberFilter);
	CComPtr<ISampleGrabberCB> pSampleGrabberCB(new CSampleGrabberCB);
	hr = pSampleGrabber->SetCallback(pSampleGrabberCB, 1);
	hr = pGraphBuilder->AddFilter(pSampleGrabberFilter, L"SampleGrabberFilter");

	hr = DShowHelper::ConnectFilters(pGraphBuilder, pDeviceFilter, pMpeg2Filter);
	hr = DShowHelper::ConnectFilters(pGraphBuilder, pMpeg2Filter, pSampleGrabberFilter);
	hr = DShowHelper::ConnectFilters(pGraphBuilder, pSampleGrabberFilter, pFilewriterFilter);

	//��ȡ��Ƶ���
	std::vector<std::wstring> friendlyNamesAudioRendererCategory;
	DShowHelper::GetFriendlyNames(CLSID_AudioRendererCategory, friendlyNamesAudioRendererCategory);


	CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
	hr = pMediaControl->Run();
}

void testVideo()
{
	//��Ƶ
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
	//��Ƶ
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
	mediaType.subtype = MEDIASUBTYPE_RGB24;
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

	CComQIPtr< IMediaEvent, &IID_IMediaEvent > pEvent(pVGraphBuilder);
	long EvCode = 0;

	hr = pEvent->WaitForCompletion(INFINITE, &EvCode);
}

int main()
{
	
	CoInitialize(nullptr);

	testCaptureVideo();

    return 0;
}

