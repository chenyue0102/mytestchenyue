#pragma once

#include <QWidget>
#include <vector>
#include "ui_node1widget.h"
#include "simplemutex.h"
#include "simplethread.h"

struct MQTTPublish {
	std::string topic;
	std::string message;
};
class Node1Widget : public QWidget
{
	Q_OBJECT

Q_SIGNALS:
	void signalMsg(const QString &msg);
	
public:
	Node1Widget(QWidget *parent = 0);
	~Node1Widget();

public:
	void setServerAddress(const QString &address);
	void setSub(const QString &sub);
	void setPub(const QString &pub);
	void publicMessage(const QString &topic, const QString &message);

public Q_SLOTS:
	void onConnect();
	void onDisconnect();
	void onPublic();
	void onLog(const QString &log);

private:
	static void* threadProc(void *arg);
	void innerThreadProc();

private:
	Ui::Node1Widget ui;
	SimpleThread *mThread;
	QString mServerAddress;
	SimpleMutex mMutex;
	bool mExit;
	QString mSub, mPub;
	std::vector< MQTTPublish> mPublics;
};
