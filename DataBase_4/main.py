import psycopg2  # работа с СУБД PostgreSQL
from config import host, user, password, db_name


def main():
    try:
        # ПОДКЛЮЧЕНИЕ К БАЗЕ ДАННЫХ
        connection = psycopg2.connect(
            host=host,
            user=user,
            password=password,
            database=db_name
        )
    except Exception as _ex:
        print("Ошибка при работе с PostgreSQL", _ex)
        return

    connection.autocommit = True
    # Создаем объект cursor, который содержит в себе методы для выполнения SQL-команд

    with connection.cursor() as cursor:
        cursor.execute(
            "SELECT version();"
        )
        print(f"Версия сервера: {cursor.fetchone()}")

        # ВСТАВКА СТРОКИ В ОДНУ ИЗ ТАБЛИЦ
        # cursor.execute(
        #     #"""INSERT INTO SPEC (code_s,name_s) VALUES('3.31.77.77', 'Стоматолог')"""
        #    #"""DELETE FROM SPEC WHERE name_s='Стоматолог'"""
        # )
        # print("Данные были успешно вставлены")

        cursor.execute("""SELECT doctor.snam_d, COUNT(visit.num_p) as "Количество посещений" FROM public.visit
        FULL JOIN public.doctor on(visit.num_d=doctor.num_d) GROUP BY doctor.snam_d;""")
        select_1 = cursor.fetchall()

        cursor.execute("""SELECT doctor.snam_d,patient.snam_p,visit.diagn FROM public.visit LEFT JOIN public.doctor 
        on (visit.num_d=doctor.num_d) LEFT JOIN public.patient on (visit.num_p=patient.num_p) ORDER BY doctor.snam_d; 
        """)
        select_2 = cursor.fetchall()

        str_content = ''
        for i in range(len(select_1)):
            str_content += f"{select_1[i][0].ljust(16, ' ')}Всего {select_1[i][1]}\n"
            for j in range(len(select_2)):
                if select_1[i][0] == select_2[j][0]:
                    str_content += " " * 40 + f"{select_2[j][1].ljust(16, ' ')}{select_2[j][2]}\n"
            str_content += "\n"

        with open('DB.txt', 'w') as filename:
            filename.write(str_content)
        # ==============================================


main()
