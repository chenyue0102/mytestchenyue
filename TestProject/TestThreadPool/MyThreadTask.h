#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "INotifyTask.h"


struct TaskInterruptedException;
class CMyThreadTask
{
public:
	enum EnumTaskStatus
	{
		EnumTaskStatusNone,
		EnumTaskStatusAppend,
		EnumTaskStatusDoing,
	};
public:
	CMyThreadTask();
	~CMyThreadTask();
public:
	void Open(INotifyTask *pNotifyTask);
	void Close();
public:
	bool DoTask(const std::function<void()> &Fun, long long llTaskID);
	void InterruptTask(bool bWaitFinished);
	bool IsTaskInterrupted()const;
private:
	void ThreadProc();
private:
	volatile bool m_bExit;					//退出线程
	volatile EnumTaskStatus m_TaskStatus;

	std::function<void()> m_Function;
	volatile long long m_llTaskID;

	volatile bool m_bInterrupted;			//中断当前的任务
	std::condition_variable m_cvFinished;
	
	std::thread m_Thread;
	mutable std::mutex m_mtx;
	std::condition_variable m_cv;
	INotifyTask *m_pNotifyTask;
};

