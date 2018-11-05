#include "stdafx.h"
#include "TaskPool.h"


CTaskPool::CTaskPool()
	: m_mutex()
	, m_bExit(false)
	, m_nPoolSize(0)
{
}


CTaskPool::~CTaskPool()
{
}

bool CTaskPool::Open(unsigned int nPoolSize)
{
	bool bRes = false;

	do 
	{
		m_bExit = false;
		m_nPoolSize = nPoolSize;
		m_taskStatus.resize(nPoolSize, TaskStatusNone);
		m_cvs.swap(std::vector<std::condition_variable>(nPoolSize));
		m_threads.swap(std::vector<std::thread>(nPoolSize));

		std::lock_guard<std::mutex> lk(m_mutex);
		for (unsigned int nIndex = 0; nIndex < nPoolSize; nIndex++)
		{
			m_threads[nIndex] = std::thread(&CTaskPool::TaskThread, this, nIndex);
		}

		bRes = true;
	} while (false);

	if (!bRes)
	{
		Close();
	}
	return bRes;
}

bool CTaskPool::Close()
{
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = true;
		for (auto &oneCv : m_cvs)
		{
			oneCv.notify_one();
		}
	}
	for (auto &oneThread : m_threads)
	{
		if (oneThread.joinable())
		{
			oneThread.join();
		}
	}
	m_threads.clear();
	m_cvs.clear();
	m_globalFuns.clear();
	m_nPoolSize = 0;
	return true;
}

bool CTaskPool::AddTask(const std::function<void()> &fun)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	m_globalFuns.push_back(fun);
	for (unsigned int nIndex = 0; nIndex < m_nPoolSize; nIndex++)
	{
		if (TaskStatusFree == m_taskStatus[nIndex])
		{
			m_cvs[nIndex].notify_one();
			break;
		}
	}
	return true;
}

void CTaskPool::TaskThread(unsigned int nCurIndex)
{
	auto &taskStatus = m_taskStatus[nCurIndex];
	auto &cv = m_cvs[nCurIndex];
	auto &globalFuns = m_globalFuns;

	TASK_ARRAY curThreadFuns;
	std::function<void()> curGlobalFun;

	{
		std::lock_guard<std::mutex> lk(m_mutex);
		taskStatus = TaskStatusFree;
	}
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		cv.wait(lk, 
			[&]()->bool
		{
			if (m_bExit
				|| !globalFuns.empty())
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
			taskStatus = TaskStatusNone;
			break;
		}

	DoTask:
		taskStatus = TaskStatusBusy;
		if (!globalFuns.empty())
		{
			//全局任务，只取1个，给其他线程一些机会
			curGlobalFun = std::move(globalFuns.front());
			globalFuns.pop_front();
		}
		lk.unlock();

		if (curGlobalFun)
		{
			curGlobalFun();
			curGlobalFun = nullptr;
		}

		//再次检测下任务
		lk.lock();
		if (globalFuns.empty())
		{
			taskStatus = TaskStatusFree;
			continue;
		}
		else
		{
			goto DoTask;
		}
	}
}
