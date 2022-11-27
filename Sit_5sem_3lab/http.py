import re
from socket import *
from ssl import *
from http_parser.http import HttpStream
from http_parser.reader import SocketReader
from html.parser import HTMLParser

hostname = "www.sumatrapdfreader.org"
path = "/download-free-pdf-viewer"
DEFAULT_PORT = 443
TIMEOUT = 0.0
sslcontext = create_default_context()


class tHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        all_tegs_attrs = ''
        all_tegs_attrs += f"{tag}:  "
        for attr in attrs:
            all_tegs_attrs += f"\n     attr: {attr}"
        print(all_tegs_attrs)


def parse_path(full_path: str):
    if full_path == '':
        return
    print("PARSE_PATH: ", full_path)
    global hostname, path
    if full_path[0] != '/':
        temp_host = re.search(r'(//[\w.]*)', full_path)
        if temp_host:
            hostname = temp_host[0][2:]
        print("parsed hostname: ", hostname)
        if re.search(r'(\w/.*)', full_path) or re.search(r'(\w/.*\.html)', full_path):
            path = re.search(r'(\w/.*)', full_path)[0][1:]
        else:
            path = '/'
    else:
        path = full_path
    return '\ncorrect_host ' + f"{hostname}{path}"


def open_link(full_path):
    parse_path(full_path)

    full_path = 'https://' + hostname + path
    print("open_link: ", full_path)

    with create_connection((hostname, DEFAULT_PORT)) as sock:
        with sslcontext.wrap_socket(sock, server_hostname=hostname) as ssock:
            print(ssock.version())
            receive_page = f"GET {path} HTTP/1.1\r\n" \
                           f"Host:{hostname}\r\n" \
                           f"User-Agent: Windows\r\n" \
                           "\r\n"
            ssock.send(receive_page.encode())

            r = SocketReader(ssock)
            p = HttpStream(r)
            body = p.body_file().read()
            if re.search(r'([^/]/.*\.\w{2,5})', path):
                filename = re.search(r'([^/]*\.\w{2,5})', path)[0]
                with open(filename, 'wb') as source:
                    source.write(body)
                    source.close()
                    return
            parser = tHTMLParser()
            parser.feed(body.decode('utf8'))


def main():
    while True:
        in_url = input('Введите url: ')
        if in_url == '-1':
            return
        open_link(in_url)


if __name__ == '__main__':
    main()
