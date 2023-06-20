#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include "ui_tcpserver.h"
#include "simpletcpserver.h"
#include "simpletcpclient.h"
#include <vector>

class tcpserver : public QWidget, public SimpleTcpServer::ICallback
{
	Q_OBJECT

Q_SIGNALS:
	void signalMsg(const QString &msg);
	void signalAcceptTcpClient(const QByteArray &d);

public:
	tcpserver(QWidget *parent = 0);
	~tcpserver();

public Q_SLOTS:
	void onStart();
	void onStop();
	void onLog(const QString &msg);
	void onAcceptTcpClient(const QByteArray &d);

protected:
	bool onAcceptTcpClient(SOCKET s, const sockaddr_in &addr)override;

private:
	Ui::tcpserverClass ui;
	SimpleTcpServer *mServer;
};

#endif // TCPSERVER_H
