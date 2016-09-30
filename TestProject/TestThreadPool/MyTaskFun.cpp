#include "MyTaskFun.h"
#include "MyThreadTask.h"
#include <assert.h>

thread_local CMyThreadTask *g_ThisThreadTask = nullptr;
namespace MyTaskFun
{
TaskInterruptedException GetTaskInterruptedException()
{
	return TaskInterruptedException();
}

bool IsTaskInterrupted()
{
	auto pThreadTask = GetThisThreadTask();
	if (nullptr != pThreadTask)
	{
		return pThreadTask->IsTaskInterrupted();
	}
	else
	{
		assert(false);
		return false;
	}
}

CMyThreadTask* GetThisThreadTask()
{
	return g_ThisThreadTask;
}

void SetThisThreadTask(CMyThreadTask *pThreadTask)
{
	g_ThisThreadTask = pThreadTask;
}

}
