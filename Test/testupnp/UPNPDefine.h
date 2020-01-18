#pragma once

#define MEDIA_RENDERER "MediaRenderer"
#define CONNECTION_MANAGER "ConnectionManager"
#define AVTRANSPORT "AVTransport"
#define RENDERING_CONTROL "RenderingControl"

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
