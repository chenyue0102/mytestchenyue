#pragma once

#include <QWidget>
#include "ui_tcpclientwidget.h"
#include "simpletcpclient.h"

class tcpclientwidget : public QWidget, public SimpleTcpClient::ITcpCallback
{
	Q_OBJECT

Q_SIGNALS:
	void signalMsg(const QString &msg);

public:
    tcpclientwidget(QWidget *parent = 0);
	~tcpclientwidget();

public:
	void setIpAddress(const QString &ip);

public Q_SLOTS:
	void onConnect();
	void onDisconnect();
	void onSend();
	void onLog(const QString &msg);

private:
	//连接关闭
	void onClose()override;
	//连接结果回馈
	void onConnect(bool success)override;
	void onRecv(void *data, uint32_t len)override;

private:
	Ui::tcpclientwidget ui;
	QString mIP;
	SimpleTcpClient *mClient;
};
