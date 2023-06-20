#pragma once

#include <QWidget>
#include "ui_tcpclient.h"
#include "simpletcpheader.h"
#include "simpletcpclient.h"

class tcpclient : public QWidget, public SimpleTcpClient::ITcpCallback
{
	Q_OBJECT

Q_SIGNALS:
	void signalMsg(const QString &msg);

public:
    tcpclient(QWidget *parent = 0);
	~tcpclient();

public:
	void setSocket(SOCKET s, const sockaddr_in &addr);

private Q_SLOTS:
	void onLog(const QString &msg);
	void onSend();
	void onClickClose();

private:
	//连接关闭
	void onClose();
	//连接结果回馈
	void onConnect(bool success);
	void onRecv(void *data, uint32_t len);

private:
	Ui::tcpclient ui;
	SimpleTcpClient *mClient;
};
