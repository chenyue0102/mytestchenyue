#include "testqtsignalslot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testqtsignalslot w;
	w.show();
	return a.exec();
}
