#pragma once
#include "UPNPDefine.h"
#include "UPNPProtocol.h"
class UPNPServiceBase
{
public:
	UPNPServiceBase(EType type);
	virtual ~UPNPServiceBase();
public:
	EType getType();
	virtual void setService(const UPNPDDDService service);
	void sendGetServiceDescriptionDocument(const std::string url);
protected:
	EType mEType;
	UPNPDDDService mUPNPDDDService;
	UPNPSDDRoot mUPNPSDDRoot;
};

