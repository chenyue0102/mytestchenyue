#ifndef _TCPCONTEXTMANAGER_H_
#define _TCPCONTEXTMANAGER_H_
#include "InterfaceDefine.h"
#include <mutex>
#include <map>
#include <list>
#include <set>
#include <thread>
#include <memory>
#include <condition_variable>
#include "SmartPtr.h"

struct UserObjectBase;
class UserObjectManager : public IUserObjectManager
{
	enum FirstMsgStatus
	{
		FirstMsgStatusAccept,
		FirstMsgStatusRecv,
		FirstMsgStatusClosing,
	};
	struct UserObjectInfo
	{
		FirstMsgStatus status;
		time_t tLastMsgTime;
		SmartPtr<UserObjectBase> pUserObject;
		UserObjectInfo();
	};
public:
	UserObjectManager();
	~UserObjectManager();
public:
	bool init();
	bool destroy();
public://回掉接口中，不能够再反调ServerObject函数
	void notifyAccept(int fd, sockaddr_in &addr)override;

	void notifyClose(int fd)override;

	void notifyRecv(int fd, const char *pBuffer, unsigned int recvLen)override;
private:
	void innerClearWaitFD(time_t tLastMsgTime, int fd);
	void innerClearRecvFD(time_t tLastMsgTime, int fd);
private:
	void timerProc();
private:
	std::mutex m_mutex;
	std::thread m_timerThead;
	std::condition_variable m_cv;
	//所有连接对象
	std::map<int, UserObjectInfo> m_fdObjectArray;
	//按照时间排序，等待第一个数据包的fd
	std::map<time_t, std::set<int>> m_waitFirstMsgFD;
	std::map<time_t, std::set<int>> m_recvMsgFD;
};

#endif