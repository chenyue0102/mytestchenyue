#pragma once

#include <QtWidgets/QWidget>
#include "ui_testqtweb.h"

class testqtweb : public QWidget
{
	Q_OBJECT

public:
	testqtweb(QWidget *parent = Q_NULLPTR);
public slots:
	void onRunScript();
private:
	Ui::testqtwebClass ui;
};
