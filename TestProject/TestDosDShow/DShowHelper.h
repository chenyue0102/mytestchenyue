#pragma once
#include <vector>
#include <string>
#include <DShow.h>
namespace DShowHelper
{
//获得音频或者视频的设备枚举
//CLSID_AudioInputDeviceCategory CLSID_VideoInputDeviceCategory
HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);

//获取设备名称
void GetFriendlyNames(REFGUID category, std::vector<std::wstring> &friendlyNames);

//
HRESULT BindFilter(REFGUID category, LPCTSTR lpFriendlyName, IBaseFilter **ppFilter);

HRESULT AddFilterByCLSID(
	IGraphBuilder *pGraph,  // Pointer to the Filter Graph Manager.
	const GUID& clsid,      // CLSID of the filter to create.
	LPCWSTR wszName,        // A name for the filter.
	IBaseFilter **ppF);      // Receives a pointer to the filter.

HRESULT GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired,
	int iNum, IPin **ppPin);

HRESULT GetUnConnectedPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, IPin **ppPin);

HRESULT ConnectFilters(IGraphBuilder *pGraph, IPin *pOutPin,IBaseFilter *pDest);

HRESULT ConnectFilters(
	IGraphBuilder *pGraph,
	IBaseFilter *pSrc,
	IBaseFilter *pDest);

bool IsVFWCard(IBaseFilter *pDeviceFilter);
bool IsWDMCard(IBaseFilter *pDeviceFilter);


};

