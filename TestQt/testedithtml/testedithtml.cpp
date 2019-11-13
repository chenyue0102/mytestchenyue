#include "testedithtml.h"


testedithtml::testedithtml(QWidget *parent)
	: QWidget(parent)
	, m_webChannel(new QWebChannel(this))
{
	ui.setupUi(this);
	connect(ui.pushButtonReload, SIGNAL(clicked()), SLOT(onReload()));
	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(onAdd()));

	QWebEnginePage *page = ui.webEngineView->page();
	m_webChannel->registerObject("webobj", this);
	page->setWebChannel(m_webChannel);
}

testedithtml::~testedithtml()
{
	QWebEnginePage *page = ui.webEngineView->page();
	page->setWebChannel(nullptr);
	m_webChannel->deregisterObject(this);
}

void testedithtml::onAdd()
{
	QString str = QStringLiteral("appendChatText(%1,'%2','%3')").arg(1).arg(u8"小马'").arg(u8"得得得");
	QWebEnginePage *p = ui.webEngineView->page();
	if (nullptr != p)
	{
		//p->runJavaScript(str);
	}
	emit notifyAddMsg(1, u8"小马'", u8"得得得");
}

void testedithtml::onReload()
{
	ui.webEngineView->load(QUrl("file:///./1.html"));
}

