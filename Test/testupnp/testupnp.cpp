// testupnp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
extern "C"{
#include "miniupnpc.h"
#include "miniwget.h"
}
#include <Winsock2.h>
#include <regex>
#include <string>
#include <sstream>
#pragma comment(lib, "miniupnpc.lib")
#pragma comment(lib, "KSSerializeD_Static.lib")
#include "KSSerializeHelper.h"
#include "KSSerialize.h"
#include <codecvt>
#include "UPNPDevInfo.h"
#include "UPNPProtocolSerialize.h"

struct TestChild
{
	int major = 0;
	int minor = 0;
};

inline bool SerializeStruct(ISerialize &pSerialize, TestChild & Value)
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

struct TestArgument
{
	std::string name;
	std::string direction;
};
inline bool SerializeStruct(ISerialize &pSerialize, TestArgument & Value)
{
	try
	{
		SERIALIZE(name);
		SERIALIZE(direction);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

struct TestStruct
{
	std::string sendEvents;
	int a;
	std::string b;
	TestChild specVersion;
	std::vector<TestArgument> argumentList;
	std::vector<int> testInt;
};
inline bool SerializeStruct(ISerialize &pSerialize, TestStruct & Value)
{
	try
	{
		const char rootName[] = { 's', 'c', 'p', 'd', };
		pSerialize.setSerializeParam(EnumSerializeParamXmlRootName, rootName, _countof(rootName));
		SERIALIZE(a);
		SERIALIZE(b);
		SERIALIZE(specVersion);
		{
			KSSerialize::CSwitchXmlChildName switchChildName(pSerialize, "ID");
			KSSerialize::CSwitchXmlValuePosition switchValuePosition(pSerialize, EnumXmlValuePositionAttribute);
			SERIALIZE(testInt);
		}
		
		{
			KSSerialize::CSwitchXmlChildName switchChildName(pSerialize, "argument");
			SERIALIZE(argumentList);
		}
		{
			//放置到属性中
			KSSerialize::CSwitchXmlValuePosition switchValuePosition(pSerialize, EnumXmlValuePositionAttribute);
			SERIALIZE(sendEvents);
		}
		
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}
int main()
{
	TestStruct t;
	t.sendEvents = "no";
	t.a = 1;
	t.b = "hello";
	t.specVersion.major = 1;
	t.testInt.push_back(1);
	t.testInt.push_back(2);

	TestArgument ta;
	ta.name = "InstanceID";
	ta.direction = "in";
	t.argumentList.push_back(ta);
	ta.name = "CurrentBlueVideoGain";
	ta.direction = "out";
	t.argumentList.push_back(ta);

	std::string data;
	SerializeHelper::PackValue(t, data, SerializeExport::EnumSerializeFormatXml);

	TestStruct t2;
	SerializeHelper::UnpackValue(data.data(), data.size(), t2, SerializeExport::EnumSerializeFormatXml);

	std::string st("urn:schemas-upnp-org:device:MediaRenderer:1");
	std::regex expr(R"(^urn:(\S+):(device|service):(\S+):([0-9]+)$)", std::regex::ECMAScript | std::regex::icase);
	std::smatch matchResult;
	if (std::regex_match(st, matchResult, expr) && matchResult.size() == 5)
	{
		for (auto &match : matchResult) {
			std::string s = match;
			//printf("%s", s.c_str());
		}
	}
	WSADATA wsaData;
	int nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	const char * const deviceList[] = {
		//"urn:schemas-upnp-org:device:MediaRenderer:1",		//媒体播放器
		//"urn:schemas-upnp-org:service:ConnectionManager:1",		//负责建立和管理与接收端的网络连接
		//"urn:schemas-upnp-org:service:AVTransport:1",			//实现暂停，快进等功能
		//"urn:schemas-upnp-org:service:RenderingControl:1",		//调整效果，如对比度，颜色,声音等
		//"urn:schemas-upnp-org:service:WANIPConnection:1",
		//"urn:schemas-upnp-org:service:WANPPPConnection:1",
		"upnp:rootdevice",										//root device
		//"ssdp:all",
		0
	};
	int error = 0;
	struct UPNPDev *devlist = upnpDiscoverDevices(deviceList, 2000, NULL, NULL, 0, 0, 2, &error, 0);
	//printf("==============\r\n");
	std::stringstream ss;
	ss << "=======================" << std::endl;
	for (UPNPDev *dev = devlist; NULL != dev; dev = dev->pNext)
	{
		UPNPDevInfo *pInfo = new UPNPDevInfo();
		pInfo->setDevInfo(dev->descURL, dev->st, dev->usn, dev->scope_id);
		char * descXML = 0;
		int descXMLsize = 0;
		char lanaddr[40] = { 0 };
		ss << "descURL:" << dev->descURL << std::endl;
		ss << "st:" << dev->st << std::endl;
		ss << "usn:" << dev->usn << std::endl;
		

		descXML = (char*)miniwget_getaddr(dev->descURL, &descXMLsize, lanaddr, _countof(lanaddr), 0, NULL);
		
		UPNPDDDRoot root;
		SerializeHelper::UnpackValue(descXML, descXMLsize, root, SerializeExport::EnumSerializeFormatXml);
		if (0 != descXML)
		{
			std::string s(descXML, descXMLsize);
			ss << "xml:" << std::endl << s.c_str() << std::endl;
		}
		
		//printf("xml==============================\r\n%s\r\n", descXML);
		free(descXML);
	}
	//printf("==================\r\n");
	/*std::string s = ss.str();
	std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
	std::wstring strw = utf8_wstr_cvt.from_bytes(s);
	typedef std::codecvt_byname< wchar_t, char, std::mbstate_t > cvt_byname;
	std::wstring_convert <std::codecvt_byname <wchar_t, char, std::mbstate_t >> char_wchar_cvt(new cvt_byname("Chinese_China.936"));
	std::string str = char_wchar_cvt.to_bytes(strw);
	printf("%s", str.c_str());
	freeUPNPDevlist(devlist);*/
    return 0;
}

