#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket

def TestSocket(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
    err = s.connect_ex((ip, port))
    if err == 0:
        print('connect success')
    else:
        print('connect failed')

    s.close()
    return

if __name__ == '__main__':
    #TestSocket('10.0.29.59', 26666)
    TestSocket('10.0.29.233', 26666)

