#pragma once

#include <QtWidgets/QWidget>
#include "ui_testqml.h"

class testqml : public QWidget
{
	Q_OBJECT

public:
	testqml(QWidget *parent = Q_NULLPTR);
public slots:
	void onAddQml();
	void onPlayFinished();
private:
	Ui::testqmlClass ui;
};
