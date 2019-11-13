#pragma once

#include <QtWidgets/QWidget>
#include "ui_testedithtml.h"

class testedithtml : public QWidget
{
	Q_OBJECT

public:
	testedithtml(QWidget *parent = Q_NULLPTR);
public slots:
	void onReload();
private:
	Ui::testedithtmlClass ui;
};
