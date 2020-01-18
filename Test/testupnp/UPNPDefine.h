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
	ETypeMediaRenderer,		//ý�岥����
	ETypeConnectionManager,	//�������͹�������ն˵���������
	ETypeAVTransport,		//ʵ����ͣ������ȹ���
	ETypeRenderingControl,	//����Ч������Աȶȣ���ɫ,������
};
