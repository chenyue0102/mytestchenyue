#include "tcpserver.h"
#include "tcpclient.h"


tcpserver::tcpserver(QWidget *parent)
	: QWidget(parent)
	, mServer(NULL)
{
	ui.setupUi(this);
	connect(ui.pushButtonStart, SIGNAL(clicked()), SLOT(onStart()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), SLOT(onStop()));
	connect(this, SIGNAL(signalAcceptTcpClient(const QByteArray &)), SLOT(onAcceptTcpClient(const QByteArray &)), Qt::QueuedConnection);
}

tcpserver::~tcpserver()
{

}

void tcpserver::onStart()
{
	onStop();
	mServer = new SimpleTcpServer();
	mServer->setPort(5000);
	mServer->setCallback(this);
	mServer->startServer();
	ui.label->setText("start");
}

void tcpserver::onStop()
{
	if (NULL != mServer) {
		mServer->stopServer();
		delete mServer;
		mServer = NULL;
	}
	ui.label->setText("stop");
}

void tcpserver::onLog(const QString & msg)
{
	
}

void tcpserver::onAcceptTcpClient(const QByteArray & d)
{
	const char *data = d.data();
	SOCKET s;
	sockaddr_in addr;
	memcpy(&s, data, sizeof(s));
	data += sizeof(s);
	memcpy(&addr, data, sizeof(addr));
	tcpclient *c = new tcpclient();
	c->setSocket(s, addr);
	ui.verticalLayoutTcpClientContainer->addWidget(c);
}

bool tcpserver::onAcceptTcpClient(SOCKET s, const sockaddr_in & addr)
{
	QByteArray d;
	d.append((const char*)&s, sizeof(s));
	d.append((const char*)&addr, sizeof(addr));
	emit signalAcceptTcpClient(d);
	return true;
}
