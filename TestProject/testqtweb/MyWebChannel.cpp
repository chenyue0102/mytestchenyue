#include "MyWebChannel.h"
#include <QMessageBox>

MyWebChannel::MyWebChannel(QObject *parent)
	: QWebChannel(parent)
{
}

MyWebChannel::~MyWebChannel()
{
}

void MyWebChannel::showMsgBox()
{
	QMessageBox::warning(nullptr, u8"��ʾ", u8"MyWebChannel::showMsgBox");
}