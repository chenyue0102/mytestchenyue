#ifndef MQTTSERVER_H
#define MQTTSERVER_H

#include <QtWidgets/QWidget>
#include "ui_mqttserver.h"
#include "simplemutex.h"

class SimpleThread;
class mqttserver : public QWidget
{
	Q_OBJECT

public:
	mqttserver(QWidget *parent = 0);
	~mqttserver();

public Q_SLOTS:
	void onStart();
	void onStop();

private:
	static void* threadProc(void* arg);
	void innerThreadProc();

private:
	Ui::mqttserverClass ui;
	SimpleThread *mThread;
	SimpleMutex mMutex;
	QString mListenPort;
	bool mExit;
};

#endif // MQTTSERVER_H
