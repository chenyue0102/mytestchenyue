#include "simpletcpheader.h"

#ifdef WIN32
bool setSocketBlock(SOCKET s, bool isBlock){
    u_long v = isBlock ? 0 : 1;
    if (ioctlsocket(s, FIONBIO, &v) == SOCKET_ERROR) {
        return false;
    }else{
        return true;
    }
}
#else

bool setSocketBlock(SOCKET s, bool isBlock){
    int flag = fcntl(s, F_GETFL, 0);
    if (isBlock){
        flag &= ~O_NONBLOCK;
    }else{
        flag |= O_NONBLOCK;
    }
    fcntl(s, F_SETFL, flag);
    return true;
}

int getSocketError(){
    return errno;
}
#endif
