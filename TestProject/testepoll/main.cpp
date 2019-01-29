#include <cstdio>
#include <syslog.h>
#include "daemon.h"
#include "ServerObject.h"
#include "Single.h"
#include "EPollObject.h"

int main()
{
	//testepoll::init_daemon("test");
	openlog("test", LOG_CONS | LOG_PID, LOG_DAEMON);

	EPollObject &epollObject = Single<EPollObject>::Instance();
	epollObject.open();

	ServerObject &serverObject = Single<ServerObject>::Instance();
	serverObject.open();
	serverObject.eventLoop();
	serverObject.close();
    return 0;
}