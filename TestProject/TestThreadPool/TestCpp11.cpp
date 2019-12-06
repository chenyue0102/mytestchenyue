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
#include <sstream>
#include <assert.h>
#include "MyThreadTask.h"
#include "MyTaskFun.h"
#include "MyThreadPool.h"
#include <windows.h>
#include "TaskPool.h"

std::mutex g_mx;
std::list<std::string> g_logArray;

void OutputLog(volatile bool &bExit)
{
	while (!bExit)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::unique_lock<std::mutex> lk(g_mx);
		while (!g_logArray.empty())
		{
			std::string str = *g_logArray.begin();
			OutputDebugStringA(str.c_str());
			g_logArray.pop_front();
		}
	}
}

void Log(const std::string &strText)
{
	std::lock_guard<std::mutex> lk(g_mx);
	g_logArray.push_back(strText);
}

void TestTask(long long &llTaskID)
{
	int n = rand() % 10;
	if (n < 3)
	{
		n = 3;
	}
	{
		std::stringstream ss;
		ss << "task execing " << llTaskID << " threadID=" << std::this_thread::get_id() << std::endl;
		Log(ss.str());
	}
	
	while ((++n) < 10)
	{
		if (MyTaskFun::IsTaskInterrupted())
		{
			std::stringstream ss;
			ss << "task Interrupted " << llTaskID << " threadID=" << std::this_thread::get_id() << std::endl;
			Log(ss.str());
			throw MyTaskFun::GetTaskInterruptedException();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	{
		std::stringstream ss;
		ss << "task end " << llTaskID << " threadID=" << std::this_thread::get_id() << std::endl;
		Log(ss.str());
	}
	
}

int main()
{
	volatile bool bExit = false;
	std::thread tLog(&OutputLog, std::ref(bExit));
	std::vector<long long> llKeyArray;
	llKeyArray.resize(1000);
	{
		CMyThreadPool MyThreadPool;
		CTaskPool<std::function<void()>, size_t> taskPool;
		MyThreadPool.Open();
		int nKey = 0;
		std::thread::id id;
		//std::vector<DWORD> m_lastTime;
		std::atomic<DWORD> m_begin = 0, m_end = 0;

		int nNumber = 0;
		taskPool.Open(0);
		do
		{
			//m_lastTime.resize(std::thread::hardware_concurrency() * 2 + 1);
			scanf("%d", &nNumber);
			switch (nNumber)
			{
			case 0:
				break;
			case 1:
			{
				taskPool.Open(0);
				break;
			}
			case 2: 
			{
				taskPool.Close();
				break;
			}
			case 3:
			{
				id = std::thread::id();
				std::function<void()> fun = [&id]()
				{
					if (id == std::thread::id())
					{
						id = std::this_thread::get_id();
					}
					assert(id == std::this_thread::get_id());
					std::this_thread::sleep_for(std::chrono::milliseconds(10000));
				};
				for (int i = 0; i < 5; i++)
				{
					taskPool.AddOrderTask(fun, 1025);
				}
				break;
			}
			case 4: 
			{
				std::function<void()> fun = [&m_end]()
				{
					std::cout << std::this_thread::get_id() << std::endl;
					DWORD d = GetTickCount();
					if (m_end < d)
					{
						m_end = d;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				};
				m_begin = GetTickCount();
				for (int i = 0; i< 100; i++)
				{
					taskPool.AddTask(fun);
				}
				break;
			}
			case 5:
			{
				std::cout << m_end - m_begin << std::endl;
				break;
			}
			default:
			{
				break;
			}
			}
			/*if (1 == nNumber)
			{
				std::function<void()> Fun = std::bind(&TestTask, std::ref(llKeyArray[nKey]));
				MyThreadPool.DoTask(Fun, llKeyArray[nKey]);
				{
					std::stringstream ss;
					ss << "DoTask " << llKeyArray[nKey] << std::endl;
					Log(ss.str());
				}
				
				nKey++;
			}
			else if (2 == nNumber)
			{
				bExit = true;
				MyThreadPool.Close();
				tLog.join();
			}*/
			
			/*else if (nNumber > 0)
			{
				MyThreadPool.InterruptTask(nNumber, true);
			}*/
		} while (0 != nNumber);
	}
	
    return 0;
}

