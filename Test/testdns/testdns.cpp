// testdns.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <regex>
#ifdef WIN32
#include <WinSock2.h>
#include <ws2ipdef.h> //sockaddr_in6
#include <WS2tcpip.h> //inet_pton
#undef _UNICODE
//#include "getopt.h"
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

#define DNS_PORT 53

#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321

#define __BYTE_ORDER __LITTLE_ENDIAN
struct DNSHeader
{
    uint16_t ID;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t RD : 1;//可选项，1：DNS解析器要求DNS服务器使用递归查询
    uint8_t TC : 1;//代表截断标记，如果报文长度比传输通道所允许的长而被分段，设置为1
    uint8_t AR : 1; //应答时才设置.1正应答的域名服务器市所查询域名的管理机构或者说是被授权的域名服务器
    uint8_t OPCODE : 4;//0:标准查询,1:逆向查询,2:查询服务器状态,3:保留,4通知,5更新报文
    uint8_t QR : 1; //0:请求,1:应答

    uint8_t RCODE : 4;//应答时设置，指明是否发生了错误，0：无错误，1：格式错误，DNS服务器不能解释应答，2：严重错误，因为名字服务器上发生了一个错误，DNS服务器不能处理查询，3：名字错误，如果DNS应答来自授权服务器，意味着DNS请求提到的名字不存在，4：没有实现，DNS服务器不支持这种DNS请求报文,5:拒绝，由于安全或策略，DNS名字服务器拒绝处理请求，6~15保留
    uint8_t Z : 3;//0
    uint8_t RA : 1;//代表正在应答的域名服务器可以执行递归查询，该字段与查询段无关
#else
    uint8_t QR:1; //0:请求,1:应答
    uint8_t OPCODE : 4;//0:标准查询,1:逆向查询,2:查询服务器状态,3:保留,4通知,5更新报文
    uint8_t AR : 1;
    uint8_t TC : 1;
    uint8_t RD : 1;

    uint8_t RA : 1;
    uint8_t Z : 3;
    uint8_t RCODE : 4;
#endif
    uint16_t QuestionCount;
    uint16_t AnswerCount;
    uint16_t AuthorityCount;
    uint16_t AdditionalCount;
};

struct DNSData
{
    //name
    //type
    //class
};
uint16_t read16(const char*& pBuffer)
{
    uint16_t retType = 0;
    memcpy(&retType, pBuffer, sizeof(retType));
    retType = ntohs(retType);
    pBuffer += sizeof(retType);
    return retType;
}

uint32_t read32(const char*& pBuffer)
{
    uint32_t retType = 0;
    memcpy(&retType, pBuffer, sizeof(retType));
    retType = ntohl(retType);
    pBuffer += sizeof(retType);
    return retType;
}
int parseName(const char* pName, std::vector<std::string> &names)
{
    int totalLen = 0;
    while (true)
    {
        uint8_t len = 0;
        memcpy(&len, pName, sizeof(len));
        totalLen++;
        if (0 == len)
        {
            break;
        }
        pName++;
        names.push_back(std::string(pName, len));
        pName += len;
        totalLen += len;
    }
    return totalLen;
}

void parseName2(const char* pBegin, const char* pName, std::vector<std::string>& names, int buflen)
{
    int totalLen = 0;
    while (true)
    {
        uint8_t len = 0;
        memcpy(&len, pName, sizeof(len));
        if (0 != (len & 0xC0))
        {
            //use offset
            uint16_t offset = read16(pName);
            offset = offset & 0x3fff;
            const char* pTmpName = pBegin + offset;
            memcpy(&len, pTmpName, sizeof(len));
            pTmpName++;
            names.push_back(std::string(pTmpName, len));
            totalLen += 2;
        }
        else
        {
            pName++;
            totalLen++;
            names.push_back(std::string(pName, len));
            pName += len;
            totalLen += len;
        }
        if (totalLen >= buflen)
        {
            break;
        }
    }
}

int parseQuestion(const char* pBegin, const char* pTmpCur)
{
    const char* pCur = pTmpCur;
    uint8_t rname0 = 0;
    memcpy(&rname0, pCur, sizeof(rname0));
    bool useOffset = (0 != (rname0 & 0xC0));
    const char* pName = nullptr;
    if (useOffset)
    {
        uint16_t offset = 0;
        memcpy(&offset, pCur, sizeof(offset));
        offset = ntohs(offset);
        offset = offset & 0x3fff;
        pName = pBegin + offset;
    }
    else
    {
        pName = pCur;
    }

    std::vector<std::string> resultName;
    int namelen = parseName(pName, resultName);
    if (useOffset)
    {
        pCur += 2;
    }
    else
    {
        pCur += namelen;
    }
    uint16_t retType = read16(pCur);
    uint16_t retClass = read16(pCur);
    return pCur - pTmpCur;
}

