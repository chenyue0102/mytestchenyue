#include "MySlider.h"
#include <QMouseEvent>

MySlider::MySlider(QWidget *parent)
	: QSlider(parent)
{
}

MySlider::~MySlider()
{
}

void MySlider::mousePressEvent(QMouseEvent * ev)
{
	__super::mousePressEvent(ev);
	if (!isSliderDown()
		&& 0 != width())
	{
		int position = ev->pos().x() * maximum() / width();
		emit signalClick(position);
	}
}
