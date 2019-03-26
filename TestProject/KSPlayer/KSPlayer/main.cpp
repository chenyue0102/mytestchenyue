#include "KSPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KSPlayer w;
	w.show();
	return a.exec();
}
