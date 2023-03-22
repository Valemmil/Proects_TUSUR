import socket


def main():
    # Создаем серверный сокет и начинаем прослушивание на порту 1080
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 1080))
    server_socket.listen(1)
    print('SOCKS4 прокси-сервер запущен на порту 1080')

    while True:
        # Принимаем входящие соединения
        client_socket, client_address = server_socket.accept()
        print(f'Новое соединение от {client_address[0]}:{client_address[1]}')

        # Обрабатываем клиентский запрос
        handle_client(client_socket)


def handle_client(client_socket):
    # Читаем заголовок SOCKS4 запроса
    header = client_socket.recv(8)
    if len(header) < 8:
        print('Неверный заголовок')
        client_socket.close()
        return

    # Парсим SOCKS4 запрос
    version, command, port, ip_address = parse_socks4_request(header)

    # Устанавливаем соединение с запрошенным назначением
    destination_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    destination_socket.connect((ip_address, port))
    print("Произошло подключение к " + ip_address + ":" + str(port))

    # Отправляем ответ на SOCKS4 запрос
    response = b'\x00\x5a' + port.to_bytes(2, byteorder='big') + ip_address.encode() + b'\x00'
    client_socket.send(response)

    # Перенаправляем трафик между клиентом и назначением
    relay_traffic(client_socket, destination_socket)


def parse_socks4_request(header):
    # Проверяем версию SOCKS4 протокола
    if header[0] != 4:
        raise ValueError('Неверная версия SOCKS4 протокола')

    # Извлекаем номер порта и IP адрес
    port = int.from_bytes(header[2:4], byteorder='big')
    ip_address = socket.inet_ntoa(header[4:8])

    # Извлекаем команду
    command = header[1]
    if command == 1:
        print('SOCKS4 connect command')
    elif command == 2:
        print('SOCKS4 bind command')
    else:
        raise ValueError('Неверная команда SOCKS4 протокола')

    return 4, command, port, ip_address


def relay_traffic(client_socket, destination_socket):
    print("Принимаю данные")
    while True:
        # Ожидаем данные от клиента или назначения
        while True:
            data = client_socket.recv(4096)
            if not data:
                break
            destination_socket.sendall(data)

            data = destination_socket.recv(4096)
            if not data:
                break
            client_socket.sendall(data)


if __name__ == '__main__':
    main()
