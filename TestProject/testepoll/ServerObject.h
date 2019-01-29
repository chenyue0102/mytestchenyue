#ifndef _SERVEROBJECT_H_
#define _SERVEROBJECT_H_
#include <mutex>

class ServerObject
{
public:
	ServerObject();
	~ServerObject();
public:
	bool open();
	bool close();
	void eventLoop();
private:
	bool onAccept();
private:
	int m_fdListen;
	std::mutex m_mutex;
};

#endif
