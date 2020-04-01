#ifndef __UPNP_PROTOCOL_H__
#define __UPNP_PROTOCOL_H__
#include <string>
#include <vector>
#include "UPNPDefine.h"


//版本号
struct UPNPDDDSpecVersion
{
	int major;
	int minor;

	UPNPDDDSpecVersion()
		: major()
		, minor()
	{}
};

//设备信息
struct UPNPDDDService
{
	std::string serviceType;			//服务类型,urn:schemas-upnp-org:service:AVTransport:1
	std::string serviceId;				//服务标识符,服务实例的唯一标识,在这一设备描述中保持唯一性
	std::string SCPDURL;				//Service Control Protocol Description on URL,获取服务描述文档的url
	std::string controlURL;				//向服务发送控制消息的URL
	std::string eventSubURL;			//订阅服务事件的URL
};

//device描述
struct UPNPDDDDevice
{
	std::string deviceType;				//urn:schemas-upnp-org:device:MediaRenderer:1
	std::string presentationURL;		//设备展示的URL,非必须
	std::string friendlyName;			//给用户展示的描述文字
	std::string manufacturer;			//制造商名称
	std::string manufacturerURL;		//制造商URL
	std::string modelDescription;		//给用户阅读的详细描述,最多128字符,非必须
	std::string modelName;				//型号
	std::string modelURL;				//型号信息URL,非必须
	std::string UDN;					//唯一设备名,设备UUID,格式:uuid:F7CA5454-3F48-4390-8009-283ee448c1ab
	std::vector<UPNPDDDService> serviceList;//服务信息,xml中子节点名称为service
};

//UPNP Device Description Document
//设备描述文档
struct UPNPDDDRoot
{
	UPNPDDDSpecVersion specVersion;		//version
	UPNPDDDDevice device;				//设备信息
	std::string URLBase;				//结构体中url需要拼接的头部,1.0版本存在,1.0以上版本不存在,

	UPNPDDDRoot()
	{}
};
///////////////////////////////////////////////////
//服务动作参数
struct UPNPSDDArgument
{
	std::string name;					//参数名称,最多32字符,不应包含-
	std::string direction;				//in输入,out输出,in在前,out在后
	std::string relatedStateVariable;	//本参数和后边的某个状态关联
};

//服务动作
struct UPNPSDDAction
{
	std::string name;					//动作名称,最多32字符,不应包含-
	std::vector<UPNPSDDArgument> argumentList;//参数列表,xml内部条目名字为argument
};

//合法值范围
struct UPNPSDDAllowedValueRange
{
	std::string minimum;				//最小值
	std::string maximum;				//最大值
	std::string step;					//步进
};

//服务状态
struct UPNPSDDServiceState
{
	std::string sendEvents;				//状态变量值发生变化,是否生成事件消息,存储在xml属性中,no yes
	std::string name;					//状态名称,最多32字符,不能包含-,厂商定义已X_开头,标准定义的不以X_,A_开头
	std::string dataType;				//参数类型,string,i4,ui4,等
	std::vector<std::string> allowedValueList;//允许的参数值,推荐使用,xml字段名字为allowedValue
	std::string defaultValue;			//期望的初值,推荐使用
	UPNPSDDAllowedValueRange allowedValueRange;//参数范围,推荐使用
};
//服务,
//Service Description Document
//root name scpd
struct UPNPSDDRoot
{
	UPNPDDDSpecVersion specVersion;		//version
	std::vector<UPNPSDDAction> actionList;//动作列表,xml内部条目名称action
};

///////////////////////////////////////////////////////
//AVTransport Action
struct UPNPPositionInfo
{
	UPNP_UI4 Track;						//
	std::string TrackDuration;			//持续时间，00:50:00
	std::string TrackURI;				//播放的url
	std::string RelTime;				//00:10:00
	std::string AbsTime;				//00:10:00
	UPNP_I4 RelCount;					//
	UPNP_I4 AbsCount;					//

	UPNPPositionInfo()
		: Track()
		, RelCount()
		, AbsCount()
	{}
};
#endif