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
	ObjectStatusProcess,
	ObjectStatusClose,
};

class UserObjectBase;
class UserObjectBasePrivate
{
public:
	UserObjectBasePrivate(UserObjectBase &userObjectBase);
	~UserObjectBasePrivate();
public://�ص��ӿ���
	void notifyRecv(const char * pBuffer, unsigned int recvLen);
	void notifyClose();
public:
	void asyncDoRecvMsg();
public:
	ObjectStatus getObjectStatus()const;
	void setStopProcess();
private:
	bool getMsgArray(std::list<std::string> &msgArray);
	void stopRecv();
private:
	UserObjectBase &m_userObjectBase;
	mutable std::mutex m_mutex;
	ObjectStatus m_objectStatus;
	std::string m_recvBuffer;
};

#endif