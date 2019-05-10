#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestGraphicsView.h"

class MyGraphicsScene;
class TestGraphicsView : public QWidget
{
	Q_OBJECT

public:
	TestGraphicsView(QWidget *parent = Q_NULLPTR);
public slots:
	void onAddText();
	void onRefresh();
	void onAddObj();
private:
	Ui::TestGraphicsViewClass ui;
	MyGraphicsScene *scene;
};
