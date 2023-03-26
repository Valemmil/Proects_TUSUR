"""
UDP-сервер для рассылки заданий от таск-менеджера расчётникам
"""
import socket
from zlib import crc32


def server():
    in_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    host = 'localhost'
    port = 4080
    addr = (host, port)

    in_socket.bind(addr)

    calculaters = []
    task_manager = None

    while True:
        data, addr = in_socket.recvfrom(4096)
        data = data.decode().split('::')
        if int(data[1]) != crc32(data[0].encode()):
            print(f"{data[1]} {crc32(data[0].encode())} {data[0]}")
            print("Hash not equal")
            continue

        if data[0] == 'calculater':
            print(f'Connecting calculater to: {addr}')
            calculaters.append(addr)

        elif data[0] == 'task_manager':
            print(f'Connecting task manager to: {addr}')
            task_manager = addr

        elif data[0] == 'end_connections' and addr == task_manager:
            break

    while True:
        data, addr = in_socket.recvfrom(4096)
        tested_data = data.decode().split('::')
        if int(tested_data[1]) != crc32(tested_data[0].encode()):
            print("Hash not equal")
            continue

        if addr == task_manager:
            for calculater in calculaters:
                in_socket.sendto(data, calculater)

        elif addr in calculaters:
            in_socket.sendto(data, task_manager)


if __name__ == '__main__':
    server()
