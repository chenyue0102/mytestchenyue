// testipv6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <assert.h>
#include <string.h>
#ifdef WIN32
#include <WinSock2.h>
#include <ws2ipdef.h> //sockaddr_in6
#include <WS2tcpip.h> //inet_pton
#undef _UNICODE
#include "getopt.h"
#define _UNICODE
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

void doProcess6(SOCKET s, const sockaddr_in6& addr)
{
    const int BUF_LEN = 1024;
    char buffer[BUF_LEN + 1];
    char ackbuffer[BUF_LEN + 1];
    char addressBuffer[40] = { 0 };
    if (nullptr == inet_ntop(AF_INET6, &addr.sin6_addr, addressBuffer, 40))
    {
        assert(false);
        return;
    }
    printf("accept=%s\n", addressBuffer);
    while (true)
    {
        int recvLen = recv(s, buffer, BUF_LEN, 0);
        if (recvLen <= 0)
        {
            break;
        }
        buffer[recvLen] = '\0';
        printf("%s\n", buffer);
        int len = snprintf(ackbuffer, BUF_LEN, "ack=%s", buffer);
        if (len < 0)
        {
            break;
        }
        int sendLen = send(s, ackbuffer, len, 0);
    }
    closesocket(s);
}

void doAcceptLoop6(SOCKET s)
{
    while (true)
    {
        sockaddr_in6 addr = { 0 };
        socklen_t addrLen = sizeof(addr);
        SOCKET apt = accept(s, (sockaddr*)&addr, &addrLen);
        if (apt < 0)
        {
            break;
        }
        std::thread t(&doProcess6, apt, addr);
        t.detach();
    }
}

