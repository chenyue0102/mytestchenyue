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

bool UPNPServiceRenderingControl::SetVolume(long InstanceID, std::string Channel, float DesiredVolume)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(0) },
		{ "Channel", "Master" },
		{ "DesiredVolume", "0.5" },
	};
	std::string result;
	int stateCode = soapPostSubmit("SetVolume", arguments, result);

	return 200 == stateCode;
}
