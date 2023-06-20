#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include "ui_tcpclient.h"

class tcpclient : public QWidget
{
	Q_OBJECT

public:
	tcpclient(QWidget *parent = 0);
	~tcpclient();

public Q_SLOTS:
	void onCreate();

private:
	Ui::tcpclientClass ui;
};

#endif // TCPCLIENT_H
