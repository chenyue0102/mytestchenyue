#include "MyThreadPool.h"
#include <assert.h>
#include <algorithm>


CMyThreadPool::CMyThreadPool()
	: m_mtx()
	, m_thread()
	, m_bExit(false)
	, m_cv()
	, m_llTaskID(0)
	, m_JobArray()
	, m_IdleThreadArray()
	, m_BusyThreadArray()
{
}

CMyThreadPool::~CMyThreadPool()
{
}

bool CMyThreadPool::Open()
{
	bool bRes = false;

	do 
	{
		std::lock_guard<std::mutex> lk(m_mtx);
		int nThreadCount = std::thread::hardware_concurrency();
		if (0 == nThreadCount)
		{
			nThreadCount = 1;
		}
		nThreadCount = 2;
		//nThreadCount *= 2;

		for (int nIndex = 0; nIndex < nThreadCount; nIndex++)
		{
			std::shared_ptr<CMyThreadTask> pMyThreadTask = std::make_shared<CMyThreadTask>();
			pMyThreadTask->Open(this);
			m_IdleThreadArray.push(pMyThreadTask);
		}
		m_thread = std::thread(&CMyThreadPool::ThreadProc, this);
		bRes = true;
	} while (false);
	return bRes;
}

bool CMyThreadPool::Close()
{
	bool bRes = false;

	do 
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		m_bExit = true;
		m_cv.notify_one();

		m_JobArray.clear();
		
		{
			while (!m_IdleThreadArray.empty())
			{
				std::shared_ptr<CMyThreadTask> pMyThreadTask = m_IdleThreadArray.top();
				if (pMyThreadTask)
				{
					pMyThreadTask->Close();
				}
				m_IdleThreadArray.pop();
			}
		}

		{
			std::map<long long, std::shared_ptr<CMyThreadTask>> TempBusyTaskArray = std::move(m_BusyThreadArray);

			lk.unlock();
			for (auto &OneBusyTask : TempBusyTaskArray)
			{
				OneBusyTask.second->InterruptTask(false);
				OneBusyTask.second->Close();
			}
		}

		m_thread.join();

		assert(0 == m_BusyThreadArray.size() && 0 == m_IdleThreadArray.size() && 0 == m_JobArray.size());

		bRes = true;
	} while (false);
	return bRes;
}

bool CMyThreadPool::DoTask(std::function<void()> Fun, long long &llTaskID)
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
		llTaskID = ++m_llTaskID;
		TaskJobInfo JobInfo = { llTaskID, Fun };
		m_JobArray.push_back(JobInfo);
		m_cv.notify_one();
		bRes = true;
	} while (false);
	return bRes;
}

bool CMyThreadPool::InterruptTask(long long llTaskID, bool bWaitFinished)
{
	bool bRes = false;

	do 
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		auto itor = m_BusyThreadArray.find(llTaskID);
		if (itor != m_BusyThreadArray.end())
		{
			itor->second->InterruptTask(bWaitFinished);
		}
		else
		{
			//查找待处理任务
			auto itorJob = std::find_if(m_JobArray.begin(), m_JobArray.end(),
				[llTaskID](const TaskJobInfo &JobInfo) {return JobInfo.llTaskID == llTaskID; });
			if (itorJob == m_JobArray.end())
			{
				assert(false);
				break;
			}
			m_JobArray.erase(itorJob);
		}
		bRes = true;
	} while (false);

	return bRes;
}

void CMyThreadPool::NotifyTaskCompleted(long long llTaskID, bool bInterrupted)
{
	std::lock_guard<std::mutex> lk(m_mtx);
	if (!m_bExit)
	{
		auto itor = m_BusyThreadArray.find(llTaskID);
		if (itor != m_BusyThreadArray.end())
		{
			m_IdleThreadArray.push(itor->second);
			m_BusyThreadArray.erase(itor);
			if (m_JobArray.size() > 0)
			{
				m_cv.notify_one();
			}
		}
		else
		{
			assert(false);
		}
	}
}

void CMyThreadPool::ThreadProc()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		m_cv.wait(lk, [this]() 
			{
				return m_bExit || (m_JobArray.size() > 0 && m_IdleThreadArray.size() > 0);
			});
		if (m_bExit)
		{
			assert(0 == m_JobArray.size());
			assert(0 == m_BusyThreadArray.size());
			break;
		}
		if (m_IdleThreadArray.size() > 0 && m_JobArray.size() > 0)
		{
			std::shared_ptr<CMyThreadTask> pMyThreadTask = m_IdleThreadArray.top();
			m_IdleThreadArray.pop();

			TaskJobInfo JobInfo = m_JobArray.front();
			m_JobArray.pop_front();

			if (pMyThreadTask && JobInfo.Fun)
			{
				bool bTask = pMyThreadTask->DoTask(JobInfo.Fun, JobInfo.llTaskID);
				assert(bTask);
				m_BusyThreadArray.insert(std::make_pair(JobInfo.llTaskID, pMyThreadTask));
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}
}
