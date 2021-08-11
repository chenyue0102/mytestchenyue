#include "MyButton.h"
#include <QDebug>
#include <QMouseEvent>

MyButton::MyButton(QWidget *parent)
	: QPushButton(parent)
{
}

MyButton::~MyButton()
{
}

void MyButton::mouseMoveEvent(QMouseEvent * event)
{
	__super::mouseMoveEvent(event);
	qDebug() << "MyButton::mouseMoveEvent" << event->pos();
}
