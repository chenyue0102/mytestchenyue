#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import random
from PySide2.QtWidgets import (QApplication, QLabel, QPushButton,
                               QVBoxLayout, QWidget, QTextEdit)
from PySide2.QtCore import Slot, Qt
from ui_test import Ui_Form
import math
import http.client
import urllib

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.maximumWidth = 800
        self.hello = ["Hallo Welt", "你好，世界", "Hei maailma",
            "Hola Mundo", "Привет мир"]

        self.button = QPushButton("Click me!")
        self.text = QTextEdit("Hello World")
        self.text.wordWrap = True
        self.text.maximumWidth = 800
        self.text.setAlignment(Qt.AlignCenter)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

        # Connecting the signal
        self.button.clicked.connect(self.magic)

    @Slot()
    def magic(self):
        #self.text.setText(random.choice(self.hello))
        #self.text.setText(str(math.pi) + '')
        con = http.client.HTTPConnection('www.baidu.com')
        con.port = 80
        con.request('GET', '')
        response = con.getresponse()
        self.text.setText(str(math.pi) + str(response.getheaders()))
        global test
        test = QWidget(None, Qt.Dialog)
        test.setAttribute(Qt.WA_DeleteOnClose)
        ui = Ui_Form()
        ui.setupUi(test)
        test.show()
		

if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())

