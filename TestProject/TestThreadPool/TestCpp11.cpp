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
	std::cout << "task end " << llTaskID << " threadID="<< std::this_thread::get_id() << std::endl;
}

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

