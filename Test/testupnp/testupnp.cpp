// testupnp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
extern "C"{
#include "miniupnpc.h"
#include "miniwget.h"
#include "server.h"
}
#include <Winsock2.h>
#include <regex>
#include <string>
#include <sstream>
#include <thread>
#include <atomic>
#include <condition_variable>
#pragma comment(lib, "miniupnpc.lib")
#pragma comment(lib, "KSSerializeD_Static.lib")
#include "KSSerializeHelper.h"
#include "KSSerialize.h"
#include <codecvt>
#include "UPNPDevInfo.h"
#include "UPNPProtocolSerialize.h"
#include "UPNPServiceAVTransport.h"


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
			//���õ�������
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
std::atomic_bool g_exit = false;
int main()
{
	TestChild tc;
	std::string tcss(R"(<root><xx:major>11</xx:major><minor>22</minor></root>)");
	SerializeHelper::UnpackValue(tcss.data(), tcss.size(), tc, SerializeExport::EnumSerializeFormatXml);



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
		//"urn:schemas-upnp-org:device:MediaRenderer:1",		//ý�岥����
		//"urn:schemas-upnp-org:service:ConnectionManager:1",		//�������͹�������ն˵���������
		//"urn:schemas-upnp-org:service:AVTransport:1",			//ʵ����ͣ������ȹ���
		//"urn:schemas-upnp-org:service:RenderingControl:1",		//����Ч������Աȶȣ���ɫ,������
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
	UPNPDevInfo *pInfo = nullptr;
	for (UPNPDev *dev = devlist; NULL != dev; dev = dev->pNext)
	{
		if (nullptr == strstr(dev->descURL, "10.0.30.32"))
		{
			continue;
		}
		pInfo = new UPNPDevInfo();
		pInfo->setDevInfo(dev->descURL, dev->st, dev->usn, dev->scope_id);
		//char * descXML = 0;
		//int descXMLsize = 0;
		//char lanaddr[40] = { 0 };
		//ss << "descURL:" << dev->descURL << std::endl;
		//ss << "st:" << dev->st << std::endl;
		//ss << "usn:" << dev->usn << std::endl;
		//

		//descXML = (char*)miniwget_getaddr(dev->descURL, &descXMLsize, lanaddr, _countof(lanaddr), 0, NULL);
		//
		//UPNPDDDRoot root;
		//SerializeHelper::UnpackValue(descXML, descXMLsize, root, SerializeExport::EnumSerializeFormatXml);
		//if (0 != descXML)
		//{
		//	std::string s(descXML, descXMLsize);
		//	ss << "xml:" << std::endl << s.c_str() << std::endl;
		//}
		//
		////printf("xml==============================\r\n%s\r\n", descXML);
		//free(descXML);
	}
	if (nullptr != pInfo)
	{
		void serverThread();
		std::thread t = std::thread(&serverThread);
		UPNPServiceAVTransport *pAVTransport = pInfo->getAVTransport();
		int a = 0;
		std::string result;
		do
		{
			printf("0:exit 1:seturl 2:pause 3:stop 4:play 5:seek 6:pos 7:reg \r\n");
			scanf("%d", &a);
			switch (a)
			{
			case 1: 
			{
				pAVTransport->SetAVTransportURI(0, "https://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8", "");
				break;
			}
			case 2:
			{
				pAVTransport->Pause(0);
				break;
			}
			case 3:
			{
				pAVTransport->Stop(0);
				break;
			}
			case 4:
			{
				pAVTransport->Play(0, "1");
				break;
			}
			case 5:
			{
				pAVTransport->Seek(0, "ABS_TIME", "00:01:00");
				break;
			}
			case 6:
			{
				UPNPPositionInfo pos;
				pAVTransport->GetPositionInfo(0, pos);
			}
			case 7:
			{
				std::string event("upnp:AVTransportURI");
				std::string callback("http://10.0.30.48:9080/1234notify");
				pAVTransport->regCallback(event, callback, 60*10);
				break;
			}
			}
		} while (0 != a);
		
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

void Dispatch(HTTPReqMessage *req, HTTPResMessage *res)
{
	{
		const char *p = "HTTP/1.1 200 OK\r\n\r\n";
		memcpy(res->_buf, p, strlen(p));
		res->_index = strlen(p);
	}
}

void serverThread()
{
	HTTPServer srv;
	HTTPServerInit(&srv, 9080);
	HTTPServerRunLoop(&srv, &Dispatch);
	HTTPServerClose(&srv);
}
