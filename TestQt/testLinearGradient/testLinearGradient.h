#pragma once

#include <QtWidgets/QWidget>
#include "ui_testLinearGradient.h"

class testLinearGradient : public QWidget
{
	Q_OBJECT

public:
	testLinearGradient(QWidget *parent = Q_NULLPTR);
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	Ui::testLinearGradientClass ui;
};
