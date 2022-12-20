import numpy
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QMessageBox

from TSiSA_UI1 import Ui_Window_stap1
from TSiSA_UI2 import Ui_Window_stap2
from TSiSA_UI3 import Ui_Window_stap3


class stap1(QtWidgets.QMainWindow, Ui_Window_stap1):
    def __init__(self, parent=None):
        super(stap1, self).__init__(parent)
        self.setupUi(self)


class stap2(QtWidgets.QMainWindow, Ui_Window_stap2):
    def __init__(self, parent=None):
        super(stap2, self).__init__(parent)
        self.setupUi(self)


class stap3(QtWidgets.QMainWindow, Ui_Window_stap3):
    def __init__(self, parent=None):
        super(stap3, self).__init__(parent)
        self.setupUi(self)


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()

        self.stacked = QtWidgets.QStackedWidget(self)
        self.setCentralWidget(self.stacked)
        self.num_experts = 0
        self.num_alters = 0
        self.experts_tables = numpy.array([])
        self.generalized_matrix = numpy.zeros((self.num_alters, self.num_alters))
        self.rank_matrix = numpy.array([])
        self.concordazhiya = 0.0

        self.window_stap1 = stap1(self)
        # self.window_Win1.setStyleSheet('#Win1 {background-color: #ffbdcc;}')
        self.window_stap2 = stap2(self)
        # self.window_Win2.setStyleSheet('#Win2 {background-color: #ccffbd;}')
        self.window_stap3 = stap3(self)
        # self.window_Win3.setStyleSheet('#Win3 {background-color: #bdccccff;}')

        self.stacked.addWidget(self.window_stap1)
        self.stacked.addWidget(self.window_stap2)
        self.stacked.addWidget(self.window_stap3)

        self.window_stap1.btn_save.clicked.connect(self.go_stap2)
        self.window_stap2.btn_save.clicked.connect(self.go_stap3)
        self.window_stap1.info_button.clicked.connect(self.info_step1)
        self.window_stap2.info_button.clicked.connect(self.info_step2)
        self.window_stap3.info_button.clicked.connect(self.info_step3)


    @staticmethod
    def info_step1():
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Information)
        msgBox.setText("Этот метод представляет собой процедуру установления предпочтения объектов при сравнении всех "
                       "возможных пар. Результаты сравнения всех пар объектов удобно представлять в виде матрицы с "
                       "булевыми значениями.\nВведите количество экспертов и альтернатив.")
        msgBox.setWindowTitle("Групповое парное сравнение")
        msgBox.setStandardButtons(QMessageBox.Ok)
        msgBox.exec_()

    @staticmethod
    def info_step2():
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Information)
        msgBox.setText("Введите значения в матрицу парного сравнения\n"
                       "Правила:\n"
                       "1) w[i][j] = 1; \n"
                       "2) если w[i][j] = 1, то w[j][i] = 0; \n"
                       "3) если w[i][j] = 1 и w[j][k] = 1, то w[i][k] = 1.")
        msgBox.setWindowTitle("Групповое парное сравнение")
        msgBox.setStandardButtons(QMessageBox.Ok)
        msgBox.exec_()\


    @staticmethod
    def error_stap2():
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Information)
        msgBox.setText("Введённые данные нарушают правила построения матриц парных сравнений\n"
                       "Правила:\n"
                       "1) w[i][j] = 1; \n"
                       "2) если w[i][j] = 1, то w[j][i] = 0; \n"
                       "3) если w[i][j] = 1 и w[j][k] = 1, то w[i][k] = 1.")
        msgBox.setWindowTitle("Ошибка")
        msgBox.setStandardButtons(QMessageBox.Ok)
        msgBox.exec_()

    @staticmethod
    def info_step3():
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Information)
        msgBox.setText("В окне представлена обобщённая матрица, ранги альтернатив и коэффициент конкордации. "
                       "Обощённая матрица показывает итоговую иерархию альтернатив. "
                       "Ранги альтернатив показывают градацию альтернатив по приоритетности "
                       "(значение 1 - самая приоритетная альтернатива). "
                       "Коэффициент конкордации представляет числовое отображение согласованности экспертов.")
        msgBox.setWindowTitle("Групповое парное сравнение")
        msgBox.setStandardButtons(QMessageBox.Ok)
        msgBox.exec_()

    def go_stap2(self):
        if self.window_stap1.num_expert.toPlainText().isdigit() and self.window_stap1.num_alter.toPlainText().isdigit():
            if int(self.window_stap1.num_expert.toPlainText()) >= 2 and \
                    int(self.window_stap1.num_alter.toPlainText()) >= 2:
                self.num_experts = int(self.window_stap1.num_expert.toPlainText())
                self.num_alters = int(self.window_stap1.num_alter.toPlainText())
                self.window_stap2.tableWidget.setRowCount(self.num_alters)
                self.window_stap2.tableWidget.setColumnCount(self.num_alters)
                top_table = self.window_stap2.tableWidget.geometry().top()
                width_table = 35 * self.num_alters + 17
                height_table = 30 * self.num_alters + 23
                self.resize(self.window_stap2.size())
                self.window_stap2.tableWidget.setGeometry(
                    QtCore.QRect(
                        ((self.size().width() - width_table) // 2),
                        top_table,
                        width_table,
                        height_table
                    )
                )

                self.stacked.setCurrentIndex(1)
                return
        msgBox = QMessageBox()
        msgBox.setIcon(QMessageBox.Warning)
        msgBox.setText("Введённные данные не коректны!\nЗначения должны быть числовыми и значения больше или равны 2")
        msgBox.setWindowTitle("Ошибка")
        msgBox.setStandardButtons(QMessageBox.Ok)
        msgBox.exec_()
        self.window_stap1.num_expert.clear()
        self.window_stap1.num_alter.clear()
        # self.create_buttons(self.window_stap2)

    def go_stap3(self):
        try:
            table = self.window_stap2.tableWidget.model().index
            table_temp = numpy.zeros((self.num_alters, self.num_alters))
            for i in range(self.num_alters):
                for j in range(self.num_alters):
                    if not (int(table(i, j).data()) == 0 or int(table(i, j).data()) == 1):
                        self.window_stap2.tableWidget.clear()
                        # print("1")
                        self.error_stap2()
                        return
                    table_temp[i][j] = int(table(i, j).data())

            for i in range(0, self.num_alters):
                for j in range(i + 1, self.num_alters):
                    if table_temp[i][j] == table_temp[j][i]:
                        self.window_stap2.tableWidget.clear()
                        # print("2")
                        self.error_stap2()
                        return
                if table_temp[i][i] == 0:
                    self.window_stap2.tableWidget.clear()
                    # print("3")
                    self.error_stap2()
                    return

            rangs = table_temp.sum(axis=0)[:]

            set_rangs = set(rangs)
            if len(rangs) != len(set_rangs):
                self.window_stap2.tableWidget.clear()
                # print("4")
                self.error_stap2()
                return

            self.rank_matrix = numpy.append(self.rank_matrix, rangs)
            self.rank_matrix = self.rank_matrix.reshape(
                (int_r(self.rank_matrix.size / self.num_alters), self.num_alters)
            )

            self.experts_tables = numpy.append(self.experts_tables, table_temp)

            # print(self.experts)

            if int_r(self.experts_tables.size / (self.num_alters ** 2)) == self.num_experts:
                self.experts_tables = self.experts_tables.reshape(
                    (int_r(self.experts_tables.size / (self.num_alters ** 2)), self.num_alters, self.num_alters))

                self.generalized_matrix = self.experts_tables.sum(axis=0)[:] / self.num_experts
                self.generalized_matrix = self.generalized_matrix.reshape(self.num_alters, self.num_alters)

                self.resize(self.window_stap3.size())
                self.window_stap3.tableWidget.setRowCount(self.num_alters)
                self.window_stap3.tableWidget.setColumnCount(self.num_alters)
                top_table = self.window_stap3.tableWidget.geometry().top()
                width_table = 35 * self.num_alters + 17
                height_table = 30 * self.num_alters + 23
                self.window_stap3.tableWidget.setGeometry(
                    QtCore.QRect(
                        ((self.size().width() - width_table) // 2),
                        top_table,
                        width_table,
                        height_table
                    )
                )

                for i in range(self.num_alters):
                    for j in range(self.num_alters):
                        self.window_stap3.tableWidget.setItem(
                            i, j, QtWidgets.QTableWidgetItem(f"{int_r(self.generalized_matrix[i][j])}")
                        )

                self.window_stap3.tableWidget_2.setRowCount(1)
                self.window_stap3.tableWidget_2.setColumnCount(self.num_alters)
                top_table = self.window_stap3.tableWidget_2.geometry().top()
                width_table = 35 * self.num_alters + 17
                height_table = 53
                self.window_stap3.tableWidget_2.setGeometry(
                    QtCore.QRect(
                        ((self.size().width() - width_table) // 2),
                        top_table,
                        width_table,
                        height_table
                    )
                )
                summ = []
                for i in range(self.num_alters):
                    summ_temp = 0
                    for j in range(self.num_alters):
                        summ_temp += int_r(self.generalized_matrix[j][i])
                    summ = numpy.append(summ, summ_temp)

                for i in range(self.num_alters):
                    self.window_stap3.tableWidget_2.setItem(
                        0, i, QtWidgets.QTableWidgetItem(f"{int_r(summ[i])}")
                    )

                self.concordazhiya = (12 * sum(
                    (self.rank_matrix.sum(axis=0) - (self.rank_matrix.sum() * (1/self.num_alters))) ** 2
                )) / (self.num_experts ** 2 * (self.num_alters ** 3 - self.num_alters))

                self.window_stap3.label_4.setText("{0:.4f}".format(self.concordazhiya))
                self.stacked.setCurrentIndex(2)
                return

            self.window_stap2.label.setText(
                f"Эксперт {int_r(self.experts_tables.size / (self.num_alters ** 2)) + 1}"
            )
            self.window_stap2.tableWidget.clear()
        except Exception as _ex:
            print(_ex)


def int_r(num):
    num = int(num + (0.5 if num > 0 else -0.5))
    return num


if __name__ == '__main__':
    from sys import argv, exit

    app = QtWidgets.QApplication(argv)
    window = MainWindow()
    window.resize(window.window_stap1.size())
    window.show()
    exit(app.exec_())
