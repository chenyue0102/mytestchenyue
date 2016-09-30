#pragma once

class CMyThreadTask;
namespace MyTaskFun
{
struct TaskInterruptedException
{
	int nReserved;
};
TaskInterruptedException GetTaskInterruptedException();
bool IsTaskInterrupted();
CMyThreadTask* GetThisThreadTask();
void SetThisThreadTask(CMyThreadTask *pThreadTask);
};

