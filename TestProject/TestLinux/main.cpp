#include <cstdio>
#include <type_traits>
#include <stdlib.h>
#include <unistd.h>//read,close
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>//sockaddr_un
#include <arpa/inet.h>//sockaddr_in
#include <errno.h>//errno
#include <signal.h>
#include <netdb.h>
#include <sys/ioctl.h>//ioctl
#include <net/if.h>//ifreq
#include <netinet/if_ether.h>//ethhdr结构
#include <net/if.h>//ifreq结构
#include <netinet/in.h>//in_addr结构
#include <netinet/ip.h>//iphdr结构
#include <netinet/udp.h>//udphdr结构
#include <netinet/tcp.h>//tcphdr结构
#include <linux/if_packet.h>//sockaddr_ll
//#include <linux/filter.h>
//#include <arpa/inet.h> 
#include <vector>
#include <map>
#include <algorithm>
#include "TestLinux.h"

template < typename T, size_t N >
size_t _countof(T(&arr)[N])
{
	return std::extent< T[N] >::value;
}
extern int errno;
#define MY_SOCK_PATH "/home/test/mysockpath"
#define BACKLOG 5
#define MY_PORT 5617
#define MY_IPADDRESS "127.0.0.1"

#define MY_UDP_PORT 5618

void client_process(int fd)
{
	int recvlen = -1;
	char buf[64] = { 0 };
	do
	{
		printf("client write %s\n", "1");
		if (-1 == write(fd, "1", 1))
		{
			printf("client_process write errno=%d\n", errno);
			break;
		}
#if 0
		break;
#endif
		if (-1 == (recvlen = read(fd, buf, sizeof(buf))))
		{
			printf("client_process read errno=%d\n", errno);
			break;
		}
		printf("client recv %s\n", buf);
		printf("client write %s\n", "0");
		if (-1 == write(fd, "0", 1))
		{
			printf("client_process write errno=%d\n", errno);
			break;
		}
	} while (false);
}

void server_process(int fd)
{
	char buf[64] = { 0 };
	int len = -1, ret = -1;
	bool bContinue = true;
	fd_set rd = { 0 };
	timeval tv = { 0 };
	while (bContinue)
	{
		FD_ZERO(&rd);
		FD_SET(fd, &rd);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		ret = select(fd + 1, &rd, nullptr, nullptr, &tv);
		if (-1 == ret)
		{
			printf("server_process select error=%d\n", errno);
			break;
		}
		else if (0 == ret)
		{
			printf("server_process select timeout\n");
			continue;
		}
		else if (!FD_ISSET(fd, &rd))
		{
			printf("server_process FD_ISSET error=%d\n", errno);
			break;
		}
		else
		{
			printf("server_process select read\n");
		}
		//len = read(fd, buf, sizeof(buf));
		len = recv(fd, buf, sizeof(buf), 0);
		if (-1 == len)
		{
			printf("server_process recv -1\n");
			break;
		}
		else if (0 == len)
		{
			printf("server_process recv 0\n");
			break;
		}
#if 0
		else
		{
			for (;;)
			{
				printf("before write\n");
				if (-1 == write(fd, "1", 1))
				{
					printf("server_process write failed\n");
					return;
				}
				printf("after write\n");
				sleep(1);
			}
		}
#endif
		printf("server recv %s\n", buf);
		switch (atoi(buf))
		{
		case 1:
			printf("service write %s\n", "1");
			write(fd, "1", 1);
			break;
		case 0:
		default:
			bContinue = false;
			break;
		}
	}
}

