#ifndef TESTQML_H
#define TESTQML_H

#include <QtWidgets/QDialog>
#include "ui_testqml.h"

class TestQml : public QDialog
{
	Q_OBJECT

public:
	TestQml(QWidget *parent = 0);
	~TestQml();

private:
	Ui::TestQmlClass ui;
};

#endif // TESTQML_H
