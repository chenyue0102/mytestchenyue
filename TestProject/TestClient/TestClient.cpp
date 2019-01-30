// TestClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <MSWSock.h>
#include <assert.h>
#include "pch.h"
#include <iostream>
#include <memory>
#include <Windows.h>
#include "SmartPtr.h"
#include <assert.h>
#pragma comment(lib, "Ws2_32.lib")

void ConverHeader(void *pMsg)
{
	MSGHEADER header = { 0 };
	memcpy(&header, pMsg, sizeof(header));
	header = Host2Net(header);
	memcpy(pMsg, &header, sizeof(header));
}

int main()
{
	int a = 0;
	WSADATA lwsaData;
	WSAStartup(MAKEWORD(2, 2), &lwsaData);

	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5617);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.101");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	MSGHEADER local = { 0 };
	local.dwMsgLen = sizeof(local);
	local = Host2Net(local);

	do
	{
		printf("0:exit 1:init and connect 2:send 3: 4:close 5:heart beat \n");
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
			break;
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
			MSG_GET_BIG_DATA_REQ req = { 0 };
			req.header.dwMsgID = PID_GET_BIG_DATA;
			req.header.dwMsgLen = sizeof(req);
			ConverHeader(&req);
			send(s, (char*)&req, sizeof(req), 0);

			MSG_GET_BIG_DATA_ACK ack = {0};

			int allrecv = 0;
			while (allrecv < sizeof(MSG_GET_BIG_DATA_ACK))
			{
				int len = recv(s, ((char*)&ack) + allrecv, sizeof(ack) - allrecv, 0);
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
			printf("");
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
