#pragma once

#include <QGraphicsObject>

class MyGraphicsObject : public QGraphicsObject
{
	Q_OBJECT

public:
	MyGraphicsObject(QGraphicsItem *parent = 0);
	~MyGraphicsObject();
public:
	void setSize(const QSizeF &sz);
public:
	virtual QRectF boundingRect(void) const override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)override;
private:
	QSizeF m_size;
};
