#include "stdafx.h"
#include "MyTask.h"
#include <assert.h>
#include "MyTaskFun.h"

thread_local CMyTask *CMyTask::m_pThisThreadTask = nullptr;
CMyTask::CMyTask()
	: m_bInterrupted(false)
	, m_TaskStatus(EnumTaskStatusNone)
	, m_Fun()
	, m_mtx()
{
}


CMyTask::~CMyTask()
{
}

void CMyTask::DoTask()
{
	CMyTask::SetThisThreadTask(this);
	bool bInterrupted = false;
	try
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		if (!m_bInterrupted)
		{
			std::function<void()> Fun = m_Fun;
			m_TaskStatus = EnumTaskStatusDoing;

			lk.unlock();

			if (Fun)
			{
				Fun();
			}
		}
		else
		{
			bInterrupted = true;
		}
	}
	catch (MyTaskFun::TaskInterruptedException &)
	{
		//catch TaskInterruptedException
		bInterrupted = true;
		printf("catch TaskInterruptedException\n");
	}
	CMyTask::SetThisThreadTask(nullptr);
	
	NotifyCompleteTask();
}

void CMyTask::SetTask(std::function<void()> Fun)
{
	assert(Fun);
	std::unique_lock<std::mutex> lk(m_mtx);
	assert(!m_Fun);
	m_Fun = Fun;
	m_TaskStatus = EnumTaskStatusAppend;
}

void CMyTask::CleanTask()
{
	std::unique_lock<std::mutex> lk(m_mtx);
	m_Fun = nullptr;
	m_TaskStatus = EnumTaskStatusNone;
	m_bInterrupted = false;
}

void CMyTask::InterruptTask()
{
	std::unique_lock<std::mutex> lk(m_mtx);
	m_bInterrupted = true;
}

void CMyTask::NotifyCompleteTask()
{

}

bool CMyTask::InnerIsTaskInterrupted()
{
	std::lock_guard<std::mutex> lk(m_mtx);
	return m_bInterrupted;
}

