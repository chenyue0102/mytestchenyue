#pragma once
#include <functional>
#include <mutex>

class CMyTask
{
public:
	enum EnumTaskStatus
	{
		EnumTaskStatusNone,
		EnumTaskStatusAppend,
		EnumTaskStatusDoing,
	};
public:
	CMyTask();
	~CMyTask();
public:
	void DoTask();
	void InterruptTask();
protected:
	void SetTask(std::function<void()> Fun);
	void CleanTask();
private:
	void NotifyCompleteTask();
public:
	static bool IsThisThreadTaskInterrupted()
	{
		auto pThisThreadTask = CMyTask::GetThisThreadTask();
		if (nullptr != pThisThreadTask)
		{
			return pThisThreadTask->InnerIsTaskInterrupted();
		}
		else
		{
			return false;
		}
	}
	static CMyTask* GetThisThreadTask()
	{
		return CMyTask::m_pThisThreadTask;
	}
	static void SetThisThreadTask(CMyTask *pThisThreadTask)
	{
		CMyTask::m_pThisThreadTask = pThisThreadTask;
	}
private:
	bool InnerIsTaskInterrupted();
private:
	volatile bool m_bInterrupted;			//中断当前的任务
	volatile EnumTaskStatus m_TaskStatus;
	std::function<void()> m_Fun;
	std::mutex		m_mtx;

	static thread_local CMyTask *m_pThisThreadTask;
};
