#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket

def TestSocket(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    err = s.connect_ex((ip, port))
    s.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1);
    #socket多久没有发送包，则发送keepalive包，单位秒
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 3);
    #两次探测间，间隔秒数
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 1);
    #探测的次数
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 2);
    if err == 0:
        print('connect success')
    else:
        print('connect failed')

    while True:
        recvBuffer = s.recv(1024, 0)
        print('receive finish')
        if (len(recvBuffer) == 0):
            break
        print (recvBuffer)
    s.close()
    return

if __name__ == '__main__':
    #TestSocket('10.0.29.59', 26666)
    TestSocket('10.0.30.83', 26666)

