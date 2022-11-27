import ssl


def defoult_request(c_sock_ssl: ssl.SSLSocket, request: str):
    c_sock_ssl.send(f"{request}\r\n".encode("UTF-8"))
    recv = c_sock_ssl.recv(1024)
    return recv.decode("UTF-8")
