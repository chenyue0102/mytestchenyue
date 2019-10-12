#include "testLinearGradient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testLinearGradient w;
	w.show();
	return a.exec();
}
