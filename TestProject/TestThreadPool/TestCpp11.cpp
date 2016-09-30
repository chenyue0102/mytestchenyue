// TestCpp11.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <iostream>
#include <atomic>
#include <string>
#include "MyThreadTask.h"
#include "MyTaskFun.h"
#include "MyThreadPool.h"

enum EnumAction
{
	EnumActionNone,
	EnumActionExit,
	EnumActionNotify,
};

void ThreadProc(std::condition_variable &cv, std::mutex &mx, std::vector<int> &vtNumber, volatile EnumAction &act)
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [&act]()
		{
			return EnumActionNone != act;
		});
		if (EnumActionNotify == act)
		{
			std::vector<int> vtTemp = std::move(vtNumber);
			lk.unlock();
			for (auto &OneNumber : vtTemp)
			{
				printf("recv %d\n", OneNumber);
			}
		}
		else if (EnumActionExit == act)
		{
			printf("recv exit\n");
			break;
		}
	}
}

void DoJob(std::mutex &mx, std::condition_variable &cv, std::queue<std::function<void()>> &JobArray)
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [&JobArray]() {return !JobArray.empty(); });
		if (JobArray.size() != 0)
		{
			std::function<void()> Fun = JobArray.front();
			int nNumber = JobArray.size();
			JobArray.pop();
			lk.unlock();
			if (Fun)
			{
				std::cout << nNumber << "  ";
				Fun();
			}
		}
	}
}

void DoFun()
{
	std::cout << "jobid=" << std::this_thread::get_id() << std::endl;
	int nCount = rand() % 1000;
	std::this_thread::sleep_for(std::chrono::milliseconds(nCount));
}

void TestTask(long long &llTaskID)
{
	int n = rand() % 10;
	if (n < 3)
	{
		n = 3;
	}
	std::cout << "task execing " << llTaskID << " threadID=" << std::this_thread::get_id() << std::endl;
	while ((++n) < 10)
	{
		if (MyTaskFun::IsTaskInterrupted())
		{
			std::cout << "task Interrupted " << llTaskID << " threadID=" << std::this_thread::get_id() << std::endl;
			throw MyTaskFun::GetTaskInterruptedException();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	//printf("task throw InterruptedException\n");
	//throw MyTaskFun::GetTaskInterruptedException();

	std::cout << "task end " << llTaskID << " threadID="<< std::this_thread::get_id() << std::endl;
}

struct TestNotify : public INotifyTask
{
	virtual void NotifyTaskCompleted(long long llTaskID, bool)
	{
		//printf("complete taskid=%lld\n", llTaskID);
	}
};

int main()
{
	std::vector<long long> llKeyArray;
	llKeyArray.resize(1000);
	{
		CMyThreadPool MyThreadPool;
		MyThreadPool.Open();
		int nKey = 0;

		int nNumber = 0;
		do
		{
			scanf("%d", &nNumber);
			if (1 == nNumber)
			{
				std::function<void()> Fun = std::bind(&TestTask, std::ref(llKeyArray[nKey]));
				MyThreadPool.DoTask(Fun, llKeyArray[nKey]);
				std::cout << "DoTask " << llKeyArray[nKey] << std::endl;
				nKey++;
			}
			else if (2 == nNumber)
			{
				MyThreadPool.Close();
			}
			else if (nNumber > 0)
			{
				MyThreadPool.InterruptTask(nNumber, true);
			}
		} while (0 != nNumber);
	}
	
    return 0;
}

