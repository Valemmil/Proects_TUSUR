import ssl
from requests import defoult_request


def read_mail(c_sock_ssl: ssl.SSLSocket):
    username = input("Введите email: ")
    if username.replace(" ", "") == "":
        username = "taosist.ni@gmail.com"

    password = input("Введите пароль: ")
    if password.replace(" ", "") == "":
        password = "ocuihbiopiueaahm"

    print(defoult_request(c_sock_ssl, f"USER {username}"))

    print(defoult_request(c_sock_ssl, f"PASS {password}"))

    while True:
        stat_mes = defoult_request(c_sock_ssl, f"STAT")
        print(stat_mes)
        statistic = stat_mes.split()[1:]
        print(f"Всего сообщений: {statistic[0]}\nЗанимают места: {statistic[1]}")

        num_message = int(input(f"Открыть какое сообщение из {statistic[0]} ты хочешь?\n"
                                f"-1 - выйти из режима чтения\n>>"))
        if num_message == -1:
            break
        elif not (0 < num_message <= int(statistic[0])):
            print("Не правильно введено значение")
            continue
        else:
            message = b""
            c_sock_ssl.send(f"RETR {num_message}\r\n".encode("UTF-8"))
            while True:
                recv = c_sock_ssl.recv(1024)
                message += recv
                if message[-len("\r\n.\r\n".encode("UTF-8")):] == "\r\n.\r\n".encode("UTF-8"):
                    break
            print(message.decode("UTF-8"))
