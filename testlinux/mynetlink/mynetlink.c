#include <linux/netlink.h>
#include <poll.h>
#include <linux/socket.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void die(char *s)
{
    write(2, s, strlen(s));
    exit(1);
}


int main(int argc, char *argv[])
{
    struct sockaddr_nl nls;
    struct pollfd pfd;
    char buf[512];

    memset(&nls, 0, sizeof(nls));
    nls.nl_family = AF_NETLINK;
    nls.nl_pid = getpid();
   nls.nl_groups = -1;

    pfd.events = POLLIN;
    pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);

    if (-1 == pfd.fd)
        die("not root\n");

    int ret = bind(pfd.fd, (void*)&nls, sizeof(struct sockaddr_nl));
    printf("%s", strerror(errno));
    if (0 != ret){
        die("bind failed\n");
    }

    printf("while \n");
    while (-1 != poll(&pfd, 1, -1))
    {
        printf("recv \n");
        int i, len = recv(pfd.fd, buf, sizeof(buf), MSG_DONTWAIT);
        if (len == -1)
            die("recv failed\n");

        i = 0;
        while(i < len){
            printf("%s\n", buf + i);
            i += strlen(buf + i) + 1;
        }
    }
    die("poll\n");

    return 0;
}