#pragma once

#include <QtWidgets/QWidget>
#include "ui_testqtsignalslot.h"

struct Test
{
	std::string s;
};
class testqtsignalslot : public QWidget
{
	Q_OBJECT

public:
	testqtsignalslot(QWidget *parent = Q_NULLPTR);
Q_SIGNALS:
	void notifyTest(const Test &test);
public slots:
	void onClickBtn();
	void onClickBtnQueue();
	void onClickBtnVariant();
	void onTest(const Test &test);
private:
	Ui::testqtsignalslotClass ui;
};
