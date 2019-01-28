#pragma once
#include <mutex>
#include <thread>
#include <list>
#include <unordered_set>
#include <condition_variable>

typedef std::function<void()> TASK_JOB;
typedef std::size_t TASK_GROUPID;
class CTaskPool
{
	enum ThreadStatus
	{
		ThreadStatusNone,
		ThreadStatusBusy,
		ThreadStatusFree,
	};
	struct ThreadInfo
	{
		std::thread t;
		ThreadStatus s;
	};
	struct TaskInfo
	{
		TASK_JOB job;
		bool groupIdValid;
		TASK_GROUPID groupId;
	};
public:
	CTaskPool();
	~CTaskPool();
public:
	bool Open(unsigned int nPoolSize);
	bool Close();
	bool AddTask(const TASK_JOB &fun);
	bool AddOrderTask(const TASK_JOB &fun, TASK_GROUPID groupId);
private:
	bool InnerAddOrderTask(const TASK_JOB &fun, bool groupIdValid, TASK_GROUPID groupId);
	std::unique_ptr<TaskInfo> InnerGetTaskInfo();
	void TaskThread(ThreadInfo &threadInfo);
public:
	typedef std::list<std::unique_ptr<TaskInfo>> TASK_INFO_ARRAY;
	typedef std::list<std::unique_ptr<ThreadInfo>> THREAD_INFO_ARRAY;
	
	std::mutex m_mutex;
	std::condition_variable m_cv;
	THREAD_INFO_ARRAY m_threadInfos;
	TASK_INFO_ARRAY m_taskInfos;
	std::unordered_set<TASK_GROUPID> m_curGroupIds;
	volatile bool m_bExit;
	unsigned int m_nPoolSize;
};

