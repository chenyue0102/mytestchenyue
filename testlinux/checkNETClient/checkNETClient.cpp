// checkNETClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include "../checkNET/CheckProtocol.h"
#pragma comment(lib, "Ws2_32.lib")
#define CLIENT_PORT 8795
#define SERVER_IPADDRESS "144.168.59.80"
//#define SERVER_IPADDRESS "192.168.29.129"
int main()
{
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(CLIENT_PORT);
	bind(s, (sockaddr*)&addr, sizeof(addr));

	sockaddr_in addr_server;
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.S_un.S_addr = inet_addr(SERVER_IPADDRESS);
	addr_server.sin_port = htons(MY_UDP_PORT);

	int a = 0;
	do
	{
		printf("0:exit 1:query address \n");
		scanf("%d", &a);
		if (0 != a)
		{
			MSG_HEADER header;
			header.msgId = htonl(a);
			sendto(s, (char*)&header, sizeof(header), 0, (sockaddr*)&addr_server, sizeof(addr_server));
			char buf[1024] = { 0 };
			int bufLen = 1024;
			memset(&addr_server, 0, sizeof(addr_server));
			int addrLen = sizeof(addr_server);
			int recvLen = recvfrom(s, buf, bufLen, 0, (sockaddr*)&addr_server, &addrLen);
			if (recvLen >= sizeof(header))
			{
				memcpy(&header, buf, sizeof(header));
				int msgId = ntohl(header.msgId);
				switch (msgId)
				{
				case EMsgIdQueryAddress:
				{
					MSG_QUERY_ADDRESS address;
					if (recvLen >= sizeof(address))
					{
						memcpy(&address, buf, sizeof(address));
						in_addr addr;
						addr.S_un.S_addr = address.clientAddress;
						const char*p = inet_ntoa(addr);
						unsigned int port = ntohs(address.clientPort);
						printf("ip=%s port=%d\n", p, port);
					}
					break;
				}
				}
			}
		}
	} while (a != 0);
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
