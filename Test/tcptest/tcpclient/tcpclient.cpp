#include "tcpclient.h"
#include "tcpclientwidget.h"

tcpclient::tcpclient(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonCreate, SIGNAL(clicked()), SLOT(onCreate()));
}

tcpclient::~tcpclient()
{

}

void tcpclient::onCreate()
{
	tcpclientwidget *w = new tcpclientwidget();
	QString ip = ui.lineEdit->text();
	w->setIpAddress(ip);
	w->setAttribute(Qt::WA_DeleteOnClose, true);
	ui.verticalLayoutTcpContainer->addWidget(w);
}
