#include "testqtsignalslot.h"
#include <string>
#include <QDebug>


Q_DECLARE_METATYPE(Test);
testqtsignalslot::testqtsignalslot(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), SLOT(onClickBtn()));
	connect(ui.pushButtonQueue, SIGNAL(clicked()), SLOT(onClickBtnQueue()));
	connect(ui.pushButtonVariant, SIGNAL(clicked()), SLOT(onClickBtnVariant()));
	qRegisterMetaType<Test>("Test");
	qRegisterMetaType<Test>("Test&");
}

void testqtsignalslot::onClickBtn()
{
	connect(this, SIGNAL(notifyTest(const Test&)), SLOT(onTest(const Test&)));
	Test t;
	t.s = "abcd";
	emit notifyTest(t);
	disconnect(SIGNAL(notifyTest(const Test&)), this, SLOT(onTest(const Test&)));
}

void testqtsignalslot::onClickBtnQueue()
{
	connect(this, SIGNAL(notifyTest(const Test&)), this, SLOT(onTest(const Test&)), Qt::QueuedConnection);
	Test t;
	t.s = "abcd";
	emit notifyTest(t);
	disconnect(SIGNAL(notifyTest(const Test&)), this, SLOT(onTest(const Test&)));
}

void testqtsignalslot::onClickBtnVariant()
{
	Test t;
	t.s = "abcd";
	QVariant v = QVariant::fromValue(t);

	bool b = v.canConvert<Test>();
	Test t2 = v.value<Test>();
	qDebug() << t2.s.c_str();
}

void testqtsignalslot::onTest(const Test &test)
{
	qDebug() << test.s.c_str();
}