#ifndef _TESTUSEROBJECT_H_
#define _TESTUSEROBJECT_H_
#include <mutex>
#include <atomic>
#include <arpa/inet.h>//sockaddr_in
#include "InterfaceDefine.h"

struct MSGHEADER;
struct sockaddr_in;
class UserObjectBase : public IUnknownEx
{
	enum ObjectStatus
	{
		ObjectStatusAccept,
		ObjectStatusRecv,
		ObjectStatusClose,
	};
public:
	UserObjectBase();
	virtual ~UserObjectBase();
public://回掉接口中，不能够再反调ServerObject函数
	void setSockInfo(int fd, const sockaddr_in &addr);
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
public:
	int getSocket()const;
	bool sendMsg(const char *pBuffer, unsigned int nLen);
	std::size_t getTaskGroupId()const;
private:
	void InnerDoRecvMsg();
public:
	virtual unsigned long AddRef(void)override;

	virtual unsigned long Release(void)override;
protected:
	virtual bool onMsg(const char *pBuffer, unsigned int nLen);
private:
	mutable std::mutex m_mutex;
	ObjectStatus m_objectStatus;
	std::atomic_ulong m_ulRef;
	int m_fd;
	unsigned short m_port;
	char m_ipAddress[INET_ADDRSTRLEN];
	std::string m_recvBuffer;
	time_t m_tLastMsgTime;
};

#endif