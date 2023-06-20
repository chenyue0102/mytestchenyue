#include "simpletcpclient.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "simplemutex.h"
#include "simplethread.h"
#include "simpleringqueue.h"

#define RING_QUEUE_SIZE (256 * 1024)
//select操作超时时间
#define SELECT_TIMEOUT_MS 100
//连接操作超时时间
#define CONNECT_TIMEOUT_MS (2 * 1000)

#define AUTO_LOCKER \
	SimpleMutexLocker locker(mData->mutex)

struct SimpleTcpClient::SimpleTcpClientData
{
	SimpleMutex mutex;
	SimpleThread *thread;
	SimpleRingQueue ringQueue;
	SOCKET s;
	sockaddr_in addr;
	ITcpCallback *callback;
	bool exit;
	bool needConnect;

	SimpleTcpClientData()
		: mutex()
		, thread(NULL)
		, ringQueue(RING_QUEUE_SIZE)
		, s(INVALID_SOCKET)
		, addr()
		, callback(NULL)
		, exit(false)
		, needConnect(false)
	{

	}
};

SimpleTcpClient::SimpleTcpClient()
	: mData(new SimpleTcpClientData())
{
	mData->addr.sin_family = AF_INET;
}

SimpleTcpClient::~SimpleTcpClient()
{
	delete mData;
}

void SimpleTcpClient::setCallback(ITcpCallback * callback)
{
	AUTO_LOCKER;
	mData->callback = callback;
}

void SimpleTcpClient::connectServer(const char * ip, uint16_t port)
{
	{
		AUTO_LOCKER;
        inet_aton(ip, &mData->addr.sin_addr);
		mData->addr.sin_port = htons(port);
		mData->needConnect = true;
	}
	startThread();
}

void SimpleTcpClient::setSocket(SOCKET s, const sockaddr_in & addr)
{
	{
		AUTO_LOCKER;
		assert(INVALID_SOCKET == mData->s);
		mData->s = s;
		mData->addr = addr;
		mData->needConnect = false;
	}
	startThread();
}

void SimpleTcpClient::closeSocket()
{
	stopThread();
	AUTO_LOCKER;
	if (INVALID_SOCKET != mData->s) {
		closesocket(mData->s);
		mData->s = INVALID_SOCKET;
	}
}

uint32_t SimpleTcpClient::sendData(const void * data, uint32_t size)
{
	AUTO_LOCKER;
	return mData->ringQueue.put(data, size);
}

void SimpleTcpClient::startThread()
{
	stopThread();
	AUTO_LOCKER;
	mData->exit = false;
	mData->thread = new SimpleThread(&SimpleTcpClient::threadProc, this);
}

void SimpleTcpClient::stopThread()
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

void* SimpleTcpClient::threadProc(void * arg)
{
	SimpleTcpClient *This = reinterpret_cast<SimpleTcpClient*>(arg);
	This->innerThreadProc();
    return NULL;
}

void SimpleTcpClient::innerThreadProc()
{
	SOCKET s = INVALID_SOCKET;
	fd_set fdRead, fdWrite;
    timeval timeout = { 0, 0 };
	ITcpCallback *callback = NULL;
	bool needConnect = false;
	sockaddr_in addr;
	{
		AUTO_LOCKER;
		addr = mData->addr;
		s = mData->s;
		mData->s = INVALID_SOCKET;
		callback = mData->callback;
		needConnect = mData->needConnect;
	}

	if (NULL == callback) {
		assert(false);
		return;
	}
	
	int rv = 0;
	uint32_t sendDataSize = 0;
    const int BUFFER_SIZE = 128;
    char buffer[BUFFER_SIZE];

	if (needConnect) {
		assert(INVALID_SOCKET == s);
		if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			goto CLOSE_SOCKET;
		}
		//将socket设置为非阻塞
        if (!setSocketBlock(s, false)){
            assert(false);
            goto CLOSE_SOCKET;
        }
		if (::connect(s, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
			if (getSocketError() != ERR_BLOCK) {
				assert(false);
				goto CLOSE_SOCKET;
			}
		}
		//每次select超时时间为100毫秒
		int selectCount = CONNECT_TIMEOUT_MS / 100;
		if (selectCount == 0) {
			selectCount = 1;
		}
		timeout.tv_sec = 0;
		timeout.tv_usec = 100 * 1000;
		bool connectSuccess = false;
		for (int i = 0; i < selectCount; i++) {
			FD_ZERO(&fdWrite);
			FD_SET(s, &fdWrite);
			rv = select(s + 1, NULL, &fdWrite, NULL, &timeout);
			if (rv == SOCKET_ERROR) {
				assert(false);
				goto CLOSE_SOCKET;
			}
			else if (rv == 0) {
				//timeout
			}
			else {
				//connect成功，设置为阻塞socket
				if (FD_ISSET(s, &fdWrite)) {
                    sockaddr_in remoteAddr;
                    socklen_t remoteAddrLen = sizeof(remoteAddr);
                    memset(&remoteAddr, 0, sizeof(remoteAddr));
					if (-1 == getpeername(s, (sockaddr*)&remoteAddr, &remoteAddrLen)) {
						assert(false);
					}
				}
                if (!setSocketBlock(s, true)){
                    assert(false);
                    goto CLOSE_SOCKET;
                }
				connectSuccess = true;
				break;
			}
		}
		if (!connectSuccess) {
			callback->onConnect(false);
			goto CLOSE_SOCKET;
		}
		else {
			callback->onConnect(true);
		}
	}
	timeout.tv_sec = 0;
	timeout.tv_usec = SELECT_TIMEOUT_MS * 1000;
	

	for (;;) {
		FD_ZERO(&fdRead);
		FD_SET(s, &fdRead);
		{
			AUTO_LOCKER;
			sendDataSize = mData->ringQueue.getDataSize();
		}
		fd_set *pfdWrite = 0 == sendDataSize ? NULL : &fdWrite;
		if (NULL != pfdWrite) {
			FD_ZERO(pfdWrite);
			FD_SET(s, pfdWrite);
		}
		rv = select(s + 1, &fdRead, pfdWrite, NULL, &timeout);

		if (SOCKET_ERROR == rv) {
			assert(false);
			break;
		}
		else if (0 == rv) {
			//timeout
		}
		else {
			if (FD_ISSET(s, &fdRead)) {
				int rSize = recv(s, buffer, BUFFER_SIZE, 0);
				if (0 == rSize) {
					callback->onClose();
					break;
				}
				else {
					callback->onRecv(buffer, rSize);
				}
			}
			else if (NULL != pfdWrite && FD_ISSET(s, pfdWrite)) {
				uint32_t wSize = 0;
				{
					AUTO_LOCKER;
					wSize = mData->ringQueue.get(buffer, BUFFER_SIZE);
				}
                if (::send(s, buffer, wSize, 0) != wSize) {
					assert(false);
				}
			}
		}
		AUTO_LOCKER;
		if (mData->exit) {
			break;
		}
	}

CLOSE_SOCKET:
	if (INVALID_SOCKET != s) {
		closesocket(s);
	}
}
