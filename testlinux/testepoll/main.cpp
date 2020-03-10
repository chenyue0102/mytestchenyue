#include <cstdio>
#include <syslog.h>
#include <signal.h>
#include <atomic>
#include <sys/types.h>
#include "daemon.h"
#include "ServerObject.h"
#include "Single.h"
#include "EPollObject.h"
#include "UserObjectManager.h"
#include "TaskPool.h"
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#define gettidv1() syscall(__NR_gettid)
#define gettidv2() syscall(SYS_gettid)


struct TestTask 
{
	bool isgroup;
	int groupid;
	int taskId;
	int  threadId;
	int index;
};
std::atomic<int> g_index;
void printTask(TestTask& testTask)
{
	testTask.threadId = gettidv1();
	testTask.index = g_index++;
	std::this_thread::sleep_for(std::chrono::milliseconds(random()%10));
	
}
void testTaskPool()
{
	CTaskPool taskPool;
	taskPool.Open(2);
	TestTask tasks[] =
	{
	{true, 0, 0},
	{true, 0, 1},
	{false, 0, 2},
	{false, 0, 3},
	{false, 0, 4},
	{true, 0, 5},
	{true, 0, 6},
	{true, 1, 7},
	{true, 1, 8},
	{true, 2, 9},
	{true, 2, 10},
	};
	std::string text1, text2;

	for (int i = 0; i < sizeof(tasks) / sizeof(tasks[0]); i++)
	{
		auto& t = tasks[i];
		auto fun = [&t]() {printTask(t); };
		if (!t.isgroup)
		{
			taskPool.AddTask(fun);
		}
		else
		{
			taskPool.AddOrderTask(fun, t.groupid);
		}
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));
	for (int i = 0; i < sizeof(tasks) / sizeof(tasks[0]); i++)
	{
		printf("taskid=%d threadid=%d index=%d\n", tasks[i].taskId, tasks[i].threadId, tasks[i].index);
	}
	taskPool.Close();
}

int main()
{
	//testepoll::init_daemon("test");
	testTaskPool();
	return 0;
	signal(SIGPIPE, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	openlog("test", LOG_CONS | LOG_PID, LOG_DAEMON);

	CTaskPool &taskPool = Single<CTaskPool>::Instance();
	taskPool.Open(0);

	UserObjectManager &userObjectManager = Single<UserObjectManager>::Instance();
	userObjectManager.init();

	EPollObject &epollObject = Single<EPollObject>::Instance();
	epollObject.init();

	ServerObject &serverObject = Single<ServerObject>::Instance();
	serverObject.setPort(5618);
	serverObject.setCallback(&userObjectManager);
	serverObject.init();
	serverObject.destory();

	epollObject.destroy();
    return 0;
}