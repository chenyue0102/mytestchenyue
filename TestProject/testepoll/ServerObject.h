#ifndef _SERVEROBJECT_H_
#define _SERVEROBJECT_H_

class ServerObject
{
public:
	ServerObject();
	~ServerObject();
public:
	bool open();
	bool close();
	void eventLoop();
};

#endif
