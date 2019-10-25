#include "testdlib.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testdlib w;
	w.show();
	return a.exec();
}
