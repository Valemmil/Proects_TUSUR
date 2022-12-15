# Импортируем библиотеки
from flask import Flask
import websockets
import asyncio
# библиотека для преобразования xml с помощью xslt
import lxml.etree as etr

# парсим xml файл в dom
dom = etr.parse("file.xml")
# парсим шаблон в dom
xslt = etr.parse("file.xslt")
# получаем трансформер
transform = etr.XSLT(xslt)
# преобразуем xml с помощью трансформера xslt
newhtml = transform(dom)
# преобразуем из памяти dom в строку, возможно, понадобится указать кодировку
strfile = etr.tostring(newhtml)

app = Flask(__name__)

all_clients = []


@app.route("/")
async def start_server():
    return strfile


@app.route("/style.css")
async def css_in():
    with open("style.css", "r") as style_file:
        style_str = style_file.read()
        return style_str


@app.route("/ws")
async def web_socket(ws):
    pass


async def new_clien_connect(clien_socket: websockets.WebSocketClientProtocol, path: str):
    print("New connection")
    all_clients.append(clien_socket)
    new_message = await clien_socket.recv()


async def main():
    await websockets.serve(new_clien_connect, "localhost", 5000)


if __name__ == "__main__":
    app.run()
    event_loop = asyncio.get_event_loop()
    event_loop.run_until_complete(main())
    event_loop.run_forever()

# # обработчик запросов к http серверу
# class MainHandler(tornado.web.RequestHandler):
#     # обработка запроса get
#     def get(self):
#         print('Get')
#         # передаем нашу страницу в которой реализована работа с клиентом
#         self.write(strfile)
#
#
# # обработчик событий вебсоккетов
# class EchoWebSocket(tornado.websocket.WebSocketHandler):
#     clients = []  # массив клиентов
#     fl = True
#     index = 0
#
#     # процедура отправки клиенту текущего индекса через 3 сек
#     def go(self, client):
#         print('ok')
#         if self.fl:
#             self.index = self.index + 1
#             s = u'{"type": "chat", "data": "' + str(self.index) + '"}'
#             print("send message : " + s)
#             # посылаем сообщение клиенту
#             client.write_message(s)
#             # запускаем таймер, который будет вызывать функцию go с аргументом client каждые 3 сек
#             t = threading.Timer(3.0, self.go, [client])
#             t.start()
#
#     # проверяются и даются права на действия с сокетом, здесь права даются всем
#     def check_origin(self, origin):
#         return True
#
#     # обработка события открытия соединения
#     def open(self):
#         print("Client open")
#         # добавляем клиента в список
#         self.clients.append(self)
#         self.fl = True
#         # запускаем поток отправки сообщение клиенту
#         self.go(self)
#
#     # обработка прихода события от сервера
#     def on_message(self, message):
#         print("Client message " + message)
#
#     # обработка события закрытия сокета клиента
#     def on_close(self):
#         self.fl = False
#         # удаляем клиента из списка
#         self.clients.remove(self)
#         print("WebSocket closed")
#
#
# # создаем приложение tornado с обработчиком вебсокетов и http сервером
# app = tornado.web.Application([(r'/', MainHandler)])
#
# # прослушиваем на порту
# app.listen(10556)
# print("Start Server")
# # запускаем цикл прослушивания и обработки событий
# tornado.ioloop.IOLoop.instance().start()
