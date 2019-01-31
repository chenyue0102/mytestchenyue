#include <cstdio>
#include <syslog.h>
#include <signal.h>
#include "daemon.h"
#include "ServerObject.h"
#include "Single.h"
#include "EPollObject.h"
#include "UserObjectManager.h"
#include "TaskPool.h"

int main()
{
	//testepoll::init_daemon("test");
	signal(SIGPIPE, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	openlog("test", LOG_CONS | LOG_PID, LOG_DAEMON);

	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.Open(0);

	UserObjectManager &userObjectManager = Single<UserObjectManager>::Instance();

	EPollObject &epollObject = Single<EPollObject>::Instance();
	epollObject.init();

	ServerObject &serverObject = Single<ServerObject>::Instance();
	serverObject.init(&userObjectManager);
	serverObject.eventLoop();
	serverObject.destory();

	epollObject.destory();
    return 0;
}