#include <cstdio>
#include "ServerObject.h"
#include "daemon.h"
#include "ServerObject.h"


int main()
{
	testepoll::init_daemon("test");

	ServerObject serverObject;
	serverObject.open();
	serverObject.eventLoop();
	serverObject.close();
    return 0;
}