#pragma once

#include <QtWidgets/QWidget>
#include "ui_testanimate.h"

class testanimate : public QWidget
{
	Q_OBJECT

public:
	testanimate(QWidget *parent = Q_NULLPTR);
public slots:
	void onLoad();
private:
	Ui::testanimateClass ui;
};
