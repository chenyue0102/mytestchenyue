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
#define MDNS_PORT 5353

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

enum EDNS_TYPE
{
    EDNS_TYPE_A = 1,  //由域名获得IPv4地址
    EDNS_TYPE_NS = 2, //查询域名服务器
    EDNS_TYPE_CNAME = 5,//查询规范名称
    EDNS_TYPE_SOA = 6,    //开始授权
    EDNS_TYPE_WKS = 11,  //熟知服务
    EDNS_TYPE_PTR = 12,  //把IP地址转换成域名
    EDNS_TYPE_HINFO = 13,    //主机信息
    EDNS_TYPE_MX = 15,   //邮件交换
    EDNS_TYPE_AAAA = 28, //由域名获得IPv6地址
    EDNS_TYPE_AXFR = 252,    //传送整个区的请求
    EDNS_TYPE_ANY = 255, //对所有记录的请求
};

enum EDNS_CLASS
{
    EDNS_CLASS_IN = 1,
    EDNS_CLASS_QU = 0x8000,//mDNS,单播相应,在设备刚启动时,查询应该使用QU,防止网络负担,正常运行后,使用QM。冲突探测包，使用QU
};
//如果自己是唯一可能回复的服务端，则回复不需要等待
struct QueryInfo
{
    std::vector<std::string> names;
    uint16_t type;
    uint16_t clazz;
};
//PTR
void getDNS(SOCKET s, const sockaddr_in &addrSend, const std::vector<QueryInfo> &info)
{
    do
    {
        DNSHeader header = { 0 };
        //header.ID = 123456;
        header.ID = 0;
        header.QR = 0;
        header.OPCODE = 0;
        header.AR = 0;
        header.TC = 0;
        //header.RD = 1;
        header.RD = 0;
        header.Z = 0;
        header.RCODE = 0;

        header.QuestionCount = htons(info.size());

        std::string data;
        for (auto& i : info)
        {
            for (auto& name : i.names)
            {
                uint8_t len = name.size();
                data.append((char*)&len, sizeof(len));
                data.append(name);
            }
            data += ('\0');
            uint16_t type = htons(i.type);
            uint16_t cls = htons(i.clazz);
            data.append((char*)&type, sizeof(type));
            data.append((char*)&cls, sizeof(cls));
        }
        

        std::string buffer;
        buffer.append((char*)&header, sizeof(header));
        buffer.append(data);
        if (sendto(s, buffer.data(), buffer.size(), 0, (sockaddr*)&addrSend, sizeof(addrSend)) < buffer.size())
        {
            assert(false);
            break;
        }
        char recvData[65535] = { 0 };
        sockaddr_in recvAddr = { 0 };
        int recvAddrLen = sizeof(recvAddr);
        int recvLen = recvfrom(s, recvData, sizeof(recvData), 0, (sockaddr*)&recvAddr, &recvAddrLen);
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
        const char* pBegin = recvData;
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
        std::string data;
        std::regex expr("\\.");
        std::sregex_token_iterator itorToken(url.begin(), url.end(), expr, -1);
        std::sregex_token_iterator itorTokenEnd;

        std::vector<QueryInfo> infos;
        QueryInfo info;
        while (itorToken != itorTokenEnd)
        {
            std::string strSubText = *itorToken;
            ++itorToken;
            info.names.push_back(strSubText);
        }
        info.type = 1;
        info.clazz = 1;
        infos.push_back(info);
        getDNS(s, addrDNS, infos);
    } while (false);
    if (INVALID_SOCKET != s)
    {
        closesocket(s);
    }
    return sockaddr_in();
}

void getmDNS()
{
    SOCKET s = INVALID_SOCKET;

    do
    {
        s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (INVALID_SOCKET == s)
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
        sockaddr_in bindAddr;
        bindAddr.sin_family = AF_INET;
        bindAddr.sin_port = htons(MDNS_PORT);
        bindAddr.sin_addr.s_addr = INADDR_ANY;
        if (bind(s, (sockaddr*)&bindAddr, sizeof(bindAddr)) < 0)
        {
            assert(false);
            break;
        }
        ip_mreq imr = { 0 };
        inet_pton(AF_INET, "224.0.0.251", &imr.imr_multiaddr.s_addr);
        //imr.imr_multiaddr.s_addr = inet_addr("224.0.0.251");
        //imr.imr_interface.s_addr = htonl(INADDR_ANY);
        //imr.imr_interface.s_addr = ip2;
        if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&imr, sizeof(imr)) < 0)
        {
            assert(false);
            break;
        }
        sockaddr_in sendAddr;
        sendAddr.sin_family = AF_INET;
        sendAddr.sin_port = htons(MDNS_PORT);
        inet_pton(AF_INET, "224.0.0.251", &sendAddr.sin_addr);
        std::vector<QueryInfo> infos;
        QueryInfo info;
        info.names.push_back("_airplay");
        info.names.push_back("_tcp");
        info.names.push_back("local");
        info.type = EDNS_TYPE_PTR;
        info.clazz = EDNS_CLASS_IN | EDNS_CLASS_QU;
        infos.push_back(info);
        info.names.clear();
        info.names.push_back("_raop");
        info.names.push_back("_tcp");
        info.names.push_back("local");
        infos.push_back(info);
        getDNS(s, sendAddr, infos);
    } while (false);
    closesocket(s);
}

