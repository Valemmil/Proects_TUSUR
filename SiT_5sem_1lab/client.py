import socket

sock = socket.socket()
sock.connect(('localhost', 9090))
n1 = int(input('Введите делимое: '))
sock.send(str(n1).encode('utf-8'))
n2 = int(input('Введите делитель: '))
sock.send(str(n2).encode('utf-8'))
data = int(sock.recv(1024).decode('utf-8'))
sock.close()
print(data)
