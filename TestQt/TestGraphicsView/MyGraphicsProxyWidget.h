#pragma once

#include <QGraphicsProxyWidget>

class MyGraphicsProxyWidget : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
	MyGraphicsProxyWidget(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());
	~MyGraphicsProxyWidget();
public:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};
