from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer
from TSiSA_UI1 import Ui_Window_stap1
from TSiSA_UI2 import Ui_Window_stap2
from TSiSA_UI3 import Ui_Window_stap3
from time import sleep


# def main():
#     import sys
#     app = QtWidgets.QApplication(sys.argv)
#     Window_stap1 = QtWidgets.QMainWindow()
#     ui1 = Ui_Window_stap1()
#     ui1.setupUi(Window_stap1)
#     Window_stap1.show()
#
#     Window_stap2 = QtWidgets.QMainWindow()
#     ui2 = Ui_Window_stap2()
#     ui2.setupUi(Window_stap2)
#     Window_stap2.show()
#
#     Window_stap3 = QtWidgets.QMainWindow()
#     ui3 = Ui_Window_stap3()
#     ui3.setupUi(Window_stap3)
#     Window_stap3.show()
#
#     sys.exit(app.exec_())
#
#
# if __name__ == '__main__':
#     main()

# from PyQt5 import QtCore, QtGui, QtWidgets
# from PyQt5.Qt import *
#

# class Ui_Win1(object):
#     def setupUi(self, Win1):
#         Win1.setObjectName("Win1")
#         Win1.resize(450, 800)
#         self.widgetWin1 = QtWidgets.QWidget(Win1)
#         self.widgetWin1.setObjectName("widgetWin1")
#
#         self.text1 = QtWidgets.QLabel(self.widgetWin1)
#         self.text1.setGeometry(QtCore.QRect(197, 378, 56, 16))
#         self.text1.setObjectName("text1")
#
#         Win1.setCentralWidget(self.widgetWin1)
#         self.retranslateUi(Win1)
#         QtCore.QMetaObject.connectSlotsByName(Win1)
#
#     def retranslateUi(self, Win1):
#         _translate = QtCore.QCoreApplication.translate
#         Win1.setWindowTitle(_translate("Win1", "MainWindow"))
#         self.text1.setText(_translate("Win1", "Win1"))
#
#
# class Ui_Win2(object):
#     def setupUi(self, Win2):
#         Win2.setObjectName("Win2")
#         Win2.resize(450, 800)
#         self.widgetWin2 = QtWidgets.QWidget(Win2)
#         self.widgetWin2.setObjectName("widgetWin2")
#         self.text2 = QtWidgets.QLabel(self.widgetWin2)
#         self.text2.setGeometry(QtCore.QRect(197, 378, 56, 16))
#         self.text2.setObjectName("text2")
#
#         Win2.setCentralWidget(self.widgetWin2)
#         self.retranslateUi(Win2)
#         QtCore.QMetaObject.connectSlotsByName(Win2)
#
#     def retranslateUi(self, Win2):
#         _translate = QtCore.QCoreApplication.translate
#         Win2.setWindowTitle(_translate("Win2", "MainWindow"))
#         self.text2.setText(_translate("Win2", "Win2"))
#
#
# class Ui_Win3(object):
#     def setupUi(self, Win3):
#         Win3.setObjectName("Win3")
#         Win3.resize(450, 800)
#         self.widgetWin3 = QtWidgets.QWidget(Win3)
#         self.widgetWin3.setObjectName("widgetWin3")
#         self.text3 = QtWidgets.QLabel(self.widgetWin3)
#         self.text3.setGeometry(QtCore.QRect(197, 378, 56, 16))
#         self.text3.setObjectName("text3")
#
#         Win3.setCentralWidget(self.widgetWin3)
#
#         self.retranslateUi(Win3)
#         QtCore.QMetaObject.connectSlotsByName(Win3)
#
#     def retranslateUi(self, Win3):
#         _translate = QtCore.QCoreApplication.translate
#         Win3.setWindowTitle(_translate("Win3", "MainWindow"))
#         self.text3.setText(_translate("Win3", "Win3"))


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

        # +++ vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    #     self.create_buttons(self.window_stap1)
    #
    # def create_buttons(self, parent):
    #     bnt = QtWidgets.QPushButton("Win1", parent)
    #     #        self.bnt.setGeometry(QtCore.QRect(0, 772, 150, 28)) # установите свою геометрию
    #     bnt.setGeometry(QtCore.QRect(0, 572, 150, 28))
    #
    #     bnt_2 = QtWidgets.QPushButton("Win2", parent)
    #     #        self.bnt_2.setGeometry(QtCore.QRect(150, 772, 150, 28))
    #     bnt_2.setGeometry(QtCore.QRect(150, 572, 150, 28))
    #
    #     bnt_3 = QtWidgets.QPushButton("Win3", parent)
    #     #        self.bnt_3.setGeometry(QtCore.QRect(300, 772, 150, 28))
    #     bnt_3.setGeometry(QtCore.QRect(300, 572, 150, 28))
    #
    #     bnt.clicked.connect(self.go_win1)
    #     bnt_2.clicked.connect(self.go_win2)
    #     bnt_3.clicked.connect(self.go_win3)
    #     bnt.show()
    #     bnt_2.show()
    #     bnt_3.show()
    #
    # def go_stap1(self):
    #     self.resize(self.window_stap1.size())
    #     self.stacked.setCurrentIndex(0)
    #     # self.create_buttons(self.window_stap1)

    def go_stap2(self):
        if self.window_stap1.num_expert.toPlainText().isdigit() and self.window_stap1.num_alter.toPlainText().isdigit():
            self.resize(self.window_stap2.size())
            self.stacked.setCurrentIndex(1)
        # self.create_buttons(self.window_stap2)

    def go_stap3(self):
        self.window_stap2.tableWidget.items()
        self.resize(self.window_stap3.size())
        self.stacked.setCurrentIndex(2)
        # self.create_buttons(self.window_stap3)
    # +++ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


if __name__ == '__main__':
    from sys import argv, exit

    app = QtWidgets.QApplication(argv)
    window = MainWindow()
    window.resize(window.window_stap1.size())
    # window.resize(450, 650)  # <---- (450, 800)
    window.show()
    exit(app.exec_())
