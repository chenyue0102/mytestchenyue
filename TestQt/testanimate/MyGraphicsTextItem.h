#pragma once

#include <QGraphicsTextItem>

class MyGraphicsTextItem : public QGraphicsTextItem
{
	Q_OBJECT

	Q_PROPERTY(QString plainText READ toPlainText WRITE setPlainText)
public:
	explicit MyGraphicsTextItem(QGraphicsItem *parent = Q_NULLPTR);
	explicit MyGraphicsTextItem(const QString &text, QGraphicsItem *parent = Q_NULLPTR);
	~MyGraphicsTextItem();
};
