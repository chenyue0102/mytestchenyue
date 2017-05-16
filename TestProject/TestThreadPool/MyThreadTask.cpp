#include "MyThreadTask.h"
#include <assert.h>
#include "MyTaskFun.h"


CMyThreadTask::CMyThreadTask()
	: m_bExit(false)
	, m_TaskStatus(EnumTaskStatusNone)
	, m_Function(nullptr)
	, m_llTaskID(0)
	, m_bInterrupted(false)
	, m_cvFinished()
	, m_Thread()
	, m_mtx()
	, m_cv()
	, m_pNotifyTask(nullptr)
{
	
}

CMyThreadTask::~CMyThreadTask()
{
}

void CMyThreadTask::Open(INotifyTask *pNotifyTask)
{
	m_pNotifyTask = pNotifyTask;
	m_Thread = std::thread(&CMyThreadTask::ThreadProc, this);
}

void CMyThreadTask::Close()
{
	if (m_Thread.joinable())
	{
		{
			std::lock_guard<std::mutex> lk(m_mtx);
			m_bExit = true;
			switch (m_TaskStatus)
			{
			case EnumTaskStatusAppend:
				m_Function = nullptr;
				break;
			case EnumTaskStatusDoing:
				m_bInterrupted = true;
				break;
			case EnumTaskStatusNone:
			default:
				break;
			}
			m_cv.notify_one();
		}
		m_Thread.join();
	}
}

bool CMyThreadTask::DoTask(const std::function<void()> &Fun, long long llTaskID)
{
	bool bRes = false;
	do 
	{
		if (!Fun)
		{
			assert(false);
			break;
		}
		std::lock_guard<std::mutex> lk(m_mtx);
		if (m_bExit)
		{
			assert(false);
			break;
		}
		if (EnumTaskStatusNone != m_TaskStatus)
		{
			assert(false);
			break;
		}
		m_bInterrupted = false;
		m_TaskStatus = EnumTaskStatusAppend;
		m_Function = Fun;
		m_llTaskID = llTaskID;
		m_cv.notify_one();
		bRes = true;
	} while (false);
	return bRes;
}

void CMyThreadTask::InterruptTask(bool bWaitFinished)
{
	std::unique_lock<std::mutex> lk(m_mtx);
	switch (m_TaskStatus)
	{
		case EnumTaskStatusAppend:
		{
			assert(m_Function);
			m_Function = nullptr;
			m_TaskStatus = EnumTaskStatusNone;
		}
		break;
		case EnumTaskStatusDoing:
		{
			assert(m_Function);
			m_bInterrupted = true;
			if (bWaitFinished)
			{
				m_cvFinished.wait(lk,
					[this]()
				{
					return EnumTaskStatusNone == m_TaskStatus;
				});
			}
		}
		break;
		case EnumTaskStatusNone:
		default:
			break;
	}
}

bool CMyThreadTask::IsTaskInterrupted()const
{
	std::lock_guard<std::mutex> lk(m_mtx);
	return m_bInterrupted;
}

void CMyThreadTask::ThreadProc()
{
	MyTaskFun::SetThisThreadTask(this);
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		m_cv.wait(lk, 
			[this]() ->bool
			{
				return (m_bExit || m_Function);
			});
		if (m_bExit)
		{
			assert(!m_Function);
			break;
		}
		if (m_Function)
		{
			m_TaskStatus = EnumTaskStatusDoing;
			std::function<void()> Fun = m_Function;
			long long llTaskID = m_llTaskID;
			lk.unlock();

			bool bInterrupted = false;
			try
			{
				Fun();
			}
			catch (MyTaskFun::TaskInterruptedException &)
			{
				//catch TaskInterruptedException
				bInterrupted = true;
			}
			
			{
				std::lock_guard<std::mutex> lkTemp(m_mtx);
				m_Function = nullptr;
				m_llTaskID = 0;
				m_TaskStatus = EnumTaskStatusNone;
			}
			m_cvFinished.notify_one();
			if (nullptr != m_pNotifyTask)
			{
				m_pNotifyTask->NotifyTaskCompleted(llTaskID, bInterrupted);
			}
		}
	}
	MyTaskFun::SetThisThreadTask(nullptr);
}
