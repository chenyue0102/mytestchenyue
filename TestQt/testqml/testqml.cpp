#include "testqml.h"
#include <QMetaObject>
#include <QQmlContext>
#include <QQuickItem>
#include <algorithm>
#include "MyQuickWidget.h"

template<typename T>
static typename std::enable_if<std::is_signed<typename T>::value, bool>::type innerIsTypeNumber(const std::string &value)
{
	bool ret = false;
	try
	{
		long long i64Value = std::stoll(value);
		auto max = std::numeric_limits<T>::max();
		auto min = std::numeric_limits<T>::min();
		if (i64Value <= max && i64Value >= min)
		{
			ret = true;
		}
	}
	catch (...)
	{
		
	}
	return ret;
}

template<typename T>
static typename std::enable_if<std::is_unsigned<typename T>::value, bool>::type innerIsTypeNumber(const std::string &value)
{
	bool ret = false;
	try
	{
		//第一个是负号
		if (!value.empty()
			&& value[0] != '-')
		{
			unsigned long long u64Value = std::stoull(value);
			auto max = std::numeric_limits<T>::max();
			auto min = std::numeric_limits<T>::min();
			if (u64Value <= max && u64Value >= min)
			{
				ret = true;
			}
		}
	}
	catch (...)
	{

	}
	return ret;
}

testqml::testqml(QWidget *parent)
	: QWidget(parent)
{
	std::string strNumber = "59000000000000000000000000000000000000000000000000000000000000";
	bool b = innerIsTypeNumber<unsigned int>(strNumber);
	std::vector<QString> ls = { "a", "b" };
	QStringList ls2;
	std::copy(ls.begin(), ls.end(), std::insert_iterator<QStringList>(ls2, ls2.end()));

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
	connect(ui.pushButtonAdd3, SIGNAL(clicked()), SLOT(onAddQml3()));
	connect(ui.pushButtonAdd4, SIGNAL(clicked()), SLOT(onAddQml4()));
	connect(ui.pushButtonRight, SIGNAL(clicked()), SLOT(onCallRight()));
	connect(ui.pushButtonWrong, SIGNAL(clicked()), SLOT(onCallWrong()));
}

void testqml::onAddQml()
{
	reallocwidget();
	QUrl url("file:///C:/Users/EDZ/Desktop/student/src/bin/student/skin/live/qml/QuestionResult.qml");
	ui.quickWidget->setSource(url);
	auto *obj = ui.quickWidget->rootContext();
	bool win = (rand() % 2 == 0) ? true : false;
	QString gif;
	if (win)
	{
		gif = "./blueright.gif";
	}
	else
	{
		gif = "./bluewrong.gif";
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
	reallocwidget();
	QUrl url("test2.qml");
	ui.quickWidget->setSource(url);
}

void testqml::onAddQml3()
{
	reallocwidget();
	QUrl url("test3.qml");
	ui.quickWidget->setSource(url);
}

void testqml::onAddQml4()
{
	reallocwidget();
	QUrl url("BeginAnswer.qml");
	ui.quickWidget->setSource(url);
}

void testqml::reallocwidget()
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
	//quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

	ui.verticalLayout->addWidget(quickWidget);
}
