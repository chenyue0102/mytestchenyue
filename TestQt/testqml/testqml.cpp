#include "testqml.h"
#include <QMetaObject>
#include <QQmlContext>
#include <QQuickItem>

testqml::testqml(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
	ui.quickWidget->setAttribute(Qt::WA_TranslucentBackground);
	ui.quickWidget->setClearColor(Qt::transparent);
	ui.quickWidget->setObjectName(QStringLiteral("quickWidget"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(ui.quickWidget->sizePolicy().hasHeightForWidth());
	ui.quickWidget->setSizePolicy(sizePolicy);
	ui.quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(onAddQml()));
	connect(ui.pushButtonAdd2, SIGNAL(clicked()), SLOT(onAddQml2()));
	connect(ui.pushButtonRight, SIGNAL(clicked()), SLOT(onCallRight()));
	connect(ui.pushButtonWrong, SIGNAL(clicked()), SLOT(onCallWrong()));
}

void testqml::onAddQml()
{
	QUrl url("./test.qml");
	ui.quickWidget->setSource(url);

	auto *obj = ui.quickWidget->rootContext();
	bool win = (rand() % 2 == 0) ? true : false;
	QString gif;
	if (win)
	{
		gif = "./right.gif";
	}
	else
	{
		gif = "./wrong.gif";
	}
	QVariant returnValue;
	QString name = obj->objectName();
	QQuickItem *rootItem = ui.quickWidget->rootObject();
	name = rootItem->objectName();
	QMetaObject::invokeMethod(rootItem, "setResultGif", Q_ARG(QVariant, QVariant(win)), Q_ARG(QVariant, QVariant(gif)));

	QMetaObject::invokeMethod(rootItem, "setResultScore", Q_ARG(QVariant, QVariant(999)), Q_ARG(QVariant, QVariant(888)));
	connect(rootItem, SIGNAL(playFinished()), SLOT(onPlayFinished()));

}

void testqml::onPlayFinished()
{
//	ui.quickWidget->hide();
}

void testqml::onCallRight()
{
	QQuickItem *rootItem = ui.quickWidget->rootObject();
	QMetaObject::invokeMethod(rootItem, "setResultGif", Q_ARG(QVariant, QVariant(true)), Q_ARG(QVariant, QVariant("./right.gif")));
}

void testqml::onCallWrong()
{
	QQuickItem *rootItem = ui.quickWidget->rootObject();
	QMetaObject::invokeMethod(rootItem, "setResultGif", Q_ARG(QVariant, QVariant(false)), Q_ARG(QVariant, QVariant("./wrong.gif")));
}

void testqml::onAddQml2()
{

}
