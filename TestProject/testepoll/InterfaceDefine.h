#ifndef _INTERFACEDEFINE_H_
#define _INTERFACEDEFINE_H_

struct sockaddr_in;
struct IUserObjectManager
{
	virtual void notifyAccept(int fd, sockaddr_in &addr) = 0;

	virtual void notifyClose(int fd) = 0;
	
	virtual void notifyRecv(int fd, const char *pBuffer, unsigned int recvLen) = 0;
	
};

struct IUnknownEx
{
	virtual unsigned long AddRef(void) = 0;

	virtual unsigned long Release(void) = 0;
};


#endif
