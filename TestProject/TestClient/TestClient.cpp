// TestClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <MSWSock.h>
#include "pch.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "SmartPtr.h"
#pragma comment(lib, "Ws2_32.lib")

struct IUnknownEx
{
	virtual unsigned long AddRef(void)
	{
		return 0;
	}

	virtual unsigned long Release(void)
	{
		return 0;
	}
};

struct test : public IUnknownEx
{
	void dotest()
	{
		printf("test");
	}

};
int main()
{
	/*std::unique_ptr<test> p(new test);
	p->dotest();*/
	SmartPtr<test> pSmartPtr(new test);
	pSmartPtr->dotest();
	auto f = [pSmartPtr]()
	{
		pSmartPtr->dotest();
	};
	
	int a = 0;
	WSADATA lwsaData;
	WSAStartup(MAKEWORD(2, 2), &lwsaData);

	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5617);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.101");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	do
	{
		printf("0:exit 1:init and connect 2:send 3: 4:close\n");
		scanf("%d", &a);
		switch (a)
		{
		case 0:
			break;
		case 1:
			s = socket(AF_INET, SOCK_STREAM, 0);
			connect(s, (const sockaddr*)&addr, sizeof(addr));
			break;
		case 2:
			send(s, "1234", 4, 0);
			break;
		case 3:
			break;
		case 4:
			closesocket(s);
			break;
		default:
			break;
		}
	} while (0 != a);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
