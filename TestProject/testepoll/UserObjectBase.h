#ifndef _TESTUSEROBJECT_H_
#define _TESTUSEROBJECT_H_

struct sockaddr_in;
class UserObjectBase
{
public:
	UserObjectBase();
	virtual ~UserObjectBase();
public:
	void setSockInfo(int fd, const sockaddr_in &addr);
};

#endif