void service_accept(int fd, int domain, int type, int protocol)
{
	int acp = -1;
	sockaddr *addr = nullptr;
	socklen_t addrlen = -1, addralloclen = -1;
	char ipaddress[INET_ADDRSTRLEN] = { 0 };

	if (AF_UNIX == domain
		&& SOCK_STREAM == type)
	{
		addralloclen = sizeof(sockaddr_un);
		addr = (sockaddr*)malloc(addralloclen);
	}
	else if (AF_INET == domain
		&& SOCK_STREAM == type)
	{
		addralloclen = sizeof(sockaddr_in);
		addr = (sockaddr*)malloc(addralloclen);
	}
	else
	{
		printf("service_accept unknown domain\n");
		return;
	}
	memset(addr, 0, addralloclen);
	int pid = -1;
	while (true)
	{
		addrlen = addralloclen;
		if (-1 == (acp = accept(fd, addr, &addrlen)))
		{
			printf("service_accept accept errno=%d\n", errno);
			break;
		}
		printf("service accept\n");
		if (AF_INET == domain
			&& SOCK_STREAM == type)
		{
			sockaddr_in *addr_in = (sockaddr_in*)addr;
			if (nullptr != inet_ntop(domain, &(addr_in->sin_addr), ipaddress, sizeof(ipaddress)))
			{
				printf("service_accept client address=%s port=%d\n", ipaddress, (int)ntohs(addr_in->sin_port));
			}
			else
			{
				printf("service_accept inet_ntop error=%d\n", errno);
			}
		}
		pid = fork();
		if (-1 == pid)
		{
			printf("service_accept fork errno=%d\n", errno);
			break;
		}
		else if (0 == pid)
		{
			server_process(acp);
			printf("service accept close\n");
			if (-1 == close(acp))
			{
				printf("service_accept close error=%d\n", errno);
			}
			acp = -1;
			break;
		}
		else
		{
			if (-1 == close(acp))
			{
				printf("service_accept close error=%d\n", errno);
			}
			acp = -1;
		}
	}
	if (nullptr != addr)
	{
		free(addr);
		addr = nullptr;
	}
}

void connect_unix_stream()
{
	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	sockaddr_un addr = { 0 };

	do
	{
		if (-1 == sfd)
		{
			printf("connect_unix_stream socket errno=%d\n", errno);
			break;
		}
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, MY_SOCK_PATH, _countof(addr.sun_path));
		if (-1 == connect(sfd, (sockaddr*)&addr, sizeof(addr)))
		{
			printf("connect_unix_stream connect errno=%d\n", errno);
			break;
		}
		client_process(sfd);
	} while (false);
	if (-1 != sfd)
	{
		if (-1 == close(sfd))
		{
			printf("connect_unix_stream close error=%d\n", errno);
		}
		sfd = -1;
	}
	printf("client close\n");
}

void test_unix_stream()
{
	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	sockaddr_un addr = { 0 };

	do
	{
		signal(SIGPIPE, SIG_IGN);
		if (-1 == sfd)
		{
			printf("test_unix_stream socket errno=%d\n", errno);
			break;
		}
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, MY_SOCK_PATH, _countof(addr.sun_path));
		if (-1 == bind(sfd, (sockaddr*)&addr, sizeof(addr)))
		{
			printf("test_unix_stream bind errno=%d\n", errno);
			break;
		}
		if (-1 == listen(sfd, BACKLOG))
		{
			printf("test_unix_stream listen errno=%d\n", errno);
			break;
		}
		int pid = fork();
		if (-1 == pid)
		{
			printf("test_unix_stream fork errno=%d\n", errno);
			break;
		}
		else if (0 == pid)
		{
			close(sfd);
			sfd = -1;
			connect_unix_stream();
		}
		else
		{
			service_accept(sfd, AF_UNIX, SOCK_STREAM, 0);
		}
	} while (false);
	if (-1 != sfd)
	{
		if (-1 == close(sfd))
		{
			printf("test_unix_stream close error=%d\n", errno);
		}
		sfd = -1;
	}
	unlink(MY_SOCK_PATH);
}

void connect_inet_stream()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr = { 0 }, localaddr = { 0 };
	socklen_t addrlen = sizeof(localaddr);
	char ipaddress[INET_ADDRSTRLEN] = { 0 };

	do
	{
		if (-1 == sfd)
		{
			printf("connect_inet_stream socket errno=%d\n", errno);
			break;
		}
		addr.sin_family = AF_INET;
		addr.sin_port = htons(MY_PORT);
		addr.sin_addr.s_addr = inet_addr(MY_IPADDRESS);
		if (-1 == connect(sfd, (sockaddr*)&addr, sizeof(addr)))
		{
			printf("connect_inet_stream connect errno=%d\n", errno);
			break;
		}
		if (-1 == getsockname(sfd, (sockaddr*)&localaddr, &addrlen))
		{
			printf("connect_inet_stream getsockname errno=%d\n", errno);
			break;
		}
		if (nullptr != inet_ntop(AF_INET, &(localaddr.sin_addr), ipaddress, sizeof(ipaddress)))
		{
			printf("connect_inet_stream client address=%s port=%d\n", ipaddress, (int)ntohs(localaddr.sin_port));
		}
		else
		{
			printf("connect_inet_stream inet_ntop error=%d\n", errno);
		}

		client_process(sfd);
	} while (false);
	if (-1 != sfd)
	{
		if (-1 == shutdown(sfd, SHUT_RDWR))
		{
			printf("connect_unix_stream shutdown error=%d\n", errno);
		}
		sfd = -1;
	}
	printf("connect_unix_stream client shutdown\n");
}

