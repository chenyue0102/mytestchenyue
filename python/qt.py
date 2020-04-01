#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import random
#from PyQt5.QtWidgets import QApplication, QWidget
from PySide2 import QtCore, QtWidgets, QtGui

class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        self.button = QtWidgts.QPushButton("ok")
        self.text = QWidgets.QLabel("tip")
        self.layout = QWidgets.QVBoxLayout()
        self.layout.addQWidget(self.text)
        self.layout.addQWidget(self.button)
        self.setLayout(self.layout)
        self.button.clicked.connect(self.onclick)

    def onclick(self):
        self.close()

if __name__ == '__main__':
    myapp = QApplication(sys.argv)
    mywidget = MyWidget()
    mywidget.show()
    sys.exit(myapp.exec_())

