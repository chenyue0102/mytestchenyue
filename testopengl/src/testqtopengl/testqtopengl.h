#pragma once

#include <QtWidgets/QWidget>
#include "ui_testqtopengl.h"

class testqtopengl : public QWidget
{
	Q_OBJECT

public:
	testqtopengl(QWidget *parent = Q_NULLPTR);

private:
	Ui::testqtopenglClass ui;
};
