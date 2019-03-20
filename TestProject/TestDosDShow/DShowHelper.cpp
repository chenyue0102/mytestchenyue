#include "DShowHelper.h"
#include <assert.h>
#include <atlbase.h>
#pragma comment(lib, "Strmiids.lib")

#define FRIENDLY_NAME L"FriendlyName"
namespace DShowHelper
{
HRESULT EnumerateDevices(REFGUID category, IEnumMoniker ** ppEnum)
{
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == ppEnum)
		{
			assert(false);
			break;
		}
		CComPtr<ICreateDevEnum> pDevEnum;
		// Create the System Device Enumerator.
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
		if (FAILED(hr))
		{
			assert(false);
			break;
		}
		// Create an enumerator for the category.
		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
		if (hr == S_FALSE)
		{
			hr = VFW_E_NOT_FOUND;
		}
	} while (false);
	
	return hr;
}
void GetFriendlyNames(REFGUID category, std::vector<std::wstring>& friendlyNames)
{
	CComPtr<IEnumMoniker> pEnum;
	if (FAILED(EnumerateDevices(category, &pEnum)))
	{
		assert(false);
		return;
	}
	pEnum->Reset();
	CComPtr<IMoniker> pMoniker;
	while (pEnum->Next(1, &pMoniker, nullptr) == S_OK)
	{
		CComPtr<IPropertyBag> pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		pMoniker = NULL;
		if (FAILED(hr))
		{
			assert(false);
			continue;
		}
		CComVariant var;
		hr = pPropBag->Read(FRIENDLY_NAME, &var, 0);
		if (FAILED(hr)
			|| NULL == var.bstrVal)
		{
			assert(false);
			continue;
		}
		friendlyNames.push_back(std::wstring(var.bstrVal));
	}
}
HRESULT BindFilter(REFGUID category, LPCTSTR lpFriendlyName, IBaseFilter ** ppFilter)
{

	if (nullptr == lpFriendlyName
		|| nullptr == ppFilter)
	{
		assert(false);
		return E_FAIL;
	}
	CComPtr<IEnumMoniker> pEnum;
	if (FAILED(EnumerateDevices(category, &pEnum)))
	{
		assert(false);
		return E_FAIL;
	}
	pEnum->Reset();
	for (CComPtr<IMoniker> pMoniker;pEnum->Next(1, &pMoniker, nullptr) == S_OK; pMoniker = nullptr)
	{
		CComPtr<IPropertyBag> pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		if (FAILED(hr))
		{
			assert(false);
			continue;
		}
		CComVariant var;
		hr = pPropBag->Read(FRIENDLY_NAME, &var, 0);
		if (FAILED(hr)
			|| NULL == var.bstrVal)
		{
			assert(false);
			continue;
		}
		if (0 == wcscmp(var.bstrVal, lpFriendlyName))
		{
			return pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
		}
	}
	return E_FAIL;
}
HRESULT AddFilterByCLSID(IGraphBuilder * pGraph, const GUID & clsid, LPCWSTR wszName, IBaseFilter ** ppF)
{
	HRESULT hr = E_FAIL;

do
{
	if (NULL == pGraph
		|| NULL == wszName
		|| NULL == ppF)
	{
		assert(false);
		break;
	}
	CComPtr<IBaseFilter> pFilter;
	if (FAILED(hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pFilter)))
	{
		assert(false);
		break;
	}
	if (FAILED(hr = pGraph->AddFilter(pFilter, wszName)))
	{
		assert(false);
		break;
	}
	*ppF = pFilter.Detach();
	hr = S_OK;
} while (false);

