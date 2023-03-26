"""
UDP-клиент для управления заданиями
"""
import socket
from zlib import crc32


def task_manager():
    out_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    host = 'localhost'
    port = 4080
    server = (host, port)

    message = "task_manager"
    data = message + "::" + str(crc32(message.encode()))
    out_socket.sendto(data.encode(), server)

    input("Press any key for continue")

    message = "end_connections"
    data = message + "::" + str(crc32(message.encode()))
    out_socket.sendto(data.encode(), server)

    input("Press any key for send task to calculater")

    in_file = open("in_list_value.txt", 'r')
    message = in_file.read()
    data = message + "::" + str(crc32(message.encode()))
    out_socket.sendto(data.encode(), server)
    in_file.close()

    while True:
        data, _ = out_socket.recvfrom(4096)
        data = data.decode().split('::')
        if int(data[1]) != crc32(data[0].encode()):
            print("Hash not equal")
            continue

        print(data[0])


if __name__ == '__main__':
    task_manager()
