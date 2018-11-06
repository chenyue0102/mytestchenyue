// TestIOCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <set>
#include "IOCPServer.h"
#include "tsdeque.h"
#include "TaskPool.h"
#include "Single.h"

int main()
{
	auto &server = CSingle<CIOCPServer>::Instance();
	auto &taskPool = CSingle<CTaskPool>::Instance();
	int a = 0;
	server.Open(5617);
	taskPool.Open(2);

	do 
	{
		std::cin >> a;
		switch (a)
		{
		case 1:
			server.Open(5617);
			break;
		case 2:
			server.Close();
			break;
		case 3:
			taskPool.Open(2);
			break;
		case 4:
			taskPool.Close();
			break;
		case 5:
			{
				int nSleep = 5;
				auto fun = [nSleep]()->void {
					std::cout << "task begin " << std::this_thread::get_id() << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(nSleep));
					std::cout << "task end" << std::endl;
				};
				taskPool.AddTask(fun);
			}
			break;
		default:
			break;
		}
	} while (a != 0);
	
    return 0;
}

