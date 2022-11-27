import socket

sock = socket.socket()
sock.bind(('', 9090))
sock.listen(10)
conn, addr = sock.accept()
print('connected:', addr)
number1 = int(conn.recv(1024).decode('utf-8'))
number2 = int(conn.recv(1024).decode('utf-8'))
result = number1 % number2
print(f'{number1} % {number2} = {result}')
conn.send(str(result).encode('utf-8'))
conn.close()
