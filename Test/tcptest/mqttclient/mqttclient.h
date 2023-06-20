#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QtWidgets/QWidget>
#include "ui_mqttclient.h"

class mqttclient : public QWidget
{
	Q_OBJECT

public:
	mqttclient(QWidget *parent = 0);
	~mqttclient();

public Q_SLOTS:
	void onCreateNode1();
	void onCreateNode2();

private:
	Ui::mqttclientClass ui;
};

#endif // MQTTCLIENT_H
