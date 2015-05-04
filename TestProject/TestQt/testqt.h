#ifndef TESTQT_H
#define TESTQT_H

#include <QtWidgets/QMainWindow>
#include "ui_testqt.h"

class TestQt : public QMainWindow
{
	Q_OBJECT

public:
	TestQt(QWidget *parent = 0);
	~TestQt();

private:
	Ui::TestQtClass ui;
};

#endif // TESTQT_H
