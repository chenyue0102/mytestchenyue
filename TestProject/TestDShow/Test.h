#pragma once
#include <dshow.h>
#include <string>
#include <vector>

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);

void DisplayDeviceInformation(IEnumMoniker *pEnum);

std::vector<std::wstring> GetFriendlyNames(IEnumMoniker *pEnum);

IMoniker* FindCaptureDeviceMoniker(IEnumMoniker *pEnum, const WCHAR *pFriendlyName);

HRESULT InitCaptureGraphBuilder(
	IGraphBuilder **ppGraph,  // Receives the pointer.
	ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
);