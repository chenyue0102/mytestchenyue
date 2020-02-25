#include "UPNPServiceRenderingControl.h"

UPNPServiceRenderingControl::UPNPServiceRenderingControl()
	: UPNPServiceBase(ETypeRenderingControl)
{

}

UPNPServiceRenderingControl::~UPNPServiceRenderingControl()
{

}

bool UPNPServiceRenderingControl::GetVolumeDBRange(int minVolume, int maxVolume)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(0) },
		{ "Channel", "Master" },
	};
	std::string result;
	int stateCode = soapPostSubmit("GetVolumeDBRange", arguments, result);

	return 200 == stateCode;
}
