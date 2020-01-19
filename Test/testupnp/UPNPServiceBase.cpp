#include "UPNPServiceBase.h"
#include <assert.h>
#include <sstream>
extern "C" {
#include "miniwget.h"
}
#include "tinyxml.h"
#include "UPNPProtocolSerialize.h"


UPNPServiceBase::UPNPServiceBase(EType type)
	: mEType(type)
{
}


UPNPServiceBase::~UPNPServiceBase()
{
}

EType UPNPServiceBase::getType()
{
	return mEType;
}

void UPNPServiceBase::setService(const UPNPDDDService service, const std::string & host, unsigned short port, unsigned int scope_id)
{
	mUPNPDDDService = service;
	mUPNPHttp.setHttpInfo(host, port, scope_id);
	mUPNPHttp.setControlURLPath(mUPNPDDDService.controlURL);
	std::string url = "http://" + host;
	if (80 != port)
	{
		url += ":" + std::to_string(port);
	}
	url += mUPNPDDDService.SCPDURL;
	sendGetServiceDescriptionDocument(url);
}

void UPNPServiceBase::sendGetServiceDescriptionDocument(const std::string &url)
{
	char *descXML = nullptr;
	do
	{
		char lanaddr[40] = { 0 };
		int descXMLsize = 0;
		if (nullptr == (descXML = (char*)miniwget_getaddr(url.c_str(), &descXMLsize, lanaddr, _countof(lanaddr), 0, NULL)))
		{
			assert(false);
			break;
		}
		if (nullptr == descXML)
		{
			assert(false);
			break;
		}
		if (!SerializeHelper::UnpackValue(descXML, descXMLsize, mUPNPSDDRoot, SerializeExport::EnumSerializeFormatXml))
		{
			assert(false);
			break;
		}
	} while (false);
	if (nullptr != descXML)
	{
		free(descXML);
		descXML = nullptr;
	}
}

std::string UPNPServiceBase::packSoapXml(const std::string actionName, std::vector<SoapArgument> arguments)
{
	TiXmlDocument XmlDocument;

	TiXmlDeclaration *pXmlDeclaration = new TiXmlDeclaration("1.0", "utf-8", "");
	XmlDocument.LinkEndChild(pXmlDeclaration);
	
	TiXmlElement *pRootValue = new TiXmlElement("s:Envelope");
	pRootValue->SetAttribute("s:encodingStyle", "http://schemas.xmlsoap.org/soap/encoding/");
	pRootValue->SetAttribute("xmlns:s", "http://schemas.xmlsoap.org/soap/envelope/");
	XmlDocument.LinkEndChild(pRootValue);
	
	TiXmlElement *pBody = new TiXmlElement("s:Body");
	pRootValue->LinkEndChild(pBody);

	std::string actName = "u:" + actionName;
	TiXmlElement *pAction = new TiXmlElement(actName.c_str());
	pAction->SetAttribute("xmlns:u", mUPNPDDDService.serviceType.c_str());
	for (auto &arg : arguments)
	{
		TiXmlElement *pElement = new TiXmlElement(arg.name.c_str());
		pAction->LinkEndChild(pElement);
		if (!arg.value.empty())
		{
			TiXmlText *pText = new TiXmlText(arg.value.c_str());
			pElement->LinkEndChild(pText);
		}
	}
	pBody->LinkEndChild(pAction);

	TiXmlPrinter XmlPrinter;
	XmlDocument.Accept(&XmlPrinter);
	std::string ret = XmlPrinter.CStr();
	return ret;
}

int UPNPServiceBase::soapPostSubmit(const std::string & action, std::vector<SoapArgument> arguments, std::string & result)
{
	std::string soapXml = packSoapXml(action, arguments);
	std::string tmpAction = mUPNPDDDService.serviceType + '#' + action;
	return mUPNPHttp.soapPostSubmit(tmpAction, soapXml, "1.1", result);
}
