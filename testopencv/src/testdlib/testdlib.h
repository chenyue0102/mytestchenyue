#pragma once

#include <QtWidgets/QWidget>
#include "ui_testdlib.h"

class testdlib : public QWidget
{
	Q_OBJECT

public:
	testdlib(QWidget *parent = Q_NULLPTR);

private:
	Ui::testdlibClass ui;
};
