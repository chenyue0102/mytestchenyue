#include "KSDoodling.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KSDoodling w;
	//w.show();
#ifdef _DEBUG
	w.showDesktop();
#endif
	return a.exec();
}
