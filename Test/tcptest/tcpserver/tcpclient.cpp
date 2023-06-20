#include "tcpclient.h"

tcpclient::tcpclient(QWidget *parent)
	: QWidget(parent)
	, mClient(NULL)
{
	ui.setupUi(this);
	connect(this, SIGNAL(signalMsg(const QString&)), SLOT(onLog(const QString&)), Qt::QueuedConnection);
	connect(ui.pushButtonSend, SIGNAL(clicked()), SLOT(onSend()));
	connect(ui.pushButtonClose, SIGNAL(clicked()), SLOT(onClickClose()));
}

tcpclient::~tcpclient()
{
	if (NULL != mClient) {
        mClient->closeSocket();
		delete mClient;
		mClient = NULL;
	}
}

void tcpclient::setSocket(SOCKET s, const sockaddr_in & addr)
{
	mClient = new SimpleTcpClient();
	mClient->setCallback(this);
	mClient->setSocket(s, addr);
}

void tcpclient::onSend()
{
    mClient->sendData("server msg", 10);
}

void tcpclient::onClickClose()
{
	if (NULL != mClient) {
        mClient->closeSocket();
		delete mClient;
		mClient = NULL;
	}
}

void tcpclient::onLog(const QString &msg)
{
	ui.textBrowser->append(msg);
}

void tcpclient::onClose()
{
	emit signalMsg(QString::fromLocal8Bit("断开\n"));
}

void tcpclient::onConnect(bool success)
{
	emit signalMsg(QString::fromLocal8Bit("连接??\n"));
}

void tcpclient::onRecv(void * data, uint32_t len)
{
	QByteArray d((const char*)data, len);
	emit signalMsg(QString::fromLocal8Bit(d) + "\n");
}
