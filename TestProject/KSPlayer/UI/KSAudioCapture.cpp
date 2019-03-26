#include "KSAudioCapture.h"
#include <vector>
#include <string>
#include <assert.h>
#include <objbase.h>
#include <atlbase.h>
#include <qedit.h>
#include <strmif.h>
#include "ui_KSAudioCapture.h"
#include "DShowHelper.h"

struct KSAudioCaptureData
{
	Ui::KSAudioCapture ui;
	std::vector<std::wstring> inputDevices;
	std::vector<std::wstring> outputDevices;
	CComPtr<ICaptureGraphBuilder2> pCaptureGraphBuilder2;
	CComPtr<IGraphBuilder> pGraphBuilder;
	CComPtr<IBaseFilter> pInputDevice;
	CComPtr<IBaseFilter> pOutputDevice;
};
KSAudioCapture::KSAudioCapture(QWidget *parent)
	: QWidget(parent)
	, m_pKSAudioCaptureData(new KSAudioCaptureData)
{
	auto &ui = m_pKSAudioCaptureData->ui;
	ui.setupUi(this);

	connect(ui.pushButtonPlay, SIGNAL(clicked()), SLOT(slotPlay()));
	connect(ui.pushButtonPause, SIGNAL(clicked()), SLOT(slotPause()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), SLOT(slotStop()));
	connect(ui.pushButtonResume, SIGNAL(clicked()), SLOT(slotResume()));

	init();
	refreshDevices();
}

KSAudioCapture::~KSAudioCapture()
{
	if (nullptr != m_pKSAudioCaptureData)
	{
		auto &pCaptureGraphBuilder2 = m_pKSAudioCaptureData->pCaptureGraphBuilder2;
		auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;
		
		slotStop();
		pGraphBuilder.Release();
		pCaptureGraphBuilder2.Release();
	}
	delete m_pKSAudioCaptureData;
	m_pKSAudioCaptureData = nullptr;
}

void KSAudioCapture::init()
{
	CoInitialize(nullptr);
	HRESULT hr = S_OK;
	do
	{
		auto &pCaptureGraphBuilder2 = m_pKSAudioCaptureData->pCaptureGraphBuilder2;
		auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;
		if (FAILED(hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pCaptureGraphBuilder2)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&pGraphBuilder)))
		{
			assert(false);
			break;
		}
		if (FAILED(pCaptureGraphBuilder2->SetFiltergraph(pGraphBuilder)))
		{
			assert(false);
		}
	} while (false);
}

void KSAudioCapture::refreshDevices()
{
	auto &inputDevices = m_pKSAudioCaptureData->inputDevices;
	auto &outputDevices = m_pKSAudioCaptureData->outputDevices;
	auto &ui = m_pKSAudioCaptureData->ui;
	//枚举声音输入设备
	inputDevices.clear();
	DShowHelper::GetFriendlyNames(CLSID_AudioInputDeviceCategory, inputDevices);
	ui.comboBoxInput->clear();
	for (auto &dev : inputDevices)
	{
		ui.comboBoxInput->addItem(QString::fromStdWString(dev));
	}

	//枚举输出设备
	outputDevices.clear();
	DShowHelper::GetFriendlyNames(CLSID_AudioRendererCategory, outputDevices);
	ui.comboBoxOutput->clear();
	for (auto &dev : outputDevices)
	{
		ui.comboBoxOutput->addItem(QString::fromStdWString(dev));
	}
}

void KSAudioCapture::slotStop()
{
	auto &pInputDevice = m_pKSAudioCaptureData->pInputDevice;
	auto &pOutputDevice = m_pKSAudioCaptureData->pOutputDevice;
	auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;

	if (pGraphBuilder)
	{
		{
			CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
			if (pMediaControl)
			{
				if (FAILED(pMediaControl->Stop()))
				{
					assert(false);
				}
			}
		}
		if (pInputDevice)
		{
			if (FAILED(pGraphBuilder->RemoveFilter(pInputDevice)))
			{
				assert(false);
			}
			pInputDevice.Release();
		}
		if (pOutputDevice)
		{
			if (FAILED(pGraphBuilder->RemoveFilter(pOutputDevice)))
			{
				assert(false);
			}
			pOutputDevice.Release();
		}
	}
}

void KSAudioCapture::slotPause()
{
	auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;
	CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
	if (pMediaControl)
	{
		if (FAILED(pMediaControl->Pause()))
		{
			assert(false);
		}
	}
}

void KSAudioCapture::slotResume()
{
	auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;
	CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
	if (pMediaControl)
	{
		if (FAILED(pMediaControl->Run()))
		{
			assert(false);
		}
	}
}

void KSAudioCapture::slotPlay()
{
	slotStop();
	bool bRet = false;
	do
	{
		auto &ui = m_pKSAudioCaptureData->ui;
		auto &pInputDevice = m_pKSAudioCaptureData->pInputDevice;
		auto &pOutputDevice = m_pKSAudioCaptureData->pOutputDevice;
		auto &pGraphBuilder = m_pKSAudioCaptureData->pGraphBuilder;
		std::wstring strInputDevice = ui.comboBoxInput->currentText().toStdWString();
		std::wstring strOutputDevice = ui.comboBoxOutput->currentText().toStdWString();
		if (strInputDevice.empty()
			|| strOutputDevice.empty())
		{
			break;
		}
		if (!pGraphBuilder)
		{
			assert(false);
			break;
		}
		HRESULT hr = S_OK;
		if (FAILED(hr = DShowHelper::BindFilter(CLSID_AudioInputDeviceCategory, strInputDevice.c_str(), &pInputDevice)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = DShowHelper::BindFilter(CLSID_AudioRendererCategory, strOutputDevice.c_str(), &pOutputDevice)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = pGraphBuilder->AddFilter(pInputDevice, strInputDevice.c_str())))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = pGraphBuilder->AddFilter(pOutputDevice, strOutputDevice.c_str())))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = DShowHelper::ConnectFilters(pGraphBuilder, pInputDevice, pOutputDevice)))
		{
			assert(false);
			break;
		}
		CComQIPtr<IMediaControl, &IID_IMediaControl> pMediaControl(pGraphBuilder);
		if (!pMediaControl)
		{
			assert(false);
			break;
		}
		if (FAILED(hr = pMediaControl->Run()))
		{
			assert(false);
			break;
		}
		bRet = true;
	} while (false);

	if (!bRet)
	{
		slotStop();
	}
}