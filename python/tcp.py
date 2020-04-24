#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket
import threading
import sys

g_server = 0


def startClient(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    err = s.connect_ex()
    if err == 0:
        print('connect success')
    else:
        print('connect failed')
        return
    s.send('hello client')
    receive = s.recv(1024)
    print('client receive' + receive)


def processServerThread(sock, address):
    print('client address' + address)
    while True:
        sock.recv(1024, 0)
        sock.send('hello, world')


def serverThread(port):
    print('serverThread start')
    global g_server
    g_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP);
    g_server.bind(('127.0.0.1', port))
    g_server.listen(5)
    while True:
        sock, address = g_server.accept()
        if 0 == sock:
            print('client socket error')
            break
        print("new client accept ")
        processServerThread(sock, address)

    print('serverThread exit')


g_serverThread = 0


def startServer(port):
    global g_serverThread
    g_serverThread = threading.Thread(target=serverThread, args=(port,))
    g_serverThread.start()


def TestSocket(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    err = s.connect_ex((ip, port))
    if err == 0:
        print('connect success')
    else:
        print('connect failed')
    s.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1);
    # socket多久没有发送包，则发送keep alive包，单位秒
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 3);
    # 两次探测间，间隔秒数
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 1);
    # 探测的次数
    s.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 2);


    while True:
        receiveBuffer = s.recv(1024, 0)
        print('receive finish')
        if len(receiveBuffer) == 0:
            break
        print(recvBuffer)
    s.close()
    return


if __name__ == '__main__':
    # TestSocket('10.0.29.59', 26666)
    # TestSocket('61.135.169.125', 80)

    num = 0
    while True:
        print('0:exit 1:startServer 2:startClient')
        strReadLine = sys.stdin.readline()
        num = int(strReadLine)
        if 0 == num:
            break
        elif 1 == num:
            startServer(10086)
        else:
            break

    if 0 != g_server:
        g_server.close()
        g_server = 0

    if 0 != g_serverThread:
        g_serverThread.join()
        g_serverThread = 0

    print("process finished")