void test_inet_stream()
{
	int sfd = -1;
	sockaddr_in addr = { 0 };

	do
	{
		signal(SIGPIPE, SIG_IGN);
		if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0)))
		{
			printf("test_inet_stream socket errno=%d\n", errno);
			break;
		}
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(MY_PORT);
		if (-1 == bind(sfd, (const sockaddr*)&addr, sizeof(addr)))
		{
			printf("test_inet_stream bind errno=%d\n", errno);
			break;
		}
		if (-1 == listen(sfd, BACKLOG))
		{
			printf("test_inet_stream listen errno=%d\n", errno);
			break;
		}
		int pid = fork();
		if (-1 == pid)
		{
			printf("test_inet_stream fork errno=%d\n", errno);
			break;
		}
		else if (0 == pid)
		{
			close(sfd);
			sfd = -1;
			connect_inet_stream();
		}
		else
		{
			service_accept(sfd, AF_INET, SOCK_STREAM, 0);
		}
	} while (false);
	if (-1 != sfd)
	{
		if (-1 == close(sfd))
		{
			printf("test_inet_stream close error=%d\n", errno);
		}
		sfd = -1;
	}
}

void print_hostent(hostent *host)
{
	char ipaddress[INET_ADDRSTRLEN] = { 0 };
	if (nullptr != host)
	{
		printf("print_hostent gethostbyname h_name:%s\n", host->h_name);
		for (char **pptr = host->h_aliases; nullptr != *pptr; pptr++)
		{
			printf("print_hostent gethostbyname h_aliases:%s\n", *pptr);
		}
		if (AF_INET == host->h_addrtype)
		{
			for (char **pptr = host->h_addr_list; nullptr != *pptr; pptr++)
			{
				if (nullptr != inet_ntop(host->h_addrtype, *pptr, ipaddress, sizeof(ipaddress)))
				{
					printf("print_hostent gethostbyname h_addr_list:%s\n", ipaddress);
				}
				else
				{
					printf("print_hostent inet_ntop error=%d\n", errno);
				}
			}
		}
	}
	else
	{
		printf("print_hostent gethostbyname error=%d\n", errno);
	}
}

void test_dns()
{
	hostent *host = gethostbyname("www.baidu.com");
	print_hostent(host);

	in_addr addr = { 0 };
	int ret = inet_pton(AF_INET, "61.135.169.125", &addr);
	char ipaddress[INET_ADDRSTRLEN] = { 0 };
	inet_ntop(AF_INET, &addr, ipaddress, sizeof(ipaddress));
	if (1 == ret)
	{
		static_assert(sizeof(addr) == 4, "");
		host = gethostbyaddr(&addr, sizeof(addr), AF_INET);
		print_hostent(host);
	}
	else if (0 == ret)
	{
		printf("test_dns inet_pton not ipv4 maybe ipv6\n");
	}
	else
	{
		printf("test_dns inet_pton error=%d\n", errno);
	}
}

void test_udp()
{
	int s = -1;
	char *buf = nullptr;
	sockaddr_in addr_ser, addr_client;
	int recvLen = 0;
	socklen_t sockLen = sizeof(addr_client);

	do
	{
		int bufLen = 65535;
		buf = (char*)malloc(bufLen);
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			printf("test_udp socket errno=%d\n", errno);
			break;
		}
		addr_ser.sin_family = AF_INET;
		addr_ser.sin_addr.s_addr = htonl(INADDR_ANY);
		addr_ser.sin_port = htons(MY_UDP_PORT);
		if (bind(s, (sockaddr*)&addr_ser, sizeof(addr_ser)) < 0)
		{
			printf("test_udp bind errno=%d\n", errno);
			break;
		}
		while (true)
		{
			sockLen = sizeof(addr_client);
			if ((recvLen = recvfrom(s, buf, bufLen, 0, (sockaddr*)&addr_client, &sockLen)) < 0)
			{
				printf("test_udp recvfrom errno=%d\n", errno);
				break;
			}
			buf[bufLen - 1] = '\0';
			printf("test_udp %s\n", buf);
			if (sendto(s, "abc", 3, 0, (sockaddr*)&addr_client, sizeof(addr_client)) < 0)
			{
				printf("test_udp sendto errno=%d\n", errno);
				break;
			}
		}
	} while (false);
	free(buf);
	buf = nullptr;
}

