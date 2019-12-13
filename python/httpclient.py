# -*- coding:UTF-8 -*-
import http.client
import urllib
import parser
import sys


def testGET():
    con = http.client.HTTPConnection('localhost')
    con.request('GET', '/getVersion')
    response = con.getresponse();
    print(response.status, response.reason)
    print(response.getheaders())
    print(response.read())
    con.close()
    return


def testPOST():
    return


if __name__ == '__main__':
    if len(sys.argv) > 0:
        if sys.argv[1] == '1':
            testGET()
        elif sys.argv[1] == '2':
            testPOST()
        else:
            print('param error')
    else:
        print('enter param')
