#include "testqml.h"
#include <QMetaObject>
#include <QQmlContext>
#include <QQuickItem>

testqml::testqml(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(onAddQml()));
}

void testqml::onAddQml()
{
	ui.quickWidget->deleteLater();
	auto &quickWidget = ui.quickWidget;

	quickWidget = new QQuickWidget(this);
	quickWidget->setObjectName(QStringLiteral("quickWidget"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(quickWidget->sizePolicy().hasHeightForWidth());
	quickWidget->setSizePolicy(sizePolicy);
	quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

	ui.verticalLayout->addWidget(quickWidget);

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
	ui.quickWidget->hide();
}
