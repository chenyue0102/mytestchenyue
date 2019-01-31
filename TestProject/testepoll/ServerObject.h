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
	void onAsyncAcceptError()const;
	void onAsyncRead(int fd)const;
	void onAsyncSend(int fd)const;
	void onAsyncError(int fd)const;
private:
	void callInnerCleanSocket(int fd);
	void callInnerAccept();
	void callInnerAcceptError();
	void callInnerRead(int fd);
	void callInnerSend(int fd);
	ssize_t innerDoSend(int fd, const char *pBuffer, ssize_t nLen);
	bool innerCleanSocket(int fd);
	bool innerAccept();
	bool innerRead(int fd);
	//发送缓冲数据
	bool innerSendCachingData(int fd);
	std::size_t getTaskGroupId()const;
private:
	int m_fdListen;
	std::mutex m_mutex;
	std::map<int, SOCKET_INFO> m_acceptSocketArray;
	IUserObjectManager *m_pUserObjectManager;
};

#endif
