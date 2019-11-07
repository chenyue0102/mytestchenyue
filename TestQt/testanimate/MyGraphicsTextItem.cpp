#include "MyGraphicsTextItem.h"

MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsItem *parent)
	: QGraphicsTextItem(parent)
{
}

MyGraphicsTextItem::MyGraphicsTextItem(const QString & text, QGraphicsItem * parent)
	: QGraphicsTextItem(text, parent)
{
}

MyGraphicsTextItem::~MyGraphicsTextItem()
{
}
