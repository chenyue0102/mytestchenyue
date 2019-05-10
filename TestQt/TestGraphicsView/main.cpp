#include "TestGraphicsView.h"
#include <QtWidgets/QApplication>
#include "TestGraphicsView.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TestGraphicsView v;
	v.show();
	return a.exec();
}