void startServer6(const std::string &address)
{
    SOCKET s = INVALID_SOCKET;
    do
    {
        if ((s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in6 addr = {0};
        addr.sin6_family = AF_INET6;
        addr.sin6_port = htons(LISTEN_PORT);
        if (address.empty())
        {
            addr.sin6_addr = in6addr_any;
        }
        else
        {
            if (inet_pton(AF_INET6, address.c_str(), &addr.sin6_addr) <= 0)
            {
                assert(false);
                break;
            }
        }
        if (bind(s, (const sockaddr*)&addr, sizeof(addr)) < 0)
        {
            assert(false);
            break;
        }
        if (listen(s, SOMAXCONN) < 0)
        {
            assert(false);
            break;
        }
        doAcceptLoop6(s);
    } while (false);
    
    if (INVALID_SOCKET != s)
    {
        closesocket(s);
        s = INVALID_SOCKET;
    }
}


void doProcess4(SOCKET s, const sockaddr_in& addr)
{
    const int BUF_LEN = 1024;
    char buffer[BUF_LEN + 1];
    char ackbuffer[BUF_LEN + 1];
    char addressBuffer[16] = { 0 };
    if (nullptr == inet_ntop(AF_INET, &addr.sin_addr, addressBuffer, 16))
    {
        assert(false);
        return;
    }
    printf("accept=%s\n", addressBuffer);
    while (true)
    {
        int recvLen = recv(s, buffer, BUF_LEN, 0);
        if (recvLen <= 0)
        {
            break;
        }
        buffer[recvLen] = '\0';
        printf("recvfrom %s %s\n", addressBuffer, buffer);
        int len = snprintf(ackbuffer, BUF_LEN, "ack=%s", buffer);
        if (len < 0)
        {
            break;
        }
        int sendLen = send(s, ackbuffer, len, 0);
    }
    closesocket(s);
}

void doAcceptLoop4(SOCKET s)
{
    while (true)
    {
        sockaddr_in addr = { 0 };
        socklen_t addrLen = sizeof(addr);
        SOCKET apt = accept(s, (sockaddr*)&addr, &addrLen);
        if (apt < 0)
        {
            break;
        }
        std::thread t(&doProcess4, apt, addr);
        t.detach();
    }
}

void startServer4(const std::string& address)
{
    SOCKET s = INVALID_SOCKET;
    do
    {
        if ((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in addr = { 0 };
        addr.sin_family = AF_INET;
        addr.sin_port = htons(LISTEN_PORT);
        if (address.empty())
        {
            addr.sin_addr.s_addr = INADDR_ANY;
        }
        else
        {
            if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) <= 0)
            {
                assert(false);
                break;
            }
            //addr.sin_addr.s_addr = inet_addr(address.c_str());
        }
        if (bind(s, (const sockaddr*)&addr, sizeof(addr)) < 0)
        {
            assert(false);
            break;
        }
        if (listen(s, SOMAXCONN) < 0)
        {
            assert(false);
            break;
        }
        doAcceptLoop4(s);
    } while (false);
}

void startClient6(const std::string& address)
{
    SOCKET s = INVALID_SOCKET;
    do
    {
        if ((s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in6 addr = { 0 };
        addr.sin6_family = AF_INET6;
        addr.sin6_port = htons(LISTEN_PORT);
        /*if (address.empty())
        {
            addr.sin6_addr = in6addr_any;
        }
        else*/
        {
            if (inet_pton(AF_INET6, address.c_str(), &addr.sin6_addr) <= 0)
            {
                assert(false);
                break;
            }
        }
        if (connect(s, (const sockaddr*)&addr, sizeof(addr)) < 0)
        {
            assert(false);
            break;
        }
        char c[] = "hello, world";
        if (send(s, c, strlen(c), 0) < 0)
        {
            assert(false);
            break;
        }
        char recvBuffer[256 + 1] = { 0 };
        int recvLen = recv(s, recvBuffer, 256, 0);
        if (recvLen < 0)
        {
            assert(false);
            break;
        }
        recvBuffer[recvLen] = '\0';
        printf("recvAck=%s\n", recvBuffer);
    } while (false);
}

void startClient4(const std::string& address)
{
    SOCKET s = INVALID_SOCKET;
    do
    {
        if ((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in addr = { 0 };
        addr.sin_family = AF_INET;
        addr.sin_port = htons(LISTEN_PORT);
        /*if (address.empty())
        {
            addr.sin_addr.s_addr = INADDR_ANY;
        }
        else*/
        {
            if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) <= 0)
            {
                assert(false);
                break;
            }
        }
        if (connect(s, (const sockaddr*)&addr, sizeof(addr)) < 0)
        {
            assert(false);
            break;
        }
        char c[] = "hello, world";
        if (send(s, c, strlen(c), 0) < 0)
        {
            assert(false);
            break;
        }
        char recvBuffer[256 + 1] = { 0 };
        int recvLen = recv(s, recvBuffer, 256, 0);
        if (recvLen < 0)
        {
            assert(false);
            break;
        }
        recvBuffer[recvLen] = '\0';
        printf("recvAck=%s\n", recvBuffer);
    } while (false);
}

//-s -c -a address
int main(int argc, char* argv[])
{
    initSocket();

    bool isServer = false;
    bool is6 = false;
    std::string address;
    int ch = 0;
    //extern char* optarg; 选项的参数
    //extern int optind;  下一个检索位置
    //extern int opterr;是否将错误信息输出到stderr
    //extern int optopt;不在选项字符串optstring中的选项
    //一个冒号就表示这个选项后面必须带有参数,有无空格均可
    //两个冒号的就表示这个选项的参数是可选的,参数与选项之间不能有空格
    opterr = 1;
    while ((ch = getopt(argc, argv, "a:s:c:")) != -1)
    {
        switch (ch)
        {
        case 'a':
        {
            address = optarg;
            break;
        }
        case 's':
        {
            isServer = true;
            if (strcmp(optarg, "6") == 0)
            {
                is6 = true;
            }
            break;
        }
        case 'c':
        {
            isServer = false;
            if (strcmp(optarg, "6") == 0)
            {
                is6 = true;
            }
            break;
        }
        default:
        {
            assert(false);
            break;
        }
        }
    }
   
    if (isServer)
    {
        if (is6)
        {
            startServer6(address);
        }
        else
        {
            startServer4(address);
        }
    }
    else
    {
        if (is6)
        {
            startClient6(address);
        }
        else
        {
            startClient4(address);
        }
    }
    getchar();

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
