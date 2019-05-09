#pragma once
#include <vector>
#include <string>
#include <DShow.h>
namespace DShowHelper
{
//�����Ƶ������Ƶ���豸ö��
//CLSID_AudioInputDeviceCategory CLSID_VideoInputDeviceCategory
HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);

//��ȡ�豸����
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

