#include "Test.h"
#include <atlbase.h>
#pragma comment(lib, "Strmiids.lib")

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker ** ppEnum)
{
	// Create the System Device Enumerator.
	CComPtr<ICreateDevEnum> pDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the category.
		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
		if (hr == S_FALSE)
		{
			hr = VFW_E_NOT_FOUND;
		}
	}
	return hr;
}

void DisplayDeviceInformation(IEnumMoniker * pEnum)
{
	CComPtr<IMoniker> pMoniker;
	pEnum->Reset();
	while (pEnum->Next(1, &pMoniker, nullptr) == S_OK)
	{
		CComPtr<IPropertyBag> pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		pMoniker = nullptr;
		if (FAILED(hr))
		{
			continue;
		}
		CComVariant var;
		/*hr = pPropBag->Read(L"Description", &var, 0);
		if (FAILED(hr))
		{*/
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
		//}
		if (SUCCEEDED(hr))
		{
			OutputDebugStringW(var.bstrVal);
		}

	}
}

std::vector<std::wstring> GetFriendlyNames(IEnumMoniker * pEnum)
{
	std::vector<std::wstring> v;
	CComPtr<IMoniker> pMoniker;
	pEnum->Reset();
	while (pEnum->Next(1, &pMoniker, nullptr) == S_OK)
	{
		CComPtr<IPropertyBag> pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		pMoniker = nullptr;
		if (FAILED(hr))
		{
			continue;
		}
		CComVariant var;
		hr = pPropBag->Read(L"FriendlyName", &var, 0);
		if (SUCCEEDED(hr))
		{
			v.push_back(var.bstrVal);
		}
	}
	return v;
}

IMoniker * FindCaptureDeviceMoniker(IEnumMoniker * pEnum, const WCHAR * pFriendlyName)
{
	CComPtr<IMoniker> pMoniker;
	pEnum->Reset();
	while (pEnum->Next(1, &pMoniker, nullptr) == S_OK)
	{
		if (nullptr == pFriendlyName)
		{
			break;
		}
		CComPtr<IPropertyBag> pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		if (FAILED(hr))
		{
			pMoniker = nullptr;
			continue;
		}
		CComVariant var;
		hr = pPropBag->Read(L"FriendlyName", &var, 0);
		if (SUCCEEDED(hr)
			&& 0 == wcscmp(var.bstrVal, pFriendlyName))
		{
			break;
		}
		pMoniker = nullptr;
	}
	return pMoniker.Detach();
}

HRESULT InitCaptureGraphBuilder(
	IGraphBuilder **ppGraph,  // Receives the pointer.
	ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
)
{
	if (!ppGraph || !ppBuild)
	{
		return E_POINTER;
	}
	IGraphBuilder *pGraph = NULL;
	ICaptureGraphBuilder2 *pBuild = NULL;

	// Create the Capture Graph Builder.
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
		CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild);
	if (SUCCEEDED(hr))
	{
		// Create the Filter Graph Manager.
		hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void**)&pGraph);
		if (SUCCEEDED(hr))
		{
			// Initialize the Capture Graph Builder.
			pBuild->SetFiltergraph(pGraph);

			// Return both interface pointers to the caller.
			*ppBuild = pBuild;
			*ppGraph = pGraph; // The caller must release both interfaces.
			return S_OK;
		}
		else
		{
			pBuild->Release();
		}
	}
	return hr; // Failed
}