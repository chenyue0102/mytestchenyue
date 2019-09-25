#include "testqtopengl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testqtopengl w;
	w.show();
	return a.exec();
}
