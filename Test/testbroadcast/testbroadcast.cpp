// testbroadcast.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <assert.h>
#include <string.h>
#ifdef WIN32
#include <WinSock2.h>
#include <ws2ipdef.h> //sockaddr_in6
#include <WS2tcpip.h> //inet_pton
typedef int socklen_t;
#else
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <sys/wait.h>  
#include <unistd.h>  
#include <arpa/inet.h>  
#include <getopt.h>
#include<pthread.h>
#define closesocket close
#endif

#define LISTEN_PORT 9876
#ifdef WIN32
void initSocket()
{
    WORD wVersion = MAKEWORD(2, 2);
    WSADATA wsaData = { 0 };
    int ret = WSAStartup(wVersion, &wsaData);
    assert(ret == 0);
}
void cleanSocket()
{
    int ret = WSACleanup();
    assert(0 == ret);
}
#else
typedef int SOCKET;
#define INVALID_SOCKET -1
void initSocket()
{

}
void cleanSocket()
{

}
#endif
SOCKET createMultiBroadcast(ULONG multiIp, ULONG localIp, int port)
{
    SOCKET s = INVALID_SOCKET;
    do
    {
        if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
        {
            assert(false);
            break;
        }
        //重用地址
        BOOL opt = TRUE;
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
        {
            assert(false);
            break;
        }
        //设置ttl为2
        int ttl = 2;
        if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl)) < 0)
        {
            assert(false);
            break;
        }
        //不接受自己发送的信息
        unsigned char loopchar = 0;
        if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&loopchar, sizeof(loopchar)) < 0)
        {
            assert(false);
            break;
        }
        //设置允许广播
        int bcast = 1;
        if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&bcast, sizeof(bcast)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in addr = { 0 };
        addr.sin_port = htons(port);                    //端口
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_family = AF_INET;
        if (bind(s, (sockaddr*)&addr, sizeof(addr)) < 0)
        {
            assert(false);
            break;
        }
        ip_mreq multiCast;
        multiCast.imr_multiaddr.s_addr = multiIp;// inet_addr("239.255.255.250");    //组播地址
        multiCast.imr_interface.s_addr = localIp;//inet_addr("10.0.30.48");      //本机地址
        if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast)) < 0)
        {
            assert(false);
            break;
        }
    } while (false);
    return s;
}

#define SERVER_IP "239.255.255.250"
#define SERVER_PORT 9898
void serverthread()
{
    SOCKET s = createMultiBroadcast(inet_addr(SERVER_IP), INADDR_ANY, SERVER_PORT);
    while (true)
    {
		const int bufferLen = 1024;
		char buffer[bufferLen + 1];
        sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);
        int recvLen = recvfrom(s, buffer, bufferLen, 0, (sockaddr*)&clientAddr, &addrLen);
        buffer[recvLen] = '\0';
        char ip[16] = { 0 };
        inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));
        printf("server recv:%s ip:%s\n", buffer, ip);
        sendto(s, buffer, recvLen, 0, (sockaddr*)&clientAddr, sizeof(clientAddr));
    }
}
int main()
{
    initSocket();

    int a = 0;
    SOCKET s = INVALID_SOCKET;
    do
    {
        printf("0:exit 1:startserver 2:startclient 3:send 4:recv\n");
        scanf("%d", &a);
        switch (a) 
        {
        case 1:
        {
            std::thread t(&serverthread);
            t.detach();
            break;
        }
        case 2:
        {
            s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
            break;
        }
        case 3:
        {
            const char* str = "hello multibroadcast";
            int len = strlen(str);
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(SERVER_PORT);
            addr.sin_addr.s_addr = inet_addr(SERVER_IP);
            int sendLen = sendto(s, str, len, 0, (sockaddr*)&addr, sizeof(addr));
            printf("sendLen=%d\n", sendLen);
            break;
        }
        case 4:
        {
            const int bufferLen = 1024;
            char buffer[bufferLen + 1];
            sockaddr_in addr;
            int addrLen = sizeof(addr);
            int recvLen = recvfrom(s, buffer, bufferLen, 0, (sockaddr*)&addr, &addrLen);
            buffer[recvLen] = '\0';
            char ip[16] = {0};
            inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
            printf("client recv:%s ip:%s\n", buffer, ip);
            break;
        }
        }
    } while (0 != a);

    cleanSocket();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
