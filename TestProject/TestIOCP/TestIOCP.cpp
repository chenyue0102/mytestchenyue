// TestIOCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <set>
#include "IOCPServer.h"
#include "tsdeque.h"

int main()
{
	std::set<int> s = {9,2};
	auto p = s.erase(2);
	CIOCPServer server;
	server.Open(5617);
	int a = 0;

	do 
	{
		std::cin >> a;
		switch (a)
		{
		case 1:
			server.Close();
			break;
		default:
			break;
		}
	} while (a != 0);
	
    return 0;
}

