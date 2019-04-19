#include "testqtweb.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testqtweb w;
	w.show();
	return a.exec();
}
