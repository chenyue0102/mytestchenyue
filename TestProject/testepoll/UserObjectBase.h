#ifndef _USEROBJECTBASE_H_
#define _USEROBJECTBASE_H_
#include <atomic>
#include <arpa/inet.h>//sockaddr_in
#include "InterfaceDefine.h"

struct MSGHEADER;
class UserObjectBasePrivate;
class UserObjectBase : public IUnknownEx
{
public:
	UserObjectBase(int fd, const sockaddr_in &addr);
	virtual ~UserObjectBase();
public://�ص��ӿ��У����ܹ��ٷ���ServerObject����
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
public:
	int getSocket()const;
	bool sendMsg(const char *pBuffer, unsigned int nLen)const;
	bool closeSocket()const;
	std::size_t getTaskGroupId()const;
public:
	virtual unsigned long AddRef(void)override;
	virtual unsigned long Release(void)override;
public:
	virtual bool onMsg(const char *pBuffer, unsigned int nLen);
private:
	std::atomic_ulong m_ulRef;
	const int m_fd;
	const sockaddr_in m_addr;
	UserObjectBasePrivate *m_pUserObjectBasePrivate;
};

#endif