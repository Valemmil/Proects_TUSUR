import socket
import re
import time


def multi_str(socket_ftp):
    buff = socket_ftp.recv(1024)
    print(buff.decode('utf-8'))
    message = buff.decode('utf-8')
    # Если многострочный прием, по rfc начинается с xyz-, и заканчивается на xyz<SP>
    if re.search(r'(\d{3}-)', message):
        # rest = buff[0:3].decode('utf-8')
        while True:
            buff = socket_ftp.recv(1024)
            print(buff.decode('utf-8'))
            message += buff.decode('utf-8')
            if re.search(r"(\d{3}\s)", message):
                break
    # Если требуется продолжение действий (читать rfc по кодам ответов ftp)
    if message:
        if message[0] == "1":
            buff = socket_ftp.recv(1024)
            print(buff.decode('utf-8'))
            message += buff.decode('utf-8')
    return message


def send_cmd(socket_ftp, cmd: bytes):
    time.sleep(0.1)
    socket_ftp.send(cmd)
    print(cmd[:-2].decode('utf-8'))
    message = multi_str(socket_ftp)
    return message


def main():
    socket_ftp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server = input('Введите ftp server: ')

    try:
        # res = socket_ftp.connect(("ftp.gnu.org", 21))
        socket_ftp.connect((server, 21))
        print("Connection OK\n")
    except:
        print("Error connection")

    time.sleep(0.1)
    multi_str(socket_ftp)

    username = input("Введите логин: ")
    password = input("Введите пароль: ")
    send_cmd(socket_ftp, f"USER {username}\r\n".encode("utf-8"))
    send_cmd(socket_ftp, f"PASS {password}\r\n".encode("utf-8"))

    while True:
        ret = send_cmd(socket_ftp, "PASV\r\n".encode('utf-8'))
        # ищем подстроку соответствующую регулярному выражению
        match = re.search(r"(\d+,\d+,\d+,\d+,\d+,\d+)", ret)
        # разбиваем через запятую получая список чисел соответствующих ip port
        match = re.split(',', match[0])
        ip = ".".join(match[0:4])
        port = int(match[4]) * 256 + int(match[5])
        print(f"ip {ip} port {port}")

        socket_pasv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            # res = s1.connect((ip, port))
            socket_pasv.connect((ip, port))
            print("Connection OK\n")
        except:
            print("Error connection")

        send_cmd(socket_ftp, "LIST\r\n".encode("utf-8"))
        list_dir = b""
        while True:
            buff = socket_pasv.recv(1024)
            if not buff:
                break
            list_dir += buff
        print(list_dir.decode('utf-8'))

        cwd_to = input("Перейти в каталог?\n-1 - выйти из режима смены каталогов\n>> ")
        if cwd_to == "-1":
            break
        send_cmd(socket_ftp, f"CWD {cwd_to}\r\n".encode("utf-8"))

    # send_cmd(socket_ftp, CMD_LIST)
    # buf = socket_pasv.recv(1024)
    filename = input("Введите название файла\n-1 - выйти из режима выбора файла\n>> ")
    if filename == "-1":
        return
    size_file = send_cmd(socket_ftp, f"SIZE {filename}\r\n".encode("utf-8"))[:-2].split(" ")

    control = input(f"Вы уверены что хотите открыть файл {filename} размера {size_file[1]}?\ny/n>> ")

    if not (control == "y" or control == "Y"):
        return

    ret = send_cmd(socket_ftp, "PASV\r\n".encode('utf-8'))
    # ищем подстроку соответствующую регулярному выражению
    match = re.search(r"(\d+,\d+,\d+,\d+,\d+,\d+)", ret)
    # разбиваем через запятую получая список чисел соответствующих ip port
    match = re.split(',', match[0])
    ip = ".".join(match[0:4])
    port = int(match[4]) * 256 + int(match[5])
    print(f"ip {ip} port {port}")

    socket_pasv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        # res = s1.connect((ip, port))
        socket_pasv.connect((ip, port))
        print("Connection OK\n")
    except:
        print("Error connection")

    # send_cmd(socket_ftp, f"RETR {filename}".encode("utf-8"))
    send_cmd(socket_ftp, f"RETR {filename}\r\n".encode("utf-8"))
    file_real = open(filename, 'w')
    file_content = b''
    for i in range(int(size_file[1]) // 1024 + 1):
        buff = socket_pasv.recv(1024)
        file_content += buff
        file_real.write(buff.decode('utf-8'))
    # print(file_content.decode('utf-8'))
    file_real.close()

    send_cmd(socket_ftp, "QUIT\r\n".encode('utf-8'))
    socket_ftp.close()


if __name__ == '__main__':
    main()
