#pragma once
#include "UPNPServiceBase.h"

class UPNPServiceRenderingControl : public UPNPServiceBase
{
public:
	UPNPServiceRenderingControl();
	~UPNPServiceRenderingControl();
public:
	bool GetVolumeDBRange(int minVolume, int maxVolume);
	bool SetVolume(long InstanceID, std::string Channel, float DesiredVolume);
};

