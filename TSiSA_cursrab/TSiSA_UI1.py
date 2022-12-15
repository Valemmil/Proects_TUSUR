# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\TSiSA_UI1.ui'
#
# Created by: PyQt5 UI code generator 5.15.7
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Window_stap1(object):
    def setupUi(self, Window_stap1):
        Window_stap1.setObjectName("Window_stap1")
        Window_stap1.setEnabled(True)
        Window_stap1.resize(270, 290)
        Window_stap1.setStyleSheet("background-color: rgb(153, 255, 148);")
        self.centralwidget = QtWidgets.QWidget(Window_stap1)
        self.centralwidget.setObjectName("centralwidget")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(33, 20, 204, 20))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.num_expert = QtWidgets.QTextEdit(self.centralwidget)
        self.num_expert.setGeometry(QtCore.QRect(35, 50, 200, 40))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.num_expert.setFont(font)
        self.num_expert.setTabletTracking(False)
        self.num_expert.setStyleSheet("background-color: rgb(211, 255, 211);")
        self.num_expert.setTabChangesFocus(True)
        self.num_expert.setObjectName("num_expert")
        self.btn_save = QtWidgets.QPushButton(self.centralwidget)
        self.btn_save.setGeometry(QtCore.QRect(35, 240, 200, 40))
        self.btn_save.setStyleSheet("background-color: rgb(164, 170, 255);")
        self.btn_save.setObjectName("btn_save")
        self.num_alter = QtWidgets.QTextEdit(self.centralwidget)
        self.num_alter.setGeometry(QtCore.QRect(35, 160, 200, 40))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.num_alter.setFont(font)
        self.num_alter.setTabletTracking(False)
        self.num_alter.setStyleSheet("background-color: rgb(211, 255, 211);")
        self.num_alter.setTabChangesFocus(True)
        self.num_alter.setObjectName("num_alter")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(20, 130, 230, 20))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        Window_stap1.setCentralWidget(self.centralwidget)

        self.retranslateUi(Window_stap1)
        QtCore.QMetaObject.connectSlotsByName(Window_stap1)

    def retranslateUi(self, Window_stap1):
        _translate = QtCore.QCoreApplication.translate
        Window_stap1.setWindowTitle(_translate("Window_stap1", "Групповой парный анализ - Шаг 1"))
        self.label.setText(_translate("Window_stap1", "Количество экспертов"))
        self.btn_save.setText(_translate("Window_stap1", "Сохранить"))
        self.label_2.setText(_translate("Window_stap1", "Количество альтернатив"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Window_stap1 = QtWidgets.QMainWindow()
    ui = Ui_Window_stap1()
    ui.setupUi(Window_stap1)
    Window_stap1.show()
    sys.exit(app.exec_())
