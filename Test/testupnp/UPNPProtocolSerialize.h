#ifndef __UPNP_PROTOCOL_SERIALIZE_H__
#define __UPNP_PROTOCOL_SERIALIZE_H__
#include "ISerialize.h"
#include "KSSerialize.h"
#include "KSSerializeHelper.h"
#include "UPNPProtocol.h"

inline bool SerializeStruct(ISerialize &pSerialize, UPNPDDDSpecVersion & Value)
{
	try
	{
		SERIALIZE(major);
		SERIALIZE(minor);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPDDDDevice & Value)
{
	try
	{
		SERIALIZE(deviceType);
		SERIALIZE(presentationURL);
		SERIALIZE(friendlyName);
		SERIALIZE(manufacturer);
		SERIALIZE(manufacturerURL);
		SERIALIZE(modelDescription);
		SERIALIZE(modelName);
		SERIALIZE(modelURL);
		SERIALIZE(UDN);
		{
			CSwitchXmlChildName switchChildName(pSerialize, "service");
			SERIALIZE(serviceList);
		}
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPDDDService & Value)
{
	try
	{
		SERIALIZE(serviceType);
		SERIALIZE(serviceId);
		SERIALIZE(SCPDURL);
		SERIALIZE(controlURL);
		SERIALIZE(eventSubURL);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPDDDRoot & Value)
{
	try
	{
		SERIALIZE(specVersion);
		SERIALIZE(device);
		SERIALIZE(URLBase);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////
//服务
inline bool SerializeStruct(ISerialize &pSerialize, UPNPSDDArgument & Value)
{
	try
	{
		SERIALIZE(name);
		SERIALIZE(direction);
		SERIALIZE(relatedStateVariable);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPSDDAction & Value)
{
	try
	{
		SERIALIZE(name);
		{
			CSwitchXmlChildName switchChildName(pSerialize, "argument");
			SERIALIZE(argumentList);
		}
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPSDDAllowedValueRange & Value)
{
	try
	{
		SERIALIZE(minimum);
		SERIALIZE(maximum);
		SERIALIZE(step);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPSDDServiceState & Value)
{
	try
	{
		SERIALIZE(sendEvents);
		SERIALIZE(name);
		SERIALIZE(dataType);
		{
			CSwitchXmlChildName switchChildName(pSerialize, "allowedValue");
			SERIALIZE(allowedValueList);
		}
		if (SerializeExport::EnumSerializeIOWrite == pSerialize.GetSerializeType())
		{
			//写的时候,不写空值
			if (!Value.defaultValue.empty())
			{
				SERIALIZE(defaultValue);
			}
			if (!Value.allowedValueRange.minimum.empty())
			{
				SERIALIZE(allowedValueRange);
			}
		}
		else
		{
			SERIALIZE(defaultValue);
			SERIALIZE(allowedValueRange);
		}
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

inline bool SerializeStruct(ISerialize &pSerialize, UPNPSDDRoot & Value)
{
	try
	{
		if (pSerialize.GetSerializeFormat() == SerializeExport::EnumSerializeFormatXml)
		{
			//xml的根节点名称市scpd
			const char rootName[] = { 's', 'c', 'p', 'd', };
			pSerialize.setSerializeParam(EnumSerializeParamXmlRootName, rootName, _countof(rootName));
		}
		SERIALIZE(specVersion);
		{
			CSwitchXmlChildName switchChildName(pSerialize, "action");
			SERIALIZE(actionList);
		}
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

#endif