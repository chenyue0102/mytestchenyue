#include "UPNPServiceConnectionManager.h"

UPNPServiceConnectionManager::UPNPServiceConnectionManager()
	: UPNPServiceBase(ETypeConnectionManager)
{
}

UPNPServiceConnectionManager::~UPNPServiceConnectionManager()
{
}

bool UPNPServiceConnectionManager::GetProtocolInfo(std::string& Source, std::string& Sink)
{
	std::vector<SoapArgument> arguments =
	{

	};
	std::string result;
	return 200 == soapPostSubmit("GetProtocolInfo", arguments, result);
}

