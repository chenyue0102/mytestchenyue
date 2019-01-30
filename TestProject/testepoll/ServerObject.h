#ifndef _SERVEROBJECT_H_
#define _SERVEROBJECT_H_
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include "InterfaceDefine.h"
struct UserObject;
struct sockaddr_in;


class ServerObject
{
	struct SOCKET_INFO
	{
		bool bClosing;
		std::string sendBytes;

		SOCKET_INFO()
			: bClosing(false)
			, sendBytes()
		{

		}
	};
public:
	ServerObject();
	~ServerObject();
public:
	bool init(IUserObjectManager *pUserObjectManager);
	bool destory();
	bool send(int fd, const char *pBuffer, unsigned int nLen);
	bool closeSocket(int fd);
	void eventLoop();
private://不加锁，不访问成员变量
	void onAsyncAccept()const;
	void onAsyncRead(int fd)const;
	void onAsyncSend(int fd)const;
	void onAsyncError(int fd)const;
private:
	void callInnerCleanSocket(int fd);
	void callInnerAccept();
	void callInnerRead(int fd);
	void callInnerSend(int fd);
	unsigned int innerDoSend(int fd, const char *pBuffer, unsigned int nLen);
	bool innerCleanSocket(int fd);
	bool innerAccept();
	bool innerRead(int fd);
	bool innerSend(int fd);
	std::size_t getTaskGroupId()const;
private:
	int m_fdListen;
	std::mutex m_mutex;
	std::map<int, SOCKET_INFO> m_acceptSocketArray;
	IUserObjectManager *m_pUserObjectManager;
};

#endif
