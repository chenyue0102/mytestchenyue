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
		std::string sendBytes;
	};
public:
	ServerObject();
	~ServerObject();
public:
	bool init(IUserObjectManager *pUserObjectManager);
	bool destory();
	bool send(int fd, const char *pBuffer, unsigned int nLen);
	void eventLoop();
private:
	bool onAccept();
	bool onRead(int fd);
	bool onSend(int fd);
	bool onError(int fd);
	unsigned int innerDoSend(int fd, const char *pBuffer, unsigned int nLen);
	bool innerCleanSocket(int fd);
private:
	int m_fdListen;
	std::mutex m_mutex;
	std::map<int, SOCKET_INFO> m_acceptSocketArray;
	IUserObjectManager *m_pUserObjectManager;
};

#endif
