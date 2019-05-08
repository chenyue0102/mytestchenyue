#include "MyWebChannel.h"
#include <QMessageBox>
#include <QDebug>

MyWebChannel::MyWebChannel(QObject *parent)
	: QWebChannel(parent)
{
}

MyWebChannel::~MyWebChannel()
{
}