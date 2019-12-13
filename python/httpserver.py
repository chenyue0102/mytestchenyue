# -*- coding:UTF-8 -*-
from http.server import HTTPServer, BaseHTTPRequestHandler
import json
from urllib import parse


testVersion = 'abcd1234'

def getModuleVersion(qs):
    module = ''
    version = ''
    for key, value in qs.items():
        if key == 'module':
            if len(value) >= 1:
                module = value[0]
        elif key == 'version':
            if len(value) >= 1:
                version = value[0]

    print('module=' + module + ' version=' + version)
    return module, version


class Resquest(BaseHTTPRequestHandler):

    def do_GET(self):
        data = {}
        errcode = 404
        print('path' + str(type(self.path)) + self.path)
        o = parse.urlparse(self.path)
        print(
            'scheme=' + o.scheme + ' netloc=' + o.netloc + ' path=' + o.path + ' query=' + o.query + ' fragment=' + o.fragment)
        if o.path == '/getVersion':
            qs = parse.parse_qs(o.query)
            module, version = getModuleVersion(qs)
            if module == "test":
                data['module'] = module;
                data['version'] = testVersion
                if version != testVersion:
                    data['url'] = 'http://localhost/download/test.zip'
                errcode = 200
            else:
                data['module'] = module
                data['version'] = 'unknown'
                errcode = 404

            self.send_response(errcode)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(data).encode())
        elif o.path == '/download/test.zip':
            self.send_response(200)
            self.send_header('Content-type', 'application/octet-stream')
            self.end_headers()
            f = open('./packet.zip', 'rb')
            while True:
                d = f.read(1024);
                if not d:
                    break
                self.wfile.write(d)
            f.close()
        else:
            data = {}
            self.send_response(errcode)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(data).encode())
        return


if __name__ == '__main__':
    host = ('localhost', 80)
    server = HTTPServer(host, Resquest)
    server.serve_forever()
