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
public://回掉接口中，不能够再反调ServerObject函数
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
public:
	bool sendMsg(const char *pBuffer, unsigned int nLen)const;
	std::size_t getTaskGroupId()const;
public:
	virtual unsigned long AddRef(void)override;
	virtual unsigned long Release(void)override;
public:
	virtual bool onMsg(const char *pBuffer, unsigned int nLen);
private:
	friend class UserObjectBasePrivate;
	std::atomic_ulong m_ulRef;
	const int m_fd;
	const sockaddr_in m_addr;
	UserObjectBasePrivate *m_pUserObjectBasePrivate;
};

#endif