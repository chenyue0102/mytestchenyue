#include "YUVRender.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	YUVRender w;
	w.show();
	return a.exec();
}
