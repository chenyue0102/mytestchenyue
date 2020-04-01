// testupnp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
extern "C"{
#include "miniupnpc.h"
#include "miniwget.h"
//#include "server.h"
}
#include <Winsock2.h>
#include <ws2tcpip.h>   
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
#include "UPNPServiceConnectionManager.h"
#include "UPNPServiceRenderingControl.h"
#include "UPNPServiceKaiShu.h"
#include "tinyxml.h"


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
std::atomic_bool g_exit = false;
#include <atlenc.h>

char* g_str = R"(<e:propertyset
    xmlns:e="urn:schemas-upnp-org:event-1-0">
    <e:property>
        <LastChange>&lt;Event xmlns = &quot;urn:schemas-upnp-org:metadata-1-0/AVT/&quot;&gt;&lt;InstanceID val=&quot;0&quot;&gt;&lt;NumberOfTracks  val=&quot;1&quot;/&gt;&lt;CurrentTrack  val=&quot;1&quot;/&gt;&lt;CurrentMediaDuration  val=&quot;00:04:01&quot;/&gt;&lt;CurrentTrackDuration  val=&quot;00:04:01&quot;/&gt;&lt;/InstanceID&gt;&lt;/Event&gt;</LastChange>
    </e:property>
</e:propertyset>)";

void startssdsever(ULONG ip1, ULONG ip2)
{
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

	do
	{
		if (s < 0) 
		{
			assert(false);
			break;
		}
		int option = 1;
		if (setsockopt(s,
			SOL_SOCKET,
			SO_REUSEADDR,
			(const char*)&option,
			sizeof(option)) < 0)
		{
			assert(false);
			break;
		}
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(1900);
		/*if (ipaddress.empty())
			addr.sin_addr.s_addr = htonl(INADDR_ANY);
		else
			addr.sin_addr.s_addr = inet_addr(ipaddress.c_str());*/
		addr.sin_addr.s_addr = ip1;
		if (bind(s, (sockaddr*)&addr, sizeof(addr)) < 0)
		{
			assert(false);
			break;
		}
		ip_mreq imr = { 0 };
		imr.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
		//imr.imr_interface.s_addr = htonl(INADDR_ANY);
		imr.imr_interface.s_addr = ip2;
		if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&imr, sizeof(imr)) < 0)
		{
			assert(false);
			break;
		}
		char* buffer = new char[2048];
		sockaddr_in recvAddr;
		int recvAddrLen = sizeof(recvAddr);
		while (true)
		{
			int recvLen = recvfrom(s, buffer, 2048, 0, (sockaddr*)&recvAddr, &recvAddrLen);
			if (recvLen < 0)
			{
				break;
			}
			buffer[recvLen] = '\0';
			if (strstr(buffer, "discover") != nullptr) 
			{
				std::stringstream ss;
				ss <<"begin " <<  buffer << "threadid:" <<std::this_thread::get_id() << " ip "<< ip1 << ip2 << " end " <<std::endl;
				OutputDebugStringA(ss.str().c_str());
			}
			if (strstr(buffer, "192.168.3.2") != nullptr)
			{
				OutputDebugStringA(buffer);
			}
			//printf("%s\r\n", buffer);
			//OutputDebugStringA(buffer);
		}
	} while (false);
}
int main()
{
	TiXmlDocument XmlDocument;
	XmlDocument.Parse(g_str, nullptr, TIXML_ENCODING_UTF8);
	TiXmlNode *pNode = XmlDocument.FirstChild();
	TiXmlNode* pNode2 = pNode->FirstChild();
	TiXmlNode* pNode3 = pNode2->FirstChild();
	std::string text = pNode3->FirstChild()->Value();

	char c[100];
	std::snprintf(c, 100, "abc");
	unsigned char ggb2312[] = { 0xc4, 0xe3, 0xba, 0xc3, 0x00 };
	char* gb2312 = (char*)ggb2312;
	typedef std::codecvt_byname< wchar_t, char, std::mbstate_t > cvt_byname;
	std::wstring_convert <std::codecvt_byname <wchar_t, char, std::mbstate_t >> char_wchar_cvt(new cvt_byname("Chinese_China.936"));
	std::wstring strW = char_wchar_cvt.from_bytes(gb2312);
	std::string str = char_wchar_cvt.to_bytes(strW);

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
	//std::thread tttt(&startssdsever, htonl(INADDR_ANY), htonl(INADDR_ANY));
	//std::thread tttt2(&startssdsever, inet_addr("192.168.3.2"), inet_addr("192.168.3.2"));
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	UPNPDevInfo *pInfo = nullptr;
	for (UPNPDev *dev = devlist; NULL != dev; dev = dev->pNext)
	{
		//if (nullptr == strstr(dev->descURL, "10.0.30.32"))
		if (nullptr == strstr(dev->descURL, "192.168.3.7"))
		//if (nullptr == strstr(dev->descURL, "192.168.3.2"))
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
	//getchar();
	if (nullptr != pInfo)
	{
		void serverThread();
		//std::thread t = std::thread(&serverThread);
		UPNPServiceAVTransport *pAVTransport = pInfo->getAVTransport();
		UPNPServiceConnectionManager* pConnectionManager = pInfo->getConnectionManager();
		UPNPServiceRenderingControl *pRenderingControl = pInfo->getRenderingControl();
		UPNPServiceKaiShu* pUPNPServiceKaiShu = pInfo->getKaiShu();
		int a = 0;
		std::string result;
		do
		{
			printf("0:exit 1:seturl 2:pause 3:stop 4:play 5:seek 6:pos 7:reg 8:getprotocolinfo 9:GetVolumeDBRange\r\n");
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
				break;
			}
			case 7:
			{
				std::string event("upnp:AVTransportURI");
				std::string callback("http://10.0.30.48:9080/1234notify");
				pAVTransport->regCallback(event, callback, 60*10);
				break;
			}
			case 8: 
			{
				std::string Source, Sink;
				pConnectionManager->GetProtocolInfo(Source, Sink);
				break;

			}
			case 9:
			{
				int minVolume = 0, maxVolume = 0;
				pRenderingControl->GetVolumeDBRange(minVolume, maxVolume);
				break;
			}
			case 10:
			{
				pUPNPServiceKaiShu->X_kaishustory_Login("1234", "5678");
				break;
			}
			case 11: {
				pRenderingControl->SetVolume(0, "Master", 0.5);
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

//void Dispatch(HTTPReqMessage *req, HTTPResMessage *res)
//{
//	{
//		const char *p = "HTTP/1.1 200 OK\r\n\r\n";
//		memcpy(res->_buf, p, strlen(p));
//		res->_index = strlen(p);
//	}
//}
//
//void serverThread()
//{
//	HTTPServer srv;
//	HTTPServerInit(&srv, 9080);
//	HTTPServerRunLoop(&srv, &Dispatch);
//	HTTPServerClose(&srv);
//}
