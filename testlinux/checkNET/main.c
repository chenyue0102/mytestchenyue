#include <stdio.h>
#include <stdint.h>
#include <unistd.h>//daemon
#include <arpa/inet.h>//sockaddr_in
#include <sys/socket.h>
#include <errno.h>//errno
#include "CheckProtocol.h"



extern int errno;
void processRecvBuf(int s, const struct sockaddr_in *addr_client, int addrLen, const char *buf, int recvLen)
{
	int sendLen = 0;
	if (recvLen < sizeof(MSG_HEADER)
		|| NULL == buf
		|| NULL == addr_client)
	{
		return;
	}
	MSG_HEADER header;
	memcpy(&header, buf, sizeof(MSG_HEADER));
	uint32_t msgId = htonl(header.msgId);
	switch (msgId)
	{
	case EMsgIdQueryAddress:
	{
		MSG_QUERY_ADDRESS  msgQueryAddress = { 0 };
		msgQueryAddress.header.msgId = htonl(EMsgIdQueryAddress);
		msgQueryAddress.clientAddress = addr_client->sin_addr.s_addr;
		msgQueryAddress.clientPort = addr_client->sin_port;
		sendLen = sendto(s, &msgQueryAddress, sizeof(msgQueryAddress), 0, addr_client, addrLen);
		break;
	}
	}
}

void processCheckNET()
{
	int s = -1, sockLen = 0;
	char *buf = NULL;
	const int bufLen = 65535;
	struct sockaddr_in addr_server, addr_client;
	int recvLen = 0;

	do
	{
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		{
			break;
		}
		addr_server.sin_family = AF_INET;
		addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
		addr_server.sin_port = htons(MY_UDP_PORT);
		if (bind(s, &addr_server, sizeof(addr_server)) == -1)
		{
			printf("test_udp bind errno=%d\n", errno);
			break;
		}
		if ((buf = malloc(bufLen)) == NULL)
		{
			break;
		}
		for (;;)
		{
			sockLen = sizeof(addr_client);
			if ((recvLen = recvfrom(s, buf, bufLen, 0, &addr_client, &sockLen)) < 0)
			{
				break;
			}
			processRecvBuf(s, &addr_client, sockLen, buf, recvLen);
		}
	} while (0);
	if (s != -1)
	{
		close(s);
		s = -1;
	}
}
int main()
{
	//daemon(0, 0);
	processCheckNET();
    return 0;
}