#include "MyGraphicsProxyWidget.h"

MyGraphicsProxyWidget::MyGraphicsProxyWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags )
	: QGraphicsProxyWidget(parent, wFlags)
{
}

MyGraphicsProxyWidget::~MyGraphicsProxyWidget()
{
}

void MyGraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	__super::mouseMoveEvent(event);
}