std::string sendrecv(SOCKET s, const std::string& strSend)
{
    std::string recvData;

    do
    {
        if (send(s, strSend.data(), strSend.size(), 0) < strSend.size())
        {
            assert(false);
            break;
        }
        char szBuffer[1024] = { 0 };
        int recvLen = recv(s, szBuffer, 1024, 0);
        if (recvLen <= 0)
        {
            assert(false);
            break;
        }
        recvData.append(szBuffer, recvLen);
    } while (false);
    return recvData;
}

std::string sendrecv(const std::string &ip, int port, const std::string &strSend) {
    SOCKET s = INVALID_SOCKET;
    std::string recvData;
    do
    {
        s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
        if (connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        {
            assert(false);
            break;
        }
        recvData = sendrecv(s, strSend);
    } while (false);
    closesocket(s);
    return recvData;
}

void testairplay()
{
    std::string strSend(
        "GET /server-info HTTP/1.1\r\n"
        "X-Apple-Device-ID: 0xdc2b61a0ce79\r\n"
        "Content-Length: 0\r\n"
        "User-Agent: MediaControl/1.0\r\n"
        "X-Apple-Session-ID: 1bd6ceeb-fffd-456c-a09c-996053a7a08c\r\n\r\n"
    );
    //std::string rv = sendrecv("192.168.3.7", 52244, strSend);

    std::string strPlay =
        "POST /play HTTP/1.1\r\n"
        "X-Transmit-Date: 2020-03-09T14:20:39.656533Z\r\n"
        "Content-Type: application/x-apple-binary-plist\r\n"
        "Content-Length: ";
    std::string body =
        //"<BINARY PLIST DATA>\r\n"
        //"\r\n"
        "";
    std::string body2 = R"(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0"> 
  <dict> 
    <key>Content-Location</key>  
    <string>http://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8</string>  
    <key>Start-Position</key>  
    <real>0.024613151326775551</real> 
  </dict> 
</plist>)";

    //"Content - Location : http://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8\r\n"
    //"Start - Position : 0.17";
    strPlay += std::to_string(body.size() + body2.size());;
    strPlay += "\r\n";
    strPlay += "User-Agent: MediaControl/1.0\r\n"
        "X-Apple-Session-ID: 368e90a4-5de6-4196-9e58-9917bdd4ffd7\r\n"
        "\r\n";
    strPlay += body + body2;
    std::string rv2 = sendrecv("192.168.3.7", 52244, strPlay);

    std::string seek = "POST /scrub?position=20.097000 HTTP/1.1\r\n"
        "User-Agent: iTunes / 10.6 (Macintosh; Intel Mac OS X 10.7.3) AppleWebKit / 535.18.5\r\n"
        "Content-Length : 0\r\n\r\n";
    std::string rseek = sendrecv("192.168.3.7", 52244, seek);
    //auto addr = getDNS("www.baidu.com");

    std::string playback = "GET /playback-info HTTP/1.1\r\n"
        "Content-Length: 0\r\n"
        "User-Agent : MediaControl / 1.0\r\n"
        "X-Apple-Session-ID : 24b3fd94-1b6d-42b1-89a3-47108bfbac89\r\n\r\n";
    auto rplayback = sendrecv("192.168.3.7", 52244, playback);

    std::string stop = "POST /stop HTTP / 1.1\r\n"
        "Content-Length: 0\r\n"
        "User-Agent : MediaControl / 1.0\r\n"
        "X-Apple-Session-ID : 1bd6ceeb-fffd-456c-a09c-996053a7a08c\r\n\r\n";
    std::string rstop = sendrecv("192.168.3.7", 52244, stop);
}

#define AIR_IP "192.168.3.7"
#define AIR_PORT 52244

void airplayreverse(SOCKET s)
{
    std::string req = "POST /reverse HTTP/1.1\r\n"
        "Upgrade: PTTH/1.0\r\n"
        "Connection: Upgrade\r\n"
        "X-Apple-Purpose: event\r\n"
        "X-Apple-Session-ID: cd20be3f-618f-4ff0-939b-d28ef91478b0\r\n"
        "User-Agent: AirPlayTo/1.0\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
        ;
    std::string ack = sendrecv(s, req);
    printf("%s\n", ack.c_str());
}

void airplayplay(SOCKET s)
{
    std::string req = "POST /play HTTP/1.1\r\n"
        "X-Apple-Session-ID: cd20be3f-618f-4ff0-939b-d28ef91478b0\r\n"
        "User-Agent: AirPlayTo/1.0\r\n"
        "Content-Type: text/parameters\r\n"
        "Content-Length: 126\r\n"
        "\r\n"
        ;
    std::string data = "Content-Location: https://cdn.kaishuhezi.com/mcourse/m3u8/71e5c57d-a4b2-44a4-845e-9c92bfcabeaa/index.m3u8\r\n"
        "Start-Position: 0\r\n";

    std::string ack = sendrecv(s, req + data);
    printf("%s\n", ack.c_str());
}

void testairplay2()
{
    SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(AIR_PORT);
    inet_pton(AF_INET, AIR_IP, &serverAddr.sin_addr);
    connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr));

    airplayreverse(s);
    airplayplay(s);
    char szBuffer[1024] = { 0 };
    std::string httpok = "HTTP/1.1 200 OK\r\n"
        "Server: AirTunes/220.68\r\n"
        "Content-Length: 0\r\n"
        "Date: Mon, 09 Mar 2020 14:09:12 GMT\r\n"
        "\r\n";
    while (true)
    {
        recv(s, szBuffer, 1024, 0);
        send(s, httpok.data(), httpok.size(), 0);
    }
    
}
int main()
{
    initSocket();

    testairplay2();
    getmDNS();
    cleanSocket();
    std::cout << "Hello World!\n";
}
