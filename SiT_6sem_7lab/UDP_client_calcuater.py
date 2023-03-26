"""
UDP-клиент для расчётов
"""
import socket
from statistics import fmean
from zlib import crc32


def obt(list_value: list):
    avg_list_value = []
    for i in range(1, len(list_value) - 1):
        avg_list_value.append(fmean((list_value[i - 1], list_value[i], list_value[i + 1])))
    return avg_list_value


def calculater():
    out_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    host = 'localhost'
    port = 4080
    server = (host, port)

    message = "calculater"
    data = f"{message}::{crc32(message.encode())}"
    out_socket.sendto(data.encode(), server)

    avg_list_value = []
    while True:
        data, _ = out_socket.recvfrom(4096)
        data = data.decode().split('::')
        if int(data[1]) != crc32(data[0].encode()):
            print("Hash not equal")
            continue

        if data[0] != "repite":
            print(data[0])
            list_value = list(map(float, data[0].split()))
            avg_list_value = obt(list_value)

        message = ' '.join(map(str, avg_list_value))
        print(message)
        data = message + "::" + str(crc32(message.encode()))
        out_socket.sendto(data.encode(), server)


if __name__ == '__main__':
    calculater()
