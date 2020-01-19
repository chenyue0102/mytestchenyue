#include "UPNPDevInfo.h"
#include <regex>
#include <assert.h>
extern "C" {
#include "miniupnpc.h"
#include "miniwget.h"
}
#include "UPNPProtocolSerialize.h"
#include "UPNPServiceAVTransport.h"


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
	sendGetDeviceDescriptionDocument(mDescURL);
}

void UPNPDevInfo::sendGetDeviceDescriptionDocument(const std::string &url)
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
		//获取通信控制的url地址,如果URLBase为空，则使用获取设备描述文档的url
		std::string strUrl;
		if (mUPNPDDDRoot.URLBase.empty())
		{
			strUrl = url;
		}
		else
		{
			strUrl = mUPNPDDDRoot.URLBase;
		}
		const int MAXHOSTNAMELEN = 64;//定义在miniwget.c中
		char hostname[MAXHOSTNAMELEN + 1] = { 0 };
		unsigned short port = 0;
		char *path = nullptr;
		unsigned int scope_id = 0;
		if (0 == parseURL(strUrl.c_str(), hostname, &port, &path, &scope_id))
		{
			strUrl += '/';
			if (0 == parseURL(strUrl.c_str(), hostname, &port, &path, &scope_id))
			{
				assert(false);
				break;
			}
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
				case ETypeConnectionManager:
					break;
				case ETypeAVTransport:
				{
					mAVTransport = std::make_shared<UPNPServiceAVTransport>();
					mAVTransport->setService(service, hostname, port, scope_id);
					//std::string metaData;// = R"(<DIDL-Lite xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/" xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:dlna="urn:schemas-dlna-org:metadata-1-0/" xmlns:sec="http://www.sec.co.kr/"><item id="video-item-755" parentID="1" restricted="0"><dc:title>V91016-201954</dc:title><dc:creator>&lt;unknown&gt;</dc:creator><upnp:class>object.item.videoItem</upnp:class><upnp:albumArtURI>http://10.0.28.173:8192/storage/emulated/0/msi/.videothumb/video_thumb_video-item-755.png</upnp:albumArtURI><dc:description/><res protocolInfo="http-get:*:video/m3u8:*" size="90836128" duration="0:0:42" resolution="1920x1080">https://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8</res></item></DIDL-Lite>)";
					//mAVTransport->SetAVTransportURI("0", "https://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8", metaData);
					break;
				}
				case ETypeRenderingControl:
					break;
				default:
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

UPNPServiceAVTransport * UPNPDevInfo::getAVTransport()
{
	return mAVTransport.get();
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