void test_broad()
{
	int s = -1;
	char *buf = nullptr;
	sockaddr_in addr_broad, addr_recv;
	int recvLen = 0;
	socklen_t sockLen = sizeof(addr_recv);
	ifreq ifr;
	int so_broadcast = 1;

	do
	{
		int bufLen = 65535;
		buf = (char*)malloc(bufLen);
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			printf("test_broad socket errno=%d\n", errno);
			break;
		}
		strcpy(ifr.ifr_name, "ens33");
		if (ioctl(s, SIOCGIFBRDADDR, &ifr) == -1)
		{
			printf("test_broad ioctl errno=%d\n", errno);
			break;
		}
		memcpy(&addr_broad, &ifr.ifr_broadaddr, sizeof(addr_broad));
		addr_broad.sin_port = htons(MY_UDP_PORT);
		if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast)) < 0)
		{
			printf("test_broad setsockopt errno=%d\n", errno);
			break;
		}
		if (sendto(s, "hello", 5, 0, (sockaddr*)&addr_broad, sizeof(addr_broad)) < 0)
		{
			printf("test_broad sendto errno=%d\n", errno);
			break;
		}
		sockLen = sizeof(addr_recv);
		if ((recvLen = recvfrom(s, buf, bufLen, 0, (sockaddr*)&addr_recv, &sockLen)) < 0)
		{
			printf("test_broad recvfrom errno=%d\n", errno);
			break;
		}
		buf[bufLen - 1] = '\0';
		printf("test_udp %s\n", buf);
	} while (false);
	if (-1 != s)
	{
		if (-1 == close(s))
		{
			printf("test_broad close error=%d\n", errno);
		}
		s = -1;
	}
	free(buf);
	buf = nullptr;
}

std::string format_hardware_address(unsigned char(&hardware_address)[ETH_ALEN])
{
	std::string strText;
	char sztemp[8];
	for (int i = 0; i < ETH_ALEN - 1; i++)
	{
		sprintf(sztemp, "%02x-", hardware_address[i]);
		strText += sztemp;
	}
	sprintf(sztemp, "%02x  ", hardware_address[ETH_ALEN - 1]);
	strText += sztemp;
	return strText;
}

void print_iphdr(const char *buf, int len);
void printf_arp(const char *buf, int len);
void print_ethhdr(const char *buf, int len)
{
	if (len < sizeof(ethhdr))
	{
		printf("print_ethhdr len failed\n");
		return;
	}
	ethhdr hdr;
	memcpy(&hdr, buf, sizeof(hdr));
	printf("dest MAC:%s ", format_hardware_address(hdr.h_dest).c_str());

	printf("source MAC:%s ", format_hardware_address(hdr.h_source).c_str());
	
	int proto = (int)ntohs(hdr.h_proto);
	printf("protocol:0x%04x", proto);
	printf("\n");
	
	switch (proto)
	{
	case ETH_P_IP:
	{
		printf("\tETH_P_IP ");
		print_iphdr(buf + ETH_HLEN, len - ETH_HLEN);
		break;
	}
	case ETH_P_ARP:
	{
		printf("\t ETH_P_ARP ");
		printf_arp(buf + ETH_HLEN, len - ETH_HLEN);
		break;
	}
	default:
	{
		break;
	}
	}
}

void print_tcp(const char *buf, u_int16_t len)
{
	tcphdr hdr;
	memcpy(&hdr, buf, sizeof(hdr));
	u_int16_t hdrlen = hdr.doff * 4;
	printf("source:%hu dest:%hu seq:%u ack_seq:%u hdrlen:%d bytes datalen:%hu ", ntohs(hdr.source), ntohs(hdr.dest), ntohl(hdr.seq), ntohl(hdr.ack_seq), hdrlen, len - hdrlen);
	printf("syn:%d fin:%d rst:%d ack:%d psh:%d ", (int)hdr.syn, (int)hdr.fin, (int)hdr.rst, (int)hdr.ack, (int)hdr.psh);
	printf("window:%hu ", hdr.window);
	printf("\n");
}

