import socket


def connect_to_proxy(address='localhost', port=1080):
    # Подключаемся к прокси
    proxy_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    proxy_socket.connect((address, port))

    # Составляем SOCKS4 запрос клиента и отправляем его
    host = input('Введите сайт: ')
    ip_address = socket.gethostbyname(host)
    socks_request = b'\x04\x01' + (80).to_bytes(2, byteorder='big') + socket.inet_aton(ip_address) + b'\x00'
    proxy_socket.send(socks_request)

    # Читаем заголовок SOCKS4 ответа
    header = proxy_socket.recv(20)
    if len(header) < 8:
        print('Неверный заголовок')
        proxy_socket.close()
        return

    if header[1] != 90:
        print('Не удалось установить соединение\nКод ответа: ')
        print(header[1])
        proxy_socket.close()
        return

    text_request = input("Введите запрос:")

    if text_request == "":
        text_request = f"GET / HTTP/1.1\r\n" \
                       f"Host:{host}\r\n" \
                       f"User-Agent: Windows\r\n" \
                       "\r\n"
    proxy_socket.send(text_request.encode())

    while True:
        data = proxy_socket.recv(4096)
        print(data)


if __name__ == '__main__':
    connect_to_proxy()