int parseAnswer(const char* pBegin, const char* pTmpCur)
{
    const char* pCur = pTmpCur;
    uint8_t rname0 = 0;
    memcpy(&rname0, pCur, sizeof(rname0));
    bool useOffset = (0 != (rname0 & 0xC0));
    const char* pName = nullptr;
    if (useOffset)
    {
        uint16_t offset = 0;
        memcpy(&offset, pCur, sizeof(offset));
        offset = ntohs(offset);
        offset = offset & 0x3fff;
        pName = pBegin + offset;
    }
    else
    {
        pName = pCur;
    }

    std::vector<std::string> resultName;
    int namelen = parseName(pName, resultName);
    if (useOffset)
    {
        pCur += 2;
    }
    else
    {
        pCur += namelen;
    }
    uint16_t retType = read16(pCur);
    uint16_t retClass = read16(pCur);
    uint32_t ttl = read32(pCur);
    uint16_t datalen = read16(pCur);
    if (retType == 1)
    {
        in_addr ip = {0};
        memcpy(&ip, pCur, sizeof(ip));
        char buffer[16] = { 0 };
        inet_ntop(PF_INET, &ip, buffer, 16);
        //std::string sip = inet_ntoa(ip);
        assert(0 != strlen(buffer));
    }
    else if (5 == retType)
    {
        std::vector<std::string> tmpNames;
        parseName2(pBegin, pCur, tmpNames, datalen);
        assert(!tmpNames.empty());
    }
    pCur += datalen;
    return pCur - pTmpCur;
}

sockaddr_in getDNS(const std::string& url) 
{
    SOCKET s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    do
    {
        if (INVALID_SOCKET == s)
        {
            assert(false);
            break;
        }
        sockaddr_in addrDNS;
        addrDNS.sin_family = AF_INET;
        addrDNS.sin_port = htons(DNS_PORT);
        //出错返回负值,协议与字符串不匹配则返回0
        if (inet_pton(PF_INET, "192.168.3.1", &addrDNS.sin_addr) <= 0)
        {
            assert(false);
            break;
        }
        DNSHeader header = { 0 };
        header.ID = 123456;
        header.QR = 0;
        header.OPCODE = 1;
        header.AR = 0;
        header.TC = 0;
        header.RD = 1;
        header.Z = 0;
        header.RCODE = 0;

        header.QuestionCount = htons(1);

        std::string data;
        std::regex expr("\\.");
        std::sregex_token_iterator itorToken(url.begin(), url.end(), expr, -1);
        std::sregex_token_iterator itorTokenEnd;

        while (itorToken != itorTokenEnd)
        {
            std::string strSubText = *itorToken;
            ++itorToken;
            uint8_t len = strSubText.size();
            data.append((char*)&len, sizeof(len));
            data.append(strSubText);
        }
        data += ('\0');
        uint16_t type = htons(1);
        uint16_t cls = htons(1);
        data.append((char*)&type, sizeof(type));
        data.append((char*)&cls, sizeof(cls));

        std::string buffer;
        buffer.append((char*)&header, sizeof(header));
        buffer.append(data);
        if (sendto(s, buffer.data(), buffer.size(), 0, (sockaddr*)&addrDNS, sizeof(addrDNS)) < buffer.size())
        {
            assert(false);
            break;
        }
        char recvData[1024] = { 0 };
        sockaddr_in recvAddr = { 0 };
        int recvAddrLen = sizeof(recvAddr);
        int recvLen = recvfrom(s, recvData, 1024, 0, (sockaddr*)&recvAddr, &recvAddrLen);
        if (recvLen <= 0) 
        {
            assert(false);
            break;
        }
        DNSHeader resultHeader = { 0 };
        memcpy(&resultHeader, recvData, sizeof(resultHeader));
        uint8_t RCODE = resultHeader.RCODE;
        if (RCODE != 0)
        {
            assert(false);
            break;
        }
        const char *pBegin = recvData;
        const char* pCurData = recvData + sizeof(resultHeader);
        int QuestionCount = ntohs(resultHeader.QuestionCount);
        int AnswerCount = ntohs(resultHeader.AnswerCount);
        for (int i = 0; i < QuestionCount; i++)
        {
            int len = parseQuestion(pBegin, pCurData);
            pCurData += len;
        }
        for (int i = 0; i < AnswerCount; i++)
        {
            int len = parseAnswer(pBegin, pCurData);
            pCurData += len;
        }
    } while (false);
    if (INVALID_SOCKET != s)
    {
        closesocket(s);
    }
    return sockaddr_in();
}

int main()
{
    initSocket();

    auto addr = getDNS("www.baidu.com");

    cleanSocket();
    std::cout << "Hello World!\n";
}
