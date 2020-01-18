#include "UPNPServiceBase.h"
#include <assert.h>
extern "C" {
#include "miniwget.h"
}
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

void UPNPServiceBase::setService(const UPNPDDDService service)
{
	mUPNPDDDService = service;
}

void UPNPServiceBase::sendGetServiceDescriptionDocument(const std::string url)
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
