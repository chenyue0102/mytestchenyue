#pragma once
#include <functional>
#include <mutex>
#include <stack>
#include <list>
#include <map>
#include "INotifyTask.h"
#include "MyThreadTask.h"

class CMyThreadTask;
class CMyThreadPool : public INotifyTask
{
	struct TaskJobInfo
	{
		long long llTaskID;
		std::function<void()> Fun;
	};
public:
	CMyThreadPool();
	~CMyThreadPool();
public:
	bool Open();
	bool Close();
public:
	bool DoTask(const std::function<void()> &Fun, long long &llTaskID);
	bool InterruptTask(long long llTaskID, bool bWaitFinished);
protected:
	virtual void NotifyTaskCompleted(long long llTaskID, bool bInterrupted)override;
private:
	void ThreadProc();
private:
	std::mutex m_mtx;
	std::thread m_thread;
	volatile bool m_bExit;
	std::condition_variable m_cv;

	volatile long long m_llTaskID;
	std::list<TaskJobInfo> m_JobArray;

	std::stack<std::shared_ptr<CMyThreadTask>>	m_IdleThreadArray;
	std::map<long long, std::shared_ptr<CMyThreadTask>> m_BusyThreadArray;


};

