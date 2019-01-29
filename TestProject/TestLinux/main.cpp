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
//#include <arpa/inet.h> 
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

int main()
{
	//test_unix_stream();
	test_inet_stream();
    return 0;
}