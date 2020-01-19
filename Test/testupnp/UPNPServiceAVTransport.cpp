#include "UPNPServiceAVTransport.h"
#include <assert.h>



UPNPServiceAVTransport::UPNPServiceAVTransport()
	: UPNPServiceBase(ETypeAVTransport)
{
}


UPNPServiceAVTransport::~UPNPServiceAVTransport()
{
}

bool UPNPServiceAVTransport::GetMediaInfo(UPNP_UI4 InstanceID, std::string & NrTracks)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
	};
	std::string result;
	int stateCode = soapPostSubmit("GetMediaInfo", arguments, result);

	return 200 == stateCode;
}

bool UPNPServiceAVTransport::GetPositionInfo(UPNP_UI4 InstanceID, UPNPPositionInfo &posInfo)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
	};
	std::string result;
	int stateCode = soapPostSubmit("GetPositionInfo", arguments, result);

	return 200 == stateCode;
}

bool UPNPServiceAVTransport::Pause(UPNP_UI4 InstanceID)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
	};
	std::string result;
	return 200 == soapPostSubmit("Pause", arguments, result);
}

bool UPNPServiceAVTransport::Play(UPNP_UI4 InstanceID, const std::string & Speed)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
		{ "Speed", Speed },
	};
	std::string result;
	return 200 == soapPostSubmit("Play", arguments, result);
}

bool UPNPServiceAVTransport::Seek(UPNP_UI4 InstanceID, const std::string & Unit, const std::string & Target)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
		{ "Unit", Unit },
		{ "Target", Target },
	};
	std::string result;
	return 200 == soapPostSubmit("Seek", arguments, result);
}

bool UPNPServiceAVTransport::SetAVTransportURI(UPNP_UI4 InstanceID, const std::string & CurrentURI, const std::string & CurrentURIMetaData)
{
	std::vector<SoapArgument> arguments = 
	{
		{"InstanceID", std::to_string(InstanceID) },
		{"CurrentURI", CurrentURI },
		{"CurrentURIMetaData", CurrentURIMetaData },
	};
	std::string result;
	return 200 == soapPostSubmit("SetAVTransportURI", arguments, result);
}

bool UPNPServiceAVTransport::Stop(UPNP_UI4 InstanceID)
{
	std::vector<SoapArgument> arguments =
	{
		{ "InstanceID", std::to_string(InstanceID) },
	};
	std::string result;
	return 200 == soapPostSubmit("Stop", arguments, result);
}
