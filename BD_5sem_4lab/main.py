from psycopg2 import connect


def main():
    try:
        connection = connect(
            database='lab1',
            user='postgres',
            password='admin',
            host='localhost',
            port='5432'
        )
    except Exception as _ex:
        print("Ошибка при работе с PostgreSQL", _ex)
        return
    connection.autocommit = True

    with connection.cursor() as cursor:
        cursor.execute(
            "SELECT version();"
        )
        print(f"Версия сервера: {cursor.fetchone()}")

        cursor.execute(
            """INSERT INTO client (code_c, fio, addr_c, tel)
            VALUES(3, 'Лисица Дмитрий Сергеевич', 'Вершинина 10', '+79133236563')"""
        )

        # cursor.execute(
        #     """DELETE FROM client WHERE code_c = 3"""
        # )

        cursor.execute("""SELECT DISTINCT client.code_c, client.fio  
                            FROM client RIGHT JOIN "order" ON (client.code_c = "order".code_c)
                            WHERE "order".del_dt >= '2022-11-14'::date AND "order".del_dt <= '2022-11-20'::date;""")
        clients = cursor.fetchall()

        cursor.execute("""SELECT Пользователь, Заказ, Сумма::numeric 
                            FROM price_orders 
                            WHERE Дата >= '2022-11-14'::date AND Дата <= '2022-11-20'::date;""")
        orders = cursor.fetchall()
        str_content = 'Отчёт'.center(60) + "\n" + \
                      "об исполненных заказах клиентов с 14.11.22 по 20.11.22".center(60) + "\n\n"
        sum_orders = 0
        num_orders = 0
        for client in clients:
            fio = client[1].split(" ")
            str_content += f"{fio[0]} {fio[1][0]}. {fio[2][0]}. ({client[0]})\n" + \
                " " * 18 + 'Заказ №' + "на сумму".rjust(22, " ") + "\n"
            sum_order = 0
            num_order = 0
            for order in orders:
                if client[0] == order[0]:
                    str_content += " " * 18 + f"{str(order[1]).rjust(7, ' ')}{(str(order[2]) + 'р.').rjust(22, ' ')}\n"
                    sum_order += order[2]
                    num_order += 1
            str_content += " " * 18 + "Всего заказов " + str(num_order) + "\n" \
                           + " " * 18 + "на сумму" + (str(sum_order) + 'р.').rjust(22, " ") + "\n"
            str_content += "\n"
            num_orders += num_order
            sum_orders += sum_order
        str_content += "\n" + "Всего заказов за неделю" + str(num_orders).rjust(10) + "\n" \
                       + "На общую сумму" + str(sum_orders).rjust(19)
        with open('DB.txt', 'w') as filename:
            filename.write(str_content + "\n")

    connection.close()


main()
