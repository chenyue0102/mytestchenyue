#pragma once

#include <QWidget>
#include "ui_MyWidget.h"

class MyWidget : public QWidget
{
	Q_OBJECT

public:
	MyWidget(QWidget *parent = Q_NULLPTR);
	~MyWidget();
protected:
	virtual void mouseMoveEvent(QMouseEvent *event)override;
private:
	Ui::MyWidget ui;
};
