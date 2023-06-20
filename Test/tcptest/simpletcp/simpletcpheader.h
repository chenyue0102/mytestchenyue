#ifdef WIN32

#include <WS2tcpip.h>
#include <winsock.h>
#include <Windows.h>
#define inet_aton(ip, buf) \
	inet_pton(AF_INET, ip, buf)

#define getSocketError WSAGetLastError
#define ERR_BLOCK WSAEWOULDBLOCK
typedef int socklen_t;

//设置socket是否为阻塞
bool setSocketBlock(SOCKET s, bool isBlock);
#else

#include <sys/socket.h>
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>
#include <unistd.h> //close
#include <fcntl.h>
#include <errno.h>

typedef int SOCKET;
#define closesocket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ERR_BLOCK EAGAIN

bool setSocketBlock(SOCKET s, bool isBlock);

int getSocketError();

#endif
