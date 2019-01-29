#ifndef _TESTUSEROBJECT_H_
#define _TESTUSEROBJECT_H_
#include <mutex>
#include <atomic>
#include <arpa/inet.h>//sockaddr_in
#include "InterfaceDefine.h"

struct sockaddr_in;
struct MSGHEADERLOCAL;
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
public:
	void setSockInfo(int fd, const sockaddr_in &addr);
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
	int getSocket()const;
	bool sendMsg(MSGHEADERLOCAL *pHeader);
	std::size_t getTaskGroupId()const;
private:
	void InnerDoRecvMsg();
public:
	virtual unsigned long AddRef(void)override;

	virtual unsigned long Release(void)override;
protected:
	virtual bool onMsg(MSGHEADERLOCAL *pHeader);
private:
	mutable std::mutex m_mutex;
	ObjectStatus m_objectStatus;
	std::atomic_ulong m_ulRef;
	int m_fd;
	sockaddr_in m_addr;
	std::string m_recvBuffer;
	time_t m_tLastMsgTime;
};

#endif