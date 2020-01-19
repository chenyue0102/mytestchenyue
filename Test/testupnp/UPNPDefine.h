#pragma once

#ifdef _MSC_VER

#define ISINVALID(s) (INVALID_SOCKET==(s))

#else

#ifndef SOCKET
#define SOCKET int
#endif
#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif
#ifndef ISINVALID
#define ISINVALID(s) ((s)<0)
#endif

#endif

typedef unsigned int UPNP_UI4;
static_assert(sizeof(UPNP_UI4) == 4, "");
typedef int UPNP_I4;

enum ETarget
{
	ETargetUnkwn = 0,
	ETargetRootDevice,
	ETargetUUID,
	ETargetDevice,
	ETargetServer,
};
enum EType
{
	ETypeUnkwn = 0,
	ETypeMediaRenderer,		//媒体播放器
	ETypeConnectionManager,	//负责建立和管理与接收端的网络连接
	ETypeAVTransport,		//实现暂停，快进等功能
	ETypeRenderingControl,	//调整效果，如对比度，颜色,声音等
};
