#include "testedithtml.h"


testedithtml::testedithtml(QWidget *parent)
	: QWidget(parent)
	, m_webChannel(new QWebChannel(this))
{
	ui.setupUi(this);
	connect(ui.pushButtonReload, SIGNAL(clicked()), SLOT(onReload()));

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

void testedithtml::onReload()
{
	ui.webEngineView->load(QUrl("file:///./1.html"));
}

