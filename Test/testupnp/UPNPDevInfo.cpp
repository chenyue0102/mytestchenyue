#include "UPNPDevInfo.h"
#include <regex>
#include <assert.h>
extern "C" {
#include "miniupnpc.h"
#include "miniwget.h"
}
#include "UPNPProtocolSerialize.h"


UPNPDevInfo::UPNPDevInfo()
	: mETarget(ETargetUnkwn)
	, mEType(ETypeUnkwn)
	, mVersion(0)
{
}


UPNPDevInfo::~UPNPDevInfo()
{
}

void UPNPDevInfo::setDevInfo(const char *descURL, const char *st, const char *usn, unsigned int scope_id)
{
	mDescURL = descURL;
	mST = st;
	mUSN = usn;
	parseST(mST);
	mUUID = getUUIDFromUSN(mUSN);
}

void UPNPDevInfo::sendGetDeviceDescriptionDocument(const std::string url)
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
		if (!SerializeHelper::UnpackValue(descXML, descXMLsize, mUPNPDDDRoot, SerializeExport::EnumSerializeFormatXml))
		{
			assert(false);
			break;
		}
		std::regex expr(R"(^urn:(\S+):service:(\S+):([0-9]+)$)", std::regex::ECMAScript | std::regex::icase);
		for (auto &service : mUPNPDDDRoot.device.serviceList)
		{
			//urn:schemas-upnp-org:service:AVTransport:1
			std::smatch matchResult;
			if (std::regex_match(service.serviceType, matchResult, expr) && matchResult.size() == 4)
			{
				std::string strType = matchResult[2];
				EType type = getType(strType);
				switch (type)
				{
				case ETypeMediaRenderer:
					break;
				}
			}
		}
	} while (false);
	
	if (nullptr != descXML)
	{
		free(descXML);
		descXML = nullptr;
	}
}

void UPNPDevInfo::parseST(const std::string &st)
{
	//upnp:rootdevice 根设备
	//uuid:device - UUID 表示本设备的uuid表示位device - uuid
	//urn : schema - upnp - org : device : device - Type : version 表示本设备类型为device - type设备，版本是version
	//urn : schema - upnp - org : service : service - Type : version 表示服务类型为service - type的设备，版本是version
	const char *strRootDevice = "upnp:rootdevice";
	const char *strUUID = "uuid:";
	if (0 == _stricmp(st.c_str(), strRootDevice))
	{
		mETarget = ETargetRootDevice;
	}
	else if (0 == _strnicmp(st.c_str(), strUUID, strlen(strUUID)))
	{
		mETarget = ETargetUUID;
	}
	else
	{
		//urn:schemas-upnp-org:device:MediaRenderer:1
		std::regex expr(R"(^urn:(\S+):(device|service):(\S+):([0-9]+)$)", std::regex::ECMAScript | std::regex::icase);
		std::smatch matchResult;
		if (std::regex_match(st, matchResult, expr) && matchResult.size() == 5)
		{
			//第一个为匹配的全项
			std::string deviceOrServer = matchResult[2];
			if (0 == _stricmp(deviceOrServer.c_str(), "device"))
			{
				mETarget = ETargetDevice;
			}
			else if (0 == _stricmp(deviceOrServer.c_str(), "service"))
			{
				mETarget = ETargetServer;
			}
			else
			{
				mETarget = ETargetUnkwn;
				assert(false);
			}
			std::string type = matchResult[3];
			mEType = getType(type);
			std::string version = matchResult[4];
			mVersion = atoi(version.c_str());
		}
	}
}

std::string UPNPDevInfo::getUUIDFromUSN(const std::string & usn)
{
	std::string uuid;
	//uuid:F7CA5454-3F48-4390-8009-283ee448c1ab::upnp:rootdevice
	std::regex expr(R"(^uuid:([0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12})\S*$)", std::regex::ECMAScript | std::regex::icase);
	std::smatch matchResult;
	if (std::regex_match(usn, matchResult, expr) && matchResult.size() == 2)
	{
		uuid = matchResult[1];
	}
	return uuid;
}

EType UPNPDevInfo::getType(const std::string & type)
{
	std::pair<EType, const char*> idNames[] =
	{
		{ ETypeMediaRenderer,"MediaRenderer" },
		{ ETypeConnectionManager,"ConnectionManager" },
		{ ETypeAVTransport,"AVTransport" },
		{ ETypeRenderingControl,"RenderingControl" },
	};
	EType ret = ETypeUnkwn;
	for (auto &pair : idNames)
	{
		if (0 == _stricmp(pair.second, type.c_str()))
		{
			ret = pair.first;
			break;
		}
	}
	return ret;
}
