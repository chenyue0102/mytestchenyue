#include <assert.h>
#include "TaskPool.h"


TaskPool::TaskPool()
	: m_mutex()
	, m_cv()
	, m_threadInfo()
	, m_taskJob()
	, m_bExit(false)
{
}


TaskPool::~TaskPool()
{
}

bool TaskPool::open(unsigned int nPoolSize)
{
	bool bRes = false;

	do 
	{
		close();
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = false;
		if (0 == nPoolSize)
		{
			nPoolSize = std::thread::hardware_concurrency() * 2 + 1;
		}
		for (unsigned int nIndex = 0; nIndex < nPoolSize; nIndex++)
		{
			std::unique_ptr<ThreadInfo> pThreadInfo(new ThreadInfo);
			pThreadInfo->t = std::thread(&TaskPool::taskThread, this, std::ref(*pThreadInfo));
			m_threadInfo.push_back(std::move(pThreadInfo));
		}

		bRes = true;
	} while (false);

	if (!bRes)
	{
		close();
	}
	return bRes;
}

bool TaskPool::close()
{
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = true;
		m_cv.notify_all();
	}
	for (auto &curThreadInfo : m_threadInfo)
	{
		if (curThreadInfo->t.joinable())
		{
#ifdef DEBUG
			if (std::this_thread::get_id() == curThreadInfo->t.get_id())
			{
				assert(false);
			}
#endif
			curThreadInfo->t.join();
		}
	}
	m_threadInfo.clear();
	//m_cv
	m_taskJob.clear();
	return true;
}

bool TaskPool::addTask(const TASK_JOB &fun)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	m_taskJob.push_back(fun);
	m_cv.notify_one();
	return true;
}

void TaskPool::taskThread(ThreadInfo &threadInfo)
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, 
			[&]()->bool
		{
			if (m_bExit
				|| !m_taskJob.empty())
			{
				return true;
			}
			else
			{
				return false;
			}
		});
		if (m_bExit)
		{
			break;
		}

		TASK_JOB taskJob = m_taskJob.front();
		m_taskJob.pop_front();
	DoTask:
		lk.unlock();

		if (taskJob)
		{
			try
			{
				taskJob();
			}
			catch (...)
			{
				assert(false);
			}
		}

		lk.lock();
		if (m_bExit)
		{
			break;
		}
		else if (!m_taskJob.empty())
		{
			taskJob = m_taskJob.front();
			m_taskJob.pop_front();
			goto DoTask;
		}
	}
}

