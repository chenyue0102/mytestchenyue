#pragma once
#include "UPNPServiceBase.h"

class UPNPServiceRenderingControl : public UPNPServiceBase
{
public:
	UPNPServiceRenderingControl();
	~UPNPServiceRenderingControl();
public:
	bool GetVolumeDBRange(int minVolume, int maxVolume);
};

