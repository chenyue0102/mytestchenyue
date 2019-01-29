#include "ServerObject.h"
#include <sys/socket.h>
#include <arpa/inet.h>//sockaddr_in
#include <fcntl.h>//fcntl
#include <unistd.h>
#include "Log.h"
#include "Single.h"
#include "EPollObject.h"

#define MY_PORT 5617
#define BACKLOG 5
ServerObject::ServerObject()
	: m_fdListen(-1)
	, m_mutex()
{
}


ServerObject::~ServerObject()
{
}

bool ServerObject::open()
{
	bool bRes = false;

	do
	{
		if ((m_fdListen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			LOG(LOG_ERR, "ServerObject::open socket errno=%d\n", errno);
			break;
		}
		int flags = fcntl(m_fdListen, F_GETFL, 0);
		if (fcntl(m_fdListen, F_SETFL, flags | O_NONBLOCK) < 0)
		{
			LOG(LOG_ERR, "ServerObject::open fcntl errno=%d\n", errno);
			break;
		}

		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(MY_PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(m_fdListen, (const sockaddr*)&addr, sizeof(addr)) < 0)
		{
			LOG(LOG_ERR, "ServerObject::open bind errno=%d\n", errno);
			break;
		}
		if (-1 == listen(m_fdListen, BACKLOG))
		{
			LOG(LOG_ERR, "ServerObject::open listen errno=%d\n", errno);
			break;
		}
		auto accpentFun = [this]() 
			{
				while (onAccept());
			};
		EPollObject &epollObject = Single<EPollObject>::Instance();
		//epollObject.updateFun(m_fdListen, ET_READ, accpentFun);

		bRes = true;
	} while (false);
	return bRes;
}

bool ServerObject::close()
{
	return false;
}

void ServerObject::eventLoop()
{
	while (true)
	{
		sleep(1);
	}
}

bool ServerObject::onAccept()
{
	bool bRet = false;

	do
	{
		sockaddr_in addr = { 0 };
		socklen_t addrlen = sizeof(addr);
		int acpSock = -1;
		if ((acpSock = accept(m_fdListen, reinterpret_cast<sockaddr*>(&addr), &addrlen)) < 0)
		{
			LOG(LOG_ERR, "ServerObject::onAccept accept errno=%d\n", errno);
			break;
		}
		int flags = fcntl(m_fdListen, F_GETFL, 0);
		if (fcntl(acpSock, F_SETFL, flags | O_NONBLOCK) < 0)
		{
			LOG(LOG_ERR, "ServerObject::onAccept fcntl errno=%d\n", errno);
			break;
		}

	} while (false);
	return bRet;
}