void print_udp(const char *buf)
{
	udphdr hdr;
	memcpy(&hdr, buf, sizeof(hdr));
	u_int16_t totallen = ntohs(hdr.len);
	u_int16_t datalen = totallen - sizeof(udphdr);
	printf("source:%hu dest:%hu totallen:%hu datalen:%hu \n", ntohs(hdr.source), ntohs(hdr.dest), totallen, datalen);
}

struct ip_frame
{
	int offset;//bytes
	std::string strData;
	
	ip_frame()
		: offset(0)
		, strData()
	{

	}
};
struct ip_packet
{
	int totalLen;
	int curLen;
	std::vector<ip_frame> frames;
	ip_packet()
		: totalLen(0)
		, curLen(0)
		, frames()
	{

	}
};

std::string make_ip_key(u_int16_t id, u_int32_t saddr, u_int32_t daddr, u_int8_t protocol)
{
	std::string str;
	str.append((char*)&id, sizeof(id));
	str.append((char*)&saddr, sizeof(saddr));
	str.append((char*)&daddr, sizeof(daddr));
	str.append((char*)&protocol, sizeof(protocol));
	return str;
}

void print_iphdr(const char *buf, int len)
{
	if (len < sizeof(iphdr))
	{
		printf("print_iphdr len failed\n");
		return;
	}

	iphdr hdr;
	memcpy(&hdr, buf, sizeof(hdr));

	int hdrlen = ((int)hdr.ihl) * 4;
	int tot_len = ntohs(hdr.tot_len);
	int frag_off = ntohs(hdr.frag_off);
	int df = (frag_off & IP_DF) ? 1 : 0;
	int mf = (frag_off & IP_MF) ? 1 : 0;
	int offset = (frag_off & IP_OFFMASK) * 8;
	int datalen = tot_len - hdrlen;
	printf("header id:%d hdrlen:%d bytes version:%d len:%d df:%d mf:%d frag_off:%d bytes ttl:%d ", ntohs(hdr.id), hdrlen, (int)hdr.version, tot_len, df, mf, offset, hdr.ttl);

	char saddr[INET_ADDRSTRLEN] = { 0 };
	char daddr[INET_ADDRSTRLEN] = { 0 };
	inet_ntop(AF_INET, (sockaddr*)&hdr.saddr, saddr, sizeof(saddr));
	inet_ntop(AF_INET, (sockaddr*)&hdr.daddr, daddr, sizeof(daddr));
	printf("saddr:%s daddr:%s \n", saddr, daddr);
	switch (hdr.protocol)
	{
	case IPPROTO_TCP:
	{
		printf("\t\tIPPROTO_TCP ");
		print_tcp(buf + hdrlen, len - hdrlen);
		break;
	}
	case IPPROTO_UDP:
	{
		printf("\t\tIPPROTO_UDP ");
		if (frag_off & (IP_MF | IP_OFFMASK))
		{
			static std::map<std::string, ip_packet> cachePacket;
			std::string key = make_ip_key(hdr.id, hdr.saddr, hdr.daddr, hdr.protocol);
			auto &packet = cachePacket[key];
			if (0 == mf)
			{
				packet.totalLen = offset + datalen;
			}
			
			ip_frame frame;
			frame.offset = offset;
			frame.strData.append(buf + hdrlen, datalen);
			packet.frames.push_back(frame);
			packet.curLen += datalen;

			if (0 != packet.totalLen
				&& packet.curLen >= packet.totalLen)
			{
				std::sort(packet.frames.begin(), packet.frames.end(), 
					[](const ip_frame &l, const ip_frame &r)->bool 
					{
						return l.offset < r.offset;
					});
				std::string strData;
				for (auto &frame : packet.frames)
				{
					strData.append(frame.strData);
				}
				print_udp(strData.data());
				printf("frame totallen:%d\n", (int)strData.size());
				cachePacket.erase(key);
			}
			else
			{
				printf(" frame\n");
			}
		}
		else
		{
			print_udp(buf + hdrlen);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}

struct arppacket
{
	unsigned char		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char		ar_sip[4];		/* sender IP address		*/
	unsigned char		ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char		ar_tip[4];		/* target IP address		*/
};
void printf_arp(const char *buf, int len)
{
	arphdr hdr;
	memcpy(&hdr, buf, sizeof(hdr));
	//ARPHRD_ETHER=1
	//ETH_P_IP=0x0800
	//ARPOP_REQUEST=1
	printf("ar_hrd:%hu ar_pro:%hu ar_hln:%d ar_pln:%d ar_op:%hu ", ntohs(hdr.ar_hrd), ntohs(hdr.ar_pro), (int)hdr.ar_hln, (int)hdr.ar_pln, ntohs(hdr.ar_op));
	arppacket packet;
	memcpy(&packet, buf + sizeof(arphdr), sizeof(arppacket));
	char souceIP[INET_ADDRSTRLEN];
	char destIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, packet.ar_sip, souceIP, sizeof(souceIP));
	inet_ntop(AF_INET, packet.ar_tip, destIP, sizeof(destIP));
	printf("souceMAC:%s souceIP:%s destMAC:%s destIP:%s ", format_hardware_address(packet.ar_sha).c_str(), souceIP,
		format_hardware_address(packet.ar_tha).c_str(), destIP);
	printf("\n");
}

void test_packet()
{
	int sock = -1;
	sockaddr_ll addr;
	do
	{
		if ((sock = socket(PF_PACKET, SOCK_RAW, htons(/*ETH_P_IP | ETH_P_ARP | */ETH_P_ALL))) == -1)
		{
			printf("test_packet socket errno=%d\n", errno);
			break;
		}
		addr.sll_ifindex = if_nametoindex("ens33");
		addr.sll_family = AF_PACKET;
		addr.sll_protocol = htons(ETH_P_ALL);
		if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1)
		{
			printf("test_packet bind errno=%d\n", errno);
			break;
		}
		//setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf))
		//ifreq ifr;
		//strcpy(ifr.ifr_name, "ens33");
		//if (ioctl(fd, SIOCGIFFLAGS, &ifr) == -1)
		//{
		//	printf("test_packet ioctl errno=%d\n", errno);
		//	break;
		//}
		//ifr.ifr_flags |= IFF_PROMISC;//加入混杂模式
		//if (ioctl(fd, SIOCSIFFLAGS, &ifr))
		//{
		//	printf("test_packet ioctl errno=%d\n", errno);
		//	break;
		//}
		while (true)
		{
			char ef[ETH_FRAME_LEN];
			int len = read(sock, ef, ETH_FRAME_LEN);
			print_ethhdr(ef, len);
		}
	} while (false);
}

void test_norecv()
{
	int sfd = -1;
	sockaddr_in addr = { 0 };

	do
	{
		signal(SIGPIPE, SIG_IGN);
		if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0)))
		{
			printf("test_inet_stream socket errno=%d\n", errno);
			break;
		}
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(MY_PORT);
		if (-1 == bind(sfd, (const sockaddr*)&addr, sizeof(addr)))
		{
			printf("test_inet_stream bind errno=%d\n", errno);
			break;
		}
		if (-1 == listen(sfd, BACKLOG))
		{
			printf("test_inet_stream listen errno=%d\n", errno);
			break;
		}
		while (true)
		{
			sockaddr_in acceptAddr;
			socklen_t acceptAddrLen = sizeof(acceptAddr);
			int acp = accept(sfd, (sockaddr*)&acceptAddr, &acceptAddrLen);
			shutdown(acp, SHUT_RD);
			linger optval;
			optval.l_onoff = 1;
			optval.l_linger = 0;
			if (-1 == setsockopt(acp, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval)))
			{
				printf("test_inet_stream setsockopt errno=%d\n", errno);
				break;
			}
			close(acp);
		}
	} while (false);
	if (-1 != sfd)
	{
		if (-1 == close(sfd))
		{
			printf("test_inet_stream close error=%d\n", errno);
		}
		sfd = -1;
	}

}

int main()
{
	//test_unix_stream();
	//test_inet_stream();
	//test_udp();
	//test_broad();
	if (0 == fork())
		test_norecv();
	else 
		test_packet();
	
    return 0;
}