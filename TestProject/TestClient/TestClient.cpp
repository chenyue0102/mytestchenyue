// TestClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <MSWSock.h>
#include <assert.h>
#include "pch.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "SmartPtr.h"
#include <thread>
#include <list>
#include <memory>
#include <assert.h>
#pragma comment(lib, "Ws2_32.lib")

void ConverHeader(void *pMsg)
{
	MSGHEADER header = { 0 };
	memcpy(&header, pMsg, sizeof(header));
	header = Host2Net(header);
	memcpy(pMsg, &header, sizeof(header));
}

void test8(SOCKET s)
{
	MSG_GET_BIG_DATA_REQ req = { 0 };
	req.header.dwMsgID = PID_GET_BIG_DATA;
	req.header.dwMsgLen = sizeof(req);
	ConverHeader(&req);
	send(s, (char*)&req, sizeof(req), 0);

	MSG_GET_BIG_DATA_ACK ack = { 0 };

	int allrecv = 0;
	while (allrecv < sizeof(MSG_GET_BIG_DATA_ACK))
	{
		int len = recv(s, ((char*)&ack) + allrecv, sizeof(ack) - allrecv, 0);
		if (len <= 0)
		{
			break;
		}
		allrecv += len;
	}


	auto *pBigData = &ack;
	for (auto &x : pBigData->a)
	{
		assert('a' == x);
	}
	for (auto &x : pBigData->b)
	{
		assert('b' == x);
	}
	for (auto &x : pBigData->d)
	{
		assert('d' == x);
	}
	for (auto &x : pBigData->e)
	{
		assert('e' == x);
	}
	for (auto &x : pBigData->f)
	{
		assert('f' == x);
	}
}

void test7(SOCKET s)
{
	MSG_BIG_DATA_REQ *pBigData = new MSG_BIG_DATA_REQ();
	memset(pBigData, 0, sizeof(MSG_BIG_DATA_REQ));
	pBigData->header.dwMsgID = PID_SEND_BIG_DATA;
	pBigData->header.dwMsgLen = sizeof(MSG_BIG_DATA_REQ);
	memset(pBigData->a, 'a', sizeof(pBigData->a));
	memset(pBigData->b, 'b', sizeof(pBigData->b));
	memset(pBigData->c, 'c', sizeof(pBigData->c));
	memset(pBigData->d, 'd', sizeof(pBigData->d));
	memset(pBigData->e, 'e', sizeof(pBigData->e));
	memset(pBigData->f, 'f', sizeof(pBigData->f));

	ConverHeader(pBigData);
	send(s, (char*)pBigData, sizeof(MSG_BIG_DATA_REQ), 0);
	delete pBigData;

	MSG_BIG_DATA_ACK ack;
	recv(s, (char*)&ack, sizeof(ack), 0);
}

void threadproc8()
{
	WSADATA lwsaData;
	WSAStartup(MAKEWORD(2, 2), &lwsaData);
	while (true)
	{
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(5617);
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.101");

		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		connect(s, (const sockaddr*)&addr, sizeof(addr));

		test8(s);
		closesocket(s);
	}
}

void threadproc7()
{
	WSADATA lwsaData;
	WSAStartup(MAKEWORD(2, 2), &lwsaData);
	while (true)
	{
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(5617);
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.101");

		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		connect(s, (const sockaddr*)&addr, sizeof(addr));

		test7(s);
		closesocket(s);
	}
}

struct test
{
	unsigned int a : 4;
	unsigned int b : 4;
	unsigned int c : 4;
	unsigned int d : 4;
};

