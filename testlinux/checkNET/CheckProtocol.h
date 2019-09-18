#ifndef _CHECK_PROTOCOL_H_
#define _CHECK_PROTOCOL_H_

#define MY_UDP_PORT 5618

enum EMsgId
{
	EMsgIdQueryAddress = 1,
};
typedef struct _MSG_HEADER
{
	uint32_t msgId;
}MSG_HEADER;

typedef struct _MSG_QUERY_ADDRESS
{
	MSG_HEADER header;
	uint32_t clientAddress;
	uint16_t clientPort;
}MSG_QUERY_ADDRESS;
#endif
