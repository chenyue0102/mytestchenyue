#include "testqtweb.h"
#include <QWebEngineSettings>
#include <QFile>
#include "MyWebChannel.h"

testqtweb::testqtweb(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.web->load(QUrl("file:///./1.html"));
	QWebEnginePage *page = ui.web->page();
	MyWebChannel *webChannel = new MyWebChannel(this);
	webChannel->registerObject("webobj", webChannel);
	page->setWebChannel(webChannel);

	connect(ui.pushButtonRunScript, SIGNAL(clicked()), SLOT(onRunScript()));
}

void testqtweb::onRunScript()
{
	ui.web->page()->runJavaScript("showAlert()");
}