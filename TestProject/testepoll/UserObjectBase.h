#ifndef _TESTUSEROBJECT_H_
#define _TESTUSEROBJECT_H_
#include <mutex>
#include <arpa/inet.h>//sockaddr_in

struct sockaddr_in;
class UserObjectBase
{
public:
	UserObjectBase();
	virtual ~UserObjectBase();
public:
	void setSockInfo(int fd, const sockaddr_in &addr);
	void notifyRecv(int fd, const char * pBuffer, unsigned int recvLen);
private:
	std::mutex m_mutex;
	int m_fd;
	sockaddr_in m_addr;
	std::string m_recvBuffer;
};

#endif