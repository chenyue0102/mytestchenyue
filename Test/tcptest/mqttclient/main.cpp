#include "mqttclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mqttclient w;
	w.show();
	return a.exec();
}
