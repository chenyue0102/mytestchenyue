# -*- coding:UTF-8 -*-
from http.server import HTTPServer, BaseHTTPRequestHandler
import json


class Resquest(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        data = {'version': 'abc123'}
        self.wfile.write(json.dumps(data).encode())


if __name__ == '__main__':
    host = ('localhost', 80)
    server = HTTPServer(host, Resquest)
    server.serve_forever()
