#include <QDebug>
#include <QMouseEvent>
#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MyWidget::~MyWidget()
{
}

void MyWidget::mouseMoveEvent(QMouseEvent * event)
{
	__super::mouseMoveEvent(event);
	qDebug() << "MyWidget::mouseMoveEvent" << event->pos();
}
