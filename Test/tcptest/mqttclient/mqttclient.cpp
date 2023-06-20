#include "mqttclient.h"
#include "node1widget.h"

mqttclient::mqttclient(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonNode1, SIGNAL(clicked()), SLOT(onCreateNode1()));
	connect(ui.pushButtonNode2, SIGNAL(clicked()), SLOT(onCreateNode2()));
}

mqttclient::~mqttclient()
{

}

void mqttclient::onCreateNode2()
{
	Node1Widget *node1 = new Node1Widget();
	node1->setServerAddress(ui.lineEdit->text());
	node1->setSub("msg/node1");
	node1->setPub("msg/node2");
	node1->setAttribute(Qt::WA_DeleteOnClose, true);
	ui.verticalLayoutNodeContainer->addWidget(node1);
}

void mqttclient::onCreateNode1()
{
	Node1Widget *node1 = new Node1Widget();
	node1->setServerAddress(ui.lineEdit->text());
	node1->setSub("msg/node2");
	node1->setPub("msg/node1");
	node1->setAttribute(Qt::WA_DeleteOnClose, true);
	ui.verticalLayoutNodeContainer->addWidget(node1);
}
