#pragma once
#include "UPNPDefine.h"
#include "UPNPProtocol.h"
#include "UPNPHttp.h"

class UPNPServiceBase
{
public:
	struct SoapArgument
	{
		std::string name;
		std::string value;
	};
public:
	UPNPServiceBase(EType type);
	virtual ~UPNPServiceBase();
public:
	EType getType();
	virtual void setService(const UPNPDDDService service, const std::string & host, unsigned short port, unsigned int scope_id);
	void sendGetServiceDescriptionDocument(const std::string &url);
	std::string packSoapXml(const std::string actionName, std::vector<SoapArgument> arguments);
	int soapPostSubmit(const std::string &action, std::vector<SoapArgument> arguments, std::string &result);
protected:
	EType mEType;
	UPNPDDDService mUPNPDDDService;
	UPNPSDDRoot mUPNPSDDRoot;
	UPNPHttp mUPNPHttp;
};

