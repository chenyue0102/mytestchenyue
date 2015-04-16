#include "testqml.h"
#include <QtWidgets/QApplication>
#include "TKUserInfo.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>


TKUserInfo UserInfo;
QContectModel ContectModel;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TestQml w;
	
	if (1)
	{
		//w.show();
	}
	
	QQmlApplicationEngine engine;
	if (1)
	{
		qmlRegisterType<QUINotify>("test.QUINotify", 1, 0, "QUINotify");
		qmlRegisterType<QContectModel>("test.QContectModel", 1, 0, "QContectModel");
		UserInfo._userID = 123456;
		UserInfo._userNickName = QString::fromLocal8Bit("ÓÃ»§êÇ³Æ123456");
		engine.rootContext()->setContextProperty("UserInfo", &UserInfo);
		engine.rootContext()->setContextProperty("ContectModel", &ContectModel);
		QUrl url = QUrl::fromLocalFile("main.qml");
		engine.load(url);

	}

	return a.exec();
}
