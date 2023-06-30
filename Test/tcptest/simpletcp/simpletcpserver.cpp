#include "simpletcpserver.h"
#include <assert.h>
#include <string.h>
#include "simplemutex.h"
#include "simplethread.h"
#include "simpletcpclient.h"

#define SELECT_TIMEOUT_MS 100L
#define AUTO_LOCKER \
	SimpleMutexLocker locker(mData->mutex)

struct SimpleTcpServer::SimpleTcpServerData
{
	SimpleMutex mutex;
	SimpleThread *thread;
	SimpleTcpServer::ICallback *callback;
	sockaddr_in addr;
	bool exit;


	SimpleTcpServerData()
		: mutex()
		, thread(NULL)
		, callback(NULL)
		, addr()
		, exit(false)
	{

	}
};
SimpleTcpServer::SimpleTcpServer()
	: mData(new SimpleTcpServerData())
{
	mData->addr.sin_family = AF_INET;
#ifdef WIN32
	mData->addr.sin_addr.S_un.S_addr = INADDR_ANY;
#else
    mData->addr.sin_addr.s_addr = INADDR_ANY;
#endif
}

SimpleTcpServer::~SimpleTcpServer()
{
	delete mData;
	mData = NULL;
}

void SimpleTcpServer::setCallback(ICallback * callback)
{
	AUTO_LOCKER;
	mData->callback = callback;
}

void SimpleTcpServer::setPort(uint16_t port)
{
	AUTO_LOCKER;
	mData->addr.sin_port = htons(port);
}

void SimpleTcpServer::setAddress(const sockaddr_in & addr)
{
	AUTO_LOCKER;
	mData->addr = addr;
}

void SimpleTcpServer::startServer()
{
	stopServer();
	AUTO_LOCKER;
	mData->exit = false;
	mData->thread = new SimpleThread(&SimpleTcpServer::threadProc, this);
}

void SimpleTcpServer::stopServer()
{
	SimpleThread *thread = NULL;
	{
		AUTO_LOCKER;
		mData->exit = true;
		thread = mData->thread;
		mData->thread = NULL;
	}
	if (NULL != thread) {
		thread->join();
		delete thread;
	}
}

void* SimpleTcpServer::threadProc(void * arg)
{
	SimpleTcpServer *This = reinterpret_cast<SimpleTcpServer*>(arg);
	This->innerThreadProc();
    return NULL;
}

void SimpleTcpServer::innerThreadProc()
{
	SOCKET sListen = INVALID_SOCKET;			//监听socket
    sockaddr_in addr;
	fd_set fd;
    timeval timeout = {0, 0};
	ICallback *callback = NULL;

    memset(&addr, 0, sizeof(addr));
	{
		AUTO_LOCKER;
		addr = mData->addr;
		callback = mData->callback;
	}
	if (NULL == callback) {
		assert(false);
		return;
	}

	do {
		if ((sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			assert(false);
			break;
		}
		if (bind(sListen, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
			assert(false);
			break;
		}
		if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
			assert(false);
			break;
		}
		int rv = 0;
		for (;;) {
			timeout.tv_sec = 0;
			timeout.tv_usec = SELECT_TIMEOUT_MS * 1000 ;	//100毫秒
			FD_ZERO(&fd);
			FD_SET(sListen, &fd);
			rv = select(sListen + 1, &fd, NULL, NULL, &timeout);
			if (rv == SOCKET_ERROR) {
				assert(false);
				break;
			}
			else if (rv == 0) {
				//timeout
			}
			else {
				sockaddr_in addrAccept = { 0 };
                socklen_t addrLen = sizeof(addrAccept);
				SOCKET sAccept = accept(sListen, reinterpret_cast<sockaddr*>(&addrAccept), &addrLen);
				if (INVALID_SOCKET == sAccept) {
					assert(false);
					break;
				}
				if (!callback->onAcceptTcpClient(sAccept, addrAccept)) {
					closesocket(sAccept);
					assert(false);
				}
			}
			{
				AUTO_LOCKER;
				if (mData->exit) {
					break;
				}
			}
		}
	} while (false);
	if (INVALID_SOCKET != sListen) {
		closesocket(sListen);
	}
}
