import datetime
import base64
import ssl
from requests import defoult_request


def send_message(c_sock_ssl: ssl.SSLSocket):
    username = input("Введите email: ")
    if username.replace(" ", "") == "":
        username = "muzykinni@gmail.com"

    password = input("Введите пароль: ")
    if password.replace(" ", "") == "":
        password = "wwlfsphygkvqcaqz"

    username64 = base64.b64encode(f'{username}'.encode("UTF-8")).decode("UTF-8")
    password64 = base64.b64encode(f'{password}'.encode("UTF-8")).decode("UTF-8")

    init_mail(c_sock_ssl, username64, password64)

    print(defoult_request(c_sock_ssl, f"MAIL FROM:<{username}>"))

    recipient = input("Введите получателя: ")

    print(defoult_request(c_sock_ssl, f"RCPT TO:<{recipient}>"))

    text_subject = input("Введите текст темы:\n")
    text_massege = input("Введите текст сообщения:\n")

    massege = f"From: {username}\r\n" \
              f"To: {recipient}\r\n" \
              f"Date: {datetime.datetime.today().strftime('%Y-%m-%d-%H.%M.%S')}\r\n" \
              f"Subject: {text_subject}\r\n\r\n" \
              f"{text_massege}\r\n.\r\n"

    print(defoult_request(c_sock_ssl, f"DATA"))
    print(defoult_request(c_sock_ssl, massege))


def init_mail(c_sock_ssl: ssl.SSLSocket, username64, password64):
    print(defoult_request(c_sock_ssl, f"EHLO exemple.ru"))

    print(defoult_request(c_sock_ssl, f"AUTH LOGIN"))

    print(defoult_request(c_sock_ssl, username64))

    c_sock_ssl.send((f"{password64}" + "\r\n").encode("UTF-8"))
    recv = c_sock_ssl.recv(1024)
    print(recv.decode("UTF-8"))
    if recv.decode("UTF-8")[0] == "5":
        print("Ошибка: не правильный логин или пароль")
        exit(500)
