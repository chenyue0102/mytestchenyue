#pragma once

#include <QtWidgets/QWidget>
#include <QWebChannel>
#include "ui_testedithtml.h"

class testedithtml : public QWidget
{
	Q_OBJECT

public:
	testedithtml(QWidget *parent = Q_NULLPTR);
	~testedithtml();
public slots:
	void onReload();
private:
	Ui::testedithtmlClass ui;
	QWebChannel *m_webChannel;
};