int main()
{
	test t = {0};
	t.a = 0x1;
	t.b = 0x2;
	t.c = 0x4;
	t.d = 0x8;
	char cc[4] = { 0 };
	memcpy(cc, &t, sizeof(t));
	int c = 235;
	c -= c % 20;

	int a = 0;
	WSADATA lwsaData;
	WSAStartup(MAKEWORD(2, 2), &lwsaData);

	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5617);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.100.100");//inet_addr("192.168.56.101");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	MSGHEADER local = { 0 };
	local.dwMsgLen = sizeof(local);
	local = Host2Net(local);
	std::list<std::unique_ptr<std::thread>> threadArray;
	do
	{
		printf("0:exit 1:init and connect 2:send 3:test 4:close 5:heart beat \n");
		printf("6:getipaddress 7:send big data 8:recv big data 9:shutdown send\n");
		printf("10:shutdown recv\n");
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
		{
			for (int i = 0; i < 30; i++)
			{
				std::unique_ptr<std::thread> pThread(new std::thread(&threadproc7));
				threadArray.push_back(std::move(pThread));
			}

			for (int i = 0; i < 30; i++)
			{
				std::unique_ptr<std::thread> pThread(new std::thread(&threadproc8));
				threadArray.push_back(std::move(pThread));
			}
			break;
		}
		case 4:
			closesocket(s);
			break;
		case 5:
			send(s, (char*)&local, sizeof(local), 0);
			break;
		case 6:
		{
			MSG_GET_IPADDRESS_REQ req = { 0 };
			req.header.dwMsgID = PID_GET_IPADDRESS;
			req.header.dwMsgLen = sizeof(req);
			req.header = Host2Net(req.header);
			send(s, (char*)&req, sizeof(req), 0);
			MSG_GET_IPADDRESS_ACK ack = { 0 };
			int re = recv(s, (char*)&ack, sizeof(ack), 0);
			//assert(re == sizeof(ack));
			ack.header = Net2Host(ack.header);
			printf("msgid=%x myipaddress %s\n", ack.header.dwMsgID, ack.szIpAddress);
			break;
		}
		case 7:
		{
			MSG_BIG_DATA_REQ *pBigData = new MSG_BIG_DATA_REQ();
			memset(pBigData, 0, sizeof(MSG_BIG_DATA_REQ));
			pBigData->header.dwMsgID = PID_SEND_BIG_DATA;
			pBigData->header.dwMsgLen = sizeof(MSG_BIG_DATA_REQ);
			memset(pBigData->a, 'a', sizeof(pBigData->a));
			memset(pBigData->b, 'b', sizeof(pBigData->b));
			memset(pBigData->c, 'c', sizeof(pBigData->c));
			memset(pBigData->d, 'd', sizeof(pBigData->d));
			memset(pBigData->e, 'e', sizeof(pBigData->e));
			memset(pBigData->f, 'f', sizeof(pBigData->f));

			ConverHeader(pBigData);
			send(s, (char*)pBigData, sizeof(MSG_BIG_DATA_REQ), 0);
			delete pBigData;
			
			MSG_BIG_DATA_ACK ack;
			recv(s, (char*)&ack, sizeof(ack), 0);
			break;
		}
		case 8:
		{
			test8(s);
			break;
		}
		case 9:
		{
			shutdown(s, SD_SEND);
			break;
		}
		case 10:
		{
			shutdown(s, SD_RECEIVE);
			break;
		}
		case 11:
		{
			SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.S_un.S_addr = inet_addr("192.168.100.135");//inet_addr("192.168.56.101");
			addr.sin_port = htons(5618);

			int len = 65000;
			std::string str(len, 'a');
			int sendret = sendto(s, str.data(), str.size(), 0, (sockaddr*)&addr, sizeof(addr));
			char sz[1024] = { 0 };
			sockaddr_in recvAddr;
			int recvAddrLen = sizeof(recvAddr);
			recvfrom(s, sz, sizeof(sz), 0, (sockaddr*)&recvAddr, &recvAddrLen);
			printf("recv udp %s\n", sz);
			break;
		}
		case 12:
		{
			SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
			addr.sin_port = htons(5618);
			bind(s, (sockaddr*)&addr, sizeof(addr));

			char buf[65525] = { 0 };
			sockaddr_in recvAddr;
			int recvAddrLen = sizeof(recvAddr);
			int nrecv = recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&recvAddr, &recvAddrLen);
			buf[nrecv] = '\0';
			printf("recv udp %s\n");
			sendto(s, "echo", 4, 0, (sockaddr*)&recvAddr, sizeof(recvAddr));
			closesocket(s);
			break;
		}
		case 13:
		{
			SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.S_un.S_addr = inet_addr("192.168.100.1");
			addr.sin_port = htons(5618);
			int ret = bind(s, (sockaddr*)&addr, sizeof(addr));

			addr.sin_addr.S_un.S_addr = inet_addr("192.168.100.136");
			sendto(s, "echo", 4, 0, (sockaddr*)&addr, sizeof(addr));

			char buf[1024] = { 0 };
			sockaddr_in recvAddr;
			int recvAddrLen = sizeof(recvAddr);
			int nrecv = recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&recvAddr, &recvAddrLen);
			buf[nrecv] = '\0';
			printf("recv udp %s\n");
			
			closesocket(s);
			break;
		}
		case 14:
		{
			send(s, "1234", 4, 0);
			char sz[1024] = { 0 };
			recv(s, sz, sizeof(sz), 0);
			printf("%s\n", sz);
			break;
		}
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
