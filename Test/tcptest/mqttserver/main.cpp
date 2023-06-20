#include "mqttserver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mqttserver w;
	w.show();
	return a.exec();
}
