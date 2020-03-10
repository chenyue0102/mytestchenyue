#pragma once
#include "UPNPServiceBase.h"
class UPNPServiceConnectionManager : public UPNPServiceBase
{
public:
	UPNPServiceConnectionManager();
	~UPNPServiceConnectionManager();
public:
	bool GetProtocolInfo(std::string& Source, std::string& Sink);
};

