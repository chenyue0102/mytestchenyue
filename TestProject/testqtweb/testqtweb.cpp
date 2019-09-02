#include "testqtweb.h"
#include <QWebEngineSettings>
#include <QFile>
#include <QMessageBox>
#include "MyWebChannel.h"

testqtweb::testqtweb(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.web->load(QUrl("file:///./1.html"));
	connect(ui.pushButtonRunScript, SIGNAL(clicked()), SLOT(onRunScript()));
	connect(ui.pushButtonBack, SIGNAL(clicked()), SLOT(onBack()));

	//ui.web->load(QUrl("https://tweixin.kaishustory.com/h5/qrcodeLogin/mtest/login"));
	QWebEnginePage *page = ui.web->page();
	MyWebChannel *webChannel = new MyWebChannel(this);
	webChannel->registerObject("webobj", this);
	page->setWebChannel(webChannel);
}

void testqtweb::onRunScript()
{
	ui.web->page()->runJavaScript("showAlert('c++')");
}

void testqtweb::onBack()
{
	bool b = ui.web->page()->action(QWebEnginePage::Back)->isEnabled();
	if (b)
	{
		ui.web->triggerPageAction(QWebEnginePage::Back);
	}
	else
	{
		close();
	}
}

void testqtweb::getAppInfos(const QString & funName)
{
	qDebug() << funName;
	QString str = QStringLiteral("window.HybridFunc.%1('{\"test\":1}\n')").arg(funName);
	ui.web->page()->runJavaScript(str);
}

void testqtweb::showMsgBox(const QString &text)
{
	QMessageBox::warning(nullptr, u8"ÌבÊ¾", u8"MyWebChannel::showMsgBox " + text);
}