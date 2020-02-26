#include <assert.h>
#include "TaskPool.h"


CTaskPool::CTaskPool()
	: m_mutex()
	, m_cv()
	, m_threadInfos()
	, m_taskInfos()
	, m_curGroupIds()
	, m_bExit(false)
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
		Close();
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bExit = false;
		if (0 == nPoolSize)
		{
			nPoolSize = std::thread::hardware_concurrency() * 2 + 1;
		}
		for (unsigned int nIndex = 0; nIndex < nPoolSize; nIndex++)
		{
			std::unique_ptr<ThreadInfo> pThreadInfo(new ThreadInfo);
			pThreadInfo->t = std::thread(&CTaskPool::TaskThread, this, std::ref(*pThreadInfo));
			pThreadInfo->index = nIndex;
			m_threadInfos.push_back(std::move(pThreadInfo));
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
	for (auto &curThreadInfo : m_threadInfos)
	{
		if (curThreadInfo->t.joinable())
		{
			if (std::this_thread::get_id() == curThreadInfo->t.get_id())
			{
				assert(false);
			}
			curThreadInfo->t.join();
		}
	}
	m_threadInfos.clear();
	//m_cv
	m_curGroupIds.clear();
	m_taskInfos.clear();
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
		std::unique_ptr<TaskInfo> pTaskInfo(new TaskInfo());// = std::make_unique<TaskInfo>();
		pTaskInfo->job = job;
		pTaskInfo->groupIdValid = groupIdValid;
		pTaskInfo->groupId = groupId;
		if (groupIdValid)
		{
			//如果该分组已经分配给某个线程,则放到该线程的任务队列中,否则放入公共任务中
			auto iter = m_curGroupIds.find(groupId);
			if (iter != m_curGroupIds.end())
			{
				auto& curThreadInfo = m_threadInfos[iter->second];
				std::lock_guard<std::mutex> lk(curThreadInfo->mtx);
				curThreadInfo->taskInfos.push_back(std::move(pTaskInfo));
			}
			else
			{
				m_taskInfos.push_back(std::move(pTaskInfo));
			}
		}
		else
		{
			m_taskInfos.push_back(std::move(pTaskInfo));
		}
		m_cv.notify_one();

		bRes = true;
	} while (false);

	return bRes;
}

std::unique_ptr<CTaskPool::TaskInfo> CTaskPool::InnerGetTaskInfo(ThreadInfo& curThreadInfo)
{
	std::unique_ptr<TaskInfo> pTaskInfo;
	{
		//先查找自己线程的任务
		std::lock_guard<std::mutex> lk(curThreadInfo.mtx);
		if (!curThreadInfo.taskInfos.empty())
		{
			pTaskInfo = std::move(curThreadInfo.taskInfos.front());
			curThreadInfo.taskInfos.pop_front();
		}
		else
		{
			//自己线程的任务完了,清空下groupid
			if (curThreadInfo.groupIdValid)
			{
				curThreadInfo.groupIdValid = false;
				m_curGroupIds.erase(curThreadInfo.groupId);
				curThreadInfo.groupId = 0;
			}
		}
		
	}
	if (!pTaskInfo)
	{
		if (!m_taskInfos.empty())
		{
			pTaskInfo = std::move(m_taskInfos.front());
			m_taskInfos.pop_front();
			//这个任务需要按照groupid顺序处理
			if (pTaskInfo->groupIdValid)
			{
				m_curGroupIds.insert(std::make_pair(pTaskInfo->groupId, curThreadInfo.index));
				std::lock_guard<std::mutex> lk(curThreadInfo.mtx);
				curThreadInfo.groupIdValid = true;
				curThreadInfo.groupId = pTaskInfo->groupId;

				//将剩余的此group的任务也加到当前线程队列中
				auto iter = m_taskInfos.begin();
				while (iter != m_taskInfos.end()) 
				{
					if ((*iter)->groupIdValid && (*iter)->groupId == pTaskInfo->groupId)
					{
						curThreadInfo.taskInfos.push_back(std::move(*iter));
						iter = m_taskInfos.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
		}
	}
	return pTaskInfo;
}

bool CTaskPool::innerCheckCurThreadTask(ThreadInfo& curThreadInfo)
{
	std::lock_guard<std::mutex> lk(curThreadInfo.mtx);
	return !curThreadInfo.taskInfos.empty();
}

bool CTaskPool::innerCheckTask()
{
	return !m_taskInfos.empty();
}

void CTaskPool::TaskThread(ThreadInfo &threadInfo)
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, 
			[&]()->bool
		{
			if (m_bExit
				|| innerCheckCurThreadTask(threadInfo)
				|| innerCheckTask())
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
	
		std::unique_ptr<TaskInfo> pTaskInfo = InnerGetTaskInfo(threadInfo);
	DoTask:

		lk.unlock();
		if (pTaskInfo)
		{
			try
			{
				pTaskInfo->job();
			}
			catch (...)
			{
				assert(false);
			}
			pTaskInfo.reset();
		}
		lk.lock();
		
		//再次检测下任务
		if (m_bExit)
		{
			break;
		}
		else
		{
			pTaskInfo = InnerGetTaskInfo(threadInfo);
			if (pTaskInfo)
			{
				goto DoTask;
			}
			else
			{
				continue;
			}
		}
	}
}

