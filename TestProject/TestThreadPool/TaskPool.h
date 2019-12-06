#pragma once
#include <mutex>
#include <thread>
#include <list>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <assert.h>
#include <limits>

template<typename TASK_JOB, typename TASK_GROUPID>
class CTaskPool
{
	enum ThreadStatus
	{
		ThreadStatusNone,
		ThreadStatusBusy,
		ThreadStatusFree,
	};
	struct TaskInfo
	{
		TASK_JOB job;
		TASK_GROUPID groupId;
	};
	typedef std::list<TaskInfo> TASK_INFO_ARRAY;
	struct ThreadInfo
	{
		std::thread thd;
		std::mutex mtx;
		volatile bool bExit = false;
		std::condition_variable cv;
		ThreadStatus status;
		TASK_INFO_ARRAY tasks;
	};
public:
	CTaskPool()
		: m_threadInfos()
	{

	}
	~CTaskPool()
	{

	}
public:
	bool Open(unsigned int nPoolSize)
	{
		bool bRes = false;

		do
		{
			if (0 == nPoolSize)
			{
				nPoolSize = std::thread::hardware_concurrency() * 2 + 1;
			}

			bool bError = false;
			for (unsigned int nIndex = 0; nIndex < nPoolSize; nIndex++)
			{
				std::unique_ptr<ThreadInfo> pThreadInfo(new ThreadInfo());// = std::make_unique<ThreadInfo>();
				if (!pThreadInfo)
				{
					bError = true;
					assert(false);
					break;
				}
				std::lock_guard<std::mutex> lk(pThreadInfo->mtx);//先锁上锁，使得初始化完成后，线程才能够
				pThreadInfo->status = ThreadStatusNone;
				pThreadInfo->thd = std::thread(&CTaskPool::TaskThread, this, std::ref(*pThreadInfo));
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

	bool Close()
	{
		for (auto &pThreadInfo : m_threadInfos)
		{
			std::lock_guard<std::mutex> lk(pThreadInfo->mtx);
			pThreadInfo->bExit = true;
			pThreadInfo->cv.notify_one();
		}
		for (auto &pThreadInfo : m_threadInfos)
		{
			if (pThreadInfo
				&& pThreadInfo->thd.joinable())
			{
				if (std::this_thread::get_id() == pThreadInfo->thd.get_id())
				{
					assert(false);
				}
				pThreadInfo->thd.join();
			}
		}
		m_threadInfos.clear();
		return true;
	}

	bool AddTask(const TASK_JOB &fun)
	{
		return InnerAddOrderTask(fun, false, 0);
	}
	bool AddOrderTask(const TASK_JOB &fun, TASK_GROUPID groupId)
	{
		return InnerAddOrderTask(fun, true, groupId);
	}
private:
	bool InnerAddOrderTask(const TASK_JOB &job, bool groupIdValid, TASK_GROUPID groupId)
	{
		bool bRes = false;

		do
		{
			if (!job)
			{
				assert(false);
				break;
			}
			if (m_threadInfos.empty())
			{
				assert(false);
				break;
			}

			TaskInfo taskInfo;
			taskInfo.job = job;
			taskInfo.groupId = groupId;
			if (groupIdValid)
			{
				int index = static_cast<int>(groupId % m_threadInfos.size());
				auto &pThreadInfo = m_threadInfos.at(index);
				std::lock_guard<std::mutex> lk(pThreadInfo->mtx);
				pThreadInfo->tasks.push_back(taskInfo);
				pThreadInfo->cv.notify_one();
			}
			else
			{
				size_t maxLimit = (std::numeric_limits<size_t>::max)();
				size_t selectIndex = maxLimit, minCount = maxLimit;
				for (size_t i = 0; i < m_threadInfos.size(); i++)
				{
					auto &pThreadInfo = m_threadInfos.at(i);
					std::lock_guard<std::mutex> lk(pThreadInfo->mtx);
					if (/*pThreadInfo->status == ThreadStatusFree
						&& */pThreadInfo->tasks.empty())
					{
						pThreadInfo->tasks.push_back(taskInfo);
						pThreadInfo->cv.notify_one();
						selectIndex = maxLimit;
						break;
					}
					if (pThreadInfo->tasks.size() < minCount)
					{
						selectIndex = i;
						minCount = pThreadInfo->tasks.size();
					}
				}
				if (maxLimit != selectIndex)
				{
					auto &pThreadInfo = m_threadInfos.at(selectIndex);
					std::lock_guard<std::mutex> lk(pThreadInfo->mtx);
					pThreadInfo->tasks.push_back(taskInfo);
					pThreadInfo->cv.notify_one();
				}
			}
			bRes = true;
		} while (false);

		return bRes;
	}
	void TaskThread(ThreadInfo &threadInfo)
	{
		{
			std::lock_guard<std::mutex> lk(threadInfo.mtx);
			threadInfo.status = ThreadStatusFree;
		}
		while (true)
		{
			std::unique_lock<std::mutex> lk(threadInfo.mtx);
			threadInfo.cv.wait(lk,
				[&]()->bool
			{
				if (threadInfo.bExit
					|| !threadInfo.tasks.empty())
				{
					return true;
				}
				else
				{
					return false;
				}
			});
			if (threadInfo.bExit)
			{
				threadInfo.status = ThreadStatusNone;
				break;
			}
			threadInfo.status = ThreadStatusBusy;
		DOTASK:
			assert(!threadInfo.tasks.empty());
			TaskInfo taskInfo = threadInfo.tasks.front();
			assert(taskInfo.job);
			threadInfo.tasks.pop_front();

			lk.unlock();
			try
			{
				taskInfo.job();
				taskInfo.job = nullptr;
				taskInfo.groupId = 0;
			}
			catch (...)
			{
				assert(false);
			}
			lk.lock();

			//再次检测下任务
			if (threadInfo.bExit)
			{
				threadInfo.status = ThreadStatusNone;
				break;
			}
			else
			{
				if (threadInfo.tasks.empty())
				{
					threadInfo.status = ThreadStatusFree;
				}
				else
				{
					goto DOTASK;
				}
			}
		}
	}
public:
	typedef std::vector<std::unique_ptr<ThreadInfo>> THREAD_INFO_ARRAY;
	THREAD_INFO_ARRAY m_threadInfos;
};

