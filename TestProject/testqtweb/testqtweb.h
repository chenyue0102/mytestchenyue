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
	void onBack();
public slots:
	void showMsgBox(const QString &text);
	void getAppInfos(const QString &funName);
private:
	Ui::testqtwebClass ui;
};
