#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <list>
#include <condition_variable>

class CTaskPool
{
	enum TaskStatus
	{
		TaskStatusNone,
		TaskStatusBusy,
		TaskStatusFree,
	};
public:
	CTaskPool();
	~CTaskPool();
public:
	bool Open(unsigned int nPoolSize);
	bool Close();
	bool AddTask(const std::function<void()> &fun);
private:
	void TaskThread(unsigned int nCurIndex);
public:
	typedef std::list<std::function<void()>> TASK_ARRAY;
	std::mutex m_mutex;
	std::vector<std::thread> m_threads;
	std::vector<std::condition_variable> m_cvs;
	TASK_ARRAY m_globalFuns;//全局任务
	std::vector<TASK_ARRAY> m_threadFuns;//某个线程的任务
	std::vector<TaskStatus> m_taskStatus;
	volatile bool m_bExit;
	unsigned int m_nPoolSize;
};

