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
	ETypeMediaRenderer,		//ý�岥����
	ETypeConnectionManager,	//�������͹�������ն˵���������
	ETypeAVTransport,		//ʵ����ͣ������ȹ���
	ETypeRenderingControl,	//����Ч������Աȶȣ���ɫ,������
};
