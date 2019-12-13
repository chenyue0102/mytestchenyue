# -*- coding:UTF-8 -*-
import http.client
import urllib
import parser
import sys


def testGET(paramText):
    con = http.client.HTTPConnection('localhost')
    con.request('GET', paramText)
    response = con.getresponse()
    print(response.status, response.reason)
    print(response.getheaders())
    print(response.read())
    con.close()
    return


def testDownload(paramText, filePath):
    con = http.client.HTTPConnection('localhost')
    con.request('GET', paramText)
    response = con.getresponse()
    print(response.status, response.reason)
    print(response.getheaders())
    # print(response.read())
    d = response.read();
    con.close()
    f = open(filePath, 'wb')
    f.write(d)
    f.close()
    return


def testPOST():
    return


if __name__ == '__main__':
    print(sys.argv)
    paramLen = len(sys.argv)
    paramText = ''
    paramFilePath = ''
    if paramLen >= 3:
        paramText = sys.argv[2]
    if paramLen >= 4:
        paramFilePath = sys.argv[3]
    if paramLen >= 1:
        if sys.argv[1] == '1':
            testGET(paramText)
        elif sys.argv[1] == '2':
            testPOST()
        elif sys.argv[1] == '3':
            testDownload(paramText, paramFilePath)
        else:
            print('param error')
    else:
        print('enter param')
