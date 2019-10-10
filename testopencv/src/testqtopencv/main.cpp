#include "testqtopencv.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testqtopencv w;
	w.show();
	return a.exec();
}
