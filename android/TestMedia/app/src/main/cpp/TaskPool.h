/*
执行任务
*/
#pragma once
#include <mutex>
#include <thread>
#include <list>
#include <vector>
#include <memory>
#include <unordered_map>
#include <condition_variable>
#include <functional>

typedef std::function<void()> TASK_JOB;
class CTaskPool
{
	typedef std::list<TASK_JOB> TASK_JOB_ARRAY;
	struct ThreadInfo
	{
		std::thread t;
		ThreadInfo()
			: t()
		{}
	};
	typedef std::vector<std::unique_ptr<ThreadInfo>> THREAD_INFO_ARRAY;
public:
	CTaskPool();
	~CTaskPool();
public:
	bool Open(unsigned int nPoolSize);
	bool Close();
	bool AddTask(const TASK_JOB &fun);
private:
	void TaskThread(ThreadInfo &threadInfo);
public:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	THREAD_INFO_ARRAY m_threadInfo;				//线程信息
	TASK_JOB_ARRAY m_taskJob;					//公共任务信息
	volatile bool m_bExit;						//退出标记
};

