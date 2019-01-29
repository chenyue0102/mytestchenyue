#ifndef _TCPCONTEXTMANAGER_H_
#define _TCPCONTEXTMANAGER_H_
#include "InterfaceDefine.h"
#include <mutex>
#include <map>
#include <memory>


struct UserObjectBase;
class UserObjectManager : public IUserObjectManager
{
public:
	UserObjectManager();
	~UserObjectManager();
public:
	void notifyAccept(int fd, sockaddr_in &addr)override;

	void notifyClose(int fd)override;

	void notifyRecv(int fd, const char *pBuffer, unsigned int recvLen)override;
private:
	std::mutex m_mutex;
	std::map<int, std::unique_ptr<UserObjectBase>> m_fdObjectArray;
};

#endif