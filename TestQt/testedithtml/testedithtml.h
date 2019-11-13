#pragma once

#include <QtWidgets/QWidget>
#include <QWebChannel>
#include "ui_testedithtml.h"

class testedithtml : public QWidget
{
	Q_OBJECT
Q_SIGNALS:
	void notifyAddMsg(int id, const QString &name, const QString &text);
public:
	testedithtml(QWidget *parent = Q_NULLPTR);
	~testedithtml();
public slots:
	void onReload();
	void onAdd();
private:
	Ui::testedithtmlClass ui;
	QWebChannel *m_webChannel;
};
