#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket
import select
import threading
import sys
import time
import binascii

g_exit = False
GET_IP_PORT_REQ = 1
GET_IP_PORT_ACK = 2
SERVER_IP = '47.105.138.43'
SERVER_BIND_IP = '0.0.0.0'
SERVER_PORT = 7788
g_s = 0


def startServer():
    print('startServer\n')
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    s.bind((SERVER_BIND_IP, SERVER_PORT))
    # IOC_IN = 0x80000000
    # IOC_VENDOR = 0x18000000
    # SIO_UDP_CONNRESET = IOC_IN | IOC_VENDOR | 12
    # socket.SIO_KEEPALIVE_VALS
    # s.ioctl(SIO_UDP_CONNRESET, False)
    s.setblocking(0)
    timeoutSeconds = 1
    while not g_exit:
        ready = select.select([s], [], [], timeoutSeconds)
        if ready[0]:
            buf, address = s.recvfrom(1024, 0)
            msgId = int.from_bytes(buf, 'big')
            if msgId == GET_IP_PORT_REQ:
                msgIdBytes = GET_IP_PORT_ACK.to_bytes(4, 'big')
                sendBytes = bytearray(msgIdBytes)
                clientIp = address[0]
                clientPort = address[1]
                # print(type(clientIp))
                # print(type(clientPort))
                # print(binascii.hexlify(clientPort.to_bytes(4, 'big')))
                sendBytes += clientPort.to_bytes(4, 'big')
                sendBytes += bytearray(clientIp, encoding='utf-8')
                try:
                    s.sendto(sendBytes, address)
                except ConnectionResetError as e:
                    print(e)
                print(binascii.hexlify(sendBytes))
        else:
            time.sleep(0.001)
    return



def testClient1():
    print('client1\n')
    sendByte = GET_IP_PORT_REQ.to_bytes(4, 'big')
    sendAddress = (SERVER_IP, SERVER_PORT)
    g_s.connect(sendAddress)
    ret = g_s.sendto(sendByte, sendAddress)
    success = False
    if ret <= 0:
        print('send error \n')
    else:
        buf, address = g_s.recvfrom(1024, 0)
        msgId = int.from_bytes(buf[0:4], 'big')
        serverRetPort = int.from_bytes(buf[4:4 + 4], 'big')
        serverRetIp = buf[8:].decode('utf-8')
        clientAddress = g_s.getsockname()
        localIp = clientAddress[0]
        localPort = clientAddress[1]
        # localIp = socket.gethostbyname(socket.gethostname())
        print('msgId:' + str(msgId) + ',serverRetIp:' + serverRetIp + ',serverRetPort:' + str(serverRetPort) +
              ',localIp:' + localIp + ',localPort:' + str(localPort) + '\n')
        if localPort == serverRetPort and localIp == serverRetIp:
            success = True
    return success


def testClient():
    if testClient1():
        print('not NAT\n')
    else:
        print('in NAT\n')
    return


if __name__ == '__main__':
    print('0:exit 1:client1 9:server\n')
    test = GET_IP_PORT_ACK.to_bytes(4, 'big')

    # print (type(test))
    # print (binascii.hexlify(test))

    g_s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

    for line in sys.stdin:
        line = line.rstrip('\n')
        if line == '0':
            break
        elif line == '1':
            testClient()
        elif line == '9':
            startServer()
        else:
            break

    g_s.close()
    print('finish\n');
