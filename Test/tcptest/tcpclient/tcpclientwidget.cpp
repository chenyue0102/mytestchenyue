#include "tcpclientwidget.h"

tcpclientwidget::tcpclientwidget(QWidget *parent)
	: QWidget(parent)
	, mClient(NULL)
{
	ui.setupUi(this);

	connect(this, SIGNAL(signalMsg(const QString &)), SLOT(onLog(const QString &)), Qt::QueuedConnection);
	connect(ui.pushButtonConnect, SIGNAL(clicked()), SLOT(onConnect()));
	connect(ui.pushButtonDisconnect, SIGNAL(clicked()), SLOT(onDisconnect()));
	connect(ui.pushButtonSend, SIGNAL(clicked()), SLOT(onSend()));
}

tcpclientwidget::~tcpclientwidget()
{
	if (NULL != mClient) {
        mClient->closeSocket();
		mClient = NULL;
	}
}

void tcpclientwidget::setIpAddress(const QString & ip)
{
	mIP = ip;
}

void tcpclientwidget::onDisconnect()
{
	if (NULL != mClient) {
        mClient->closeSocket();
		mClient = NULL;
		emit signalMsg(QString::fromLocal8Bit("断开连接\n"));
	}
}

void tcpclientwidget::onSend()
{
    mClient->sendData("abc123", 6);
}

void tcpclientwidget::onLog(const QString & msg)
{
	ui.textBrowser->append(msg);
}

void tcpclientwidget::onClose()
{
	emit signalMsg(QString::fromLocal8Bit("关闭\n"));
}

void tcpclientwidget::onConnect(bool success)
{
	emit signalMsg(QString::fromLocal8Bit("连接:%1\n").arg(success ? QString::fromLocal8Bit("成功") : QString::fromLocal8Bit("失败")));
}

void tcpclientwidget::onRecv(void * data, uint32_t len)
{
	QByteArray d((const char*)data, len);
	emit signalMsg(QString::fromLatin1(d));
}

void tcpclientwidget::onConnect()
{
	onDisconnect();
	mClient = new SimpleTcpClient();
	mClient->setCallback(this);
	std::string ip = mIP.toStdString();
    mClient->connectServer(ip.c_str(), 5000);
}
