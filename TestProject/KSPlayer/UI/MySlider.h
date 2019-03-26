#pragma once

#include <QSlider>

class MySlider : public QSlider
{
	Q_OBJECT

public:
	MySlider(QWidget *parent);
	~MySlider();
Q_SIGNALS:
	void signalClick(int position);
protected:
	virtual void mousePressEvent(QMouseEvent *ev)override;
};