return hr;
}
HRESULT GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin ** ppPin)
{
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == pFilter
			|| nullptr == ppPin)
		{
			assert(false);
			break;
		}
		*ppPin = nullptr;
		CComPtr<IEnumPins> pEnumPins;
		if (FAILED(hr = pFilter->EnumPins(&pEnumPins)))
		{
			assert(false);
			break;
		}
		pEnumPins->Reset();
		IPin *pPin = nullptr;
		while (pEnumPins->Next(1, &pPin, nullptr) == S_OK)
		{
			PIN_DIRECTION pindir = (PIN_DIRECTION)3;
			if (SUCCEEDED(pPin->QueryDirection(&pindir))
				&& pindir == dirrequired)
			{
				if (0 == iNum)
				{
					*ppPin = pPin;
					break;
				}
				--iNum;
			}
			pPin->Release();
			pPin = nullptr;
		}
		hr = (nullptr == *ppPin) ? E_FAIL : S_OK;
	} while (false);

	return hr;
}

HRESULT GetUnConnectedPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, IPin ** ppPin)
{
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == pFilter
			|| nullptr == ppPin)
		{
			assert(false);
			break;
		}
		*ppPin = nullptr;
		CComPtr<IEnumPins> pEnumPins;
		if (FAILED(hr = pFilter->EnumPins(&pEnumPins)))
		{
			assert(false);
			break;
		}
		pEnumPins->Reset();
		IPin *pPin = nullptr;
		while (pEnumPins->Next(1, &pPin, nullptr) == S_OK)
		{
			PIN_DIRECTION pindir = (PIN_DIRECTION)3;
			if (SUCCEEDED(pPin->QueryDirection(&pindir))
				&& pindir == dirrequired)
			{
				CComPtr<IPin> pConnectTo;// 
				hr = pPin->ConnectedTo(&pConnectTo);
				if (VFW_E_NOT_CONNECTED == hr 
					&& !pConnectTo)
				{
					*ppPin = pPin;
					break;
				}
			}
			pPin->Release();
			pPin = nullptr;
		}
		hr = (nullptr == *ppPin) ? E_FAIL : S_OK;
	} while (false);

	return hr;
}

HRESULT ConnectFilters(IGraphBuilder *pGraph, IPin *pOutPin, IBaseFilter *pDest)
{
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == pGraph
			|| nullptr == pOutPin
			|| nullptr == pDest)
		{
			assert(false);
			break;
		}
		CComPtr<IPin> pInPin;
		if (FAILED(hr = GetPin(pDest, PINDIR_INPUT, 0, &pInPin)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = pGraph->Connect(pOutPin, pInPin)))
		{
			assert(false);
			break;
		}
	} while (false);
	return hr;
}

HRESULT ConnectFilters(IGraphBuilder * pGraph, IBaseFilter * pSrc, IBaseFilter * pDest)
{
	HRESULT hr = E_FAIL;

	do
	{
		if (nullptr == pGraph
			|| nullptr == pSrc
			|| nullptr == pDest)
		{
			assert(false);
			break;
		}
		CComPtr<IPin> pPinIn, pPinOut;
		if (FAILED(hr = GetPin(pSrc, PINDIR_OUTPUT, 0, &pPinOut)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = GetPin(pDest, PINDIR_INPUT, 0, &pPinIn)))
		{
			assert(false);
			break;
		}
		if (FAILED(hr = pGraph->Connect(pPinOut, pPinIn)))
		{
			assert(false);
			break;
		}
		hr = S_OK;
	} while (false);
	return hr;
}

bool IsVFWCard(IBaseFilter *pDeviceFilter)
{
	bool bRet = false;

	do
	{
		if (nullptr == pDeviceFilter)
		{
			assert(false);
			break;
		}
		CComQIPtr<IAMVfwCaptureDialogs, &IID_IAMVfwCaptureDialogs> pIAMVfwCaptureDialogs(pDeviceFilter);
		if (!pIAMVfwCaptureDialogs)
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool IsWDMCard(IBaseFilter *pDeviceFilter)
{
	bool bRet = false;

	do
	{
		if (nullptr == pDeviceFilter)
		{
			assert(false);
			break;
		}
		CComQIPtr<IAMAnalogVideoDecoder, &IID_IAMAnalogVideoDecoder> pAMAnalogVideoDecoder(pDeviceFilter);
		if (!pAMAnalogVideoDecoder)
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

};


