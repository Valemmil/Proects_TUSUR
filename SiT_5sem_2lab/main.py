import ssl
from socket import *
from smtp_client import send_message
from pop3 import read_mail


def main():

    control = int(input("Отправить(0) или прочитать(1) сообщение?\n>>"))

    if control == 0:
        mailserver = 'smtp.gmail.com'
        port = 465
    elif control == 1:
        mailserver = 'pop.gmail.com'
        port = 995
    else:
        return 0

    try:
        c_sock = socket(AF_INET, SOCK_STREAM)
        c_sock.connect((mailserver, port))
        c_sock_ssl = ssl.wrap_socket(c_sock)
        recv = c_sock_ssl.recv(1024)
        print(recv.decode("UTF-8"))
    except:
        print("Ошибка подключения")
        return

    if control == 0:
        send_message(c_sock_ssl)
    elif control == 1:
        read_mail(c_sock_ssl)

    c_sock_ssl.close()
    c_sock.close()


if __name__ == "__main__":
    main()
