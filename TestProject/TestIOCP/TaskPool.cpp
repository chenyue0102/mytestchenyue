#include "stdafx.h"
#include <assert.h>
#include "TaskPool.h"


CTaskPool::CTaskPool()
	: m_mutex()
	, m_cv()
	, m_threadInfos()
	, m_taskInfos()
	, m_curGroupIds()
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
		
		bool bError = false;
		std::lock_guard<std::mutex> lk(m_mutex);
		for (unsigned int nIndex = 0; nIndex < nPoolSize; nIndex++)
		{
			std::unique_ptr<ThreadInfo> pThreadInfo = std::make_unique<ThreadInfo>();
			if (!pThreadInfo)
			{
				bError = true;
				assert(false);
				break;
			}
			pThreadInfo->s = ThreadStatusNone;
			pThreadInfo->t.swap(std::thread(&CTaskPool::TaskThread, this, std::ref(*pThreadInfo)));
			m_threadInfos.push_back(std::move(pThreadInfo));
		}
		if (bError)
		{
			break;
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
		m_cv.notify_all();
	}
	for (auto &pThreadInfo : m_threadInfos)
	{
		if (pThreadInfo
			&& pThreadInfo->t.joinable())
		{
			pThreadInfo->t.join();
		}
	}
	m_threadInfos.clear();
	//m_cv
	m_curGroupIds.clear();
	m_taskInfos.clear();
	m_nPoolSize = 0;
	return true;
}

bool CTaskPool::AddTask(const TASK_JOB &fun)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return InnerAddOrderTask(fun, false, 0);
}

bool CTaskPool::AddOrderTask(const TASK_JOB &fun, TASK_GROUPID groupId)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return InnerAddOrderTask(fun, true, groupId);
}

bool CTaskPool::InnerAddOrderTask(const TASK_JOB & job, bool groupIdValid, TASK_GROUPID groupId)
{
	bool bRes = false;

	do
	{
		std::unique_ptr<TaskInfo> pTaskInfo = std::make_unique<TaskInfo>();
		if (!pTaskInfo)
		{
			assert(false);
			break;
		}
		pTaskInfo->job = job;
		pTaskInfo->groupIdValid = groupIdValid;
		pTaskInfo->groupId = groupId;
		m_taskInfos.push_back(std::move(pTaskInfo));
		m_cv.notify_one();

		bRes = true;
	} while (false);

	return bRes;
}

std::unique_ptr<CTaskPool::TaskInfo> CTaskPool::InnerGetTaskInfo()
{
	std::unique_ptr<TaskInfo> pTaskInfo;
	auto iter = m_taskInfos.begin();
	while (iter != m_taskInfos.end())
	{
		if (!(*iter))
		{
			iter = m_taskInfos.erase(iter);
			assert(false);
			continue;
		}
		std::unique_ptr<TaskInfo> &pFindTaskInfo = *iter;
		if (pFindTaskInfo->groupIdValid
			&& m_curGroupIds.find(pFindTaskInfo->groupId) != m_curGroupIds.end())
		{
			++iter;
			continue;
		}
		pTaskInfo = std::move(pFindTaskInfo);
		m_taskInfos.erase(iter);
		break;
	}
	return pTaskInfo;
}

void CTaskPool::TaskThread(ThreadInfo &threadInfo)
{
	auto &threadStatus = threadInfo.s;
	

	{
		std::lock_guard<std::mutex> lk(m_mutex);
		threadStatus = ThreadStatusFree;
	}
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, 
			[&]()->bool
		{
			if (m_bExit
				|| !m_taskInfos.empty())
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
			threadStatus = ThreadStatusNone;
			break;
		}
	
		std::unique_ptr<TaskInfo> pTaskInfo = InnerGetTaskInfo();
	DoTask:
		threadStatus = ThreadStatusBusy;
		if (pTaskInfo
			&& pTaskInfo->groupIdValid)
		{
			m_curGroupIds.insert(pTaskInfo->groupId);
		}

		lk.unlock();

		if (pTaskInfo)
		{
			pTaskInfo->job();
			if (pTaskInfo->groupIdValid)
			{
				std::lock_guard<std::mutex> lkguard(m_mutex);
				m_curGroupIds.erase(pTaskInfo->groupId);
			}
			pTaskInfo.reset();
		}
		
		//再次检测下任务
		lk.lock();
		if (m_bExit)
		{
			threadStatus = ThreadStatusNone;
			break;
		}
		else
		{
			pTaskInfo = InnerGetTaskInfo();
			if (pTaskInfo)
			{
				goto DoTask;
			}
			else
			{
				threadStatus = ThreadStatusFree;
				continue;
			}
		}
	}
}

