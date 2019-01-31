#ifndef _USEROBJECTBASEPRIVATE_H_
#define _USEROBJECTBASEPRIVATE_H_
#include <mutex>
#include <list>
#include <string>
#include <time.h>

enum ObjectStatus
{
	ObjectStatusAccept,
	ObjectStatusRecv,
	ObjectStatusClose,
};

class UserObjectBase;
class UserObjectBasePrivate
{
public:
	UserObjectBasePrivate(UserObjectBase &userObjectBase);
	~UserObjectBasePrivate();
public://回掉接口中
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
public:
	void asyncDoRecvMsg();
public:
	ObjectStatus getObjectStatus()const;
private:
	bool getMsgArray(std::list<std::string> &msgArray);
	void stopRecv();
private:
	void innerNotifyRecv(const char * pBuffer, unsigned int recvLen);
private:
	UserObjectBase &m_userObjectBase;
	mutable std::mutex m_mutex;
	ObjectStatus m_objectStatus;
	std::string m_recvBuffer;
};

#endif