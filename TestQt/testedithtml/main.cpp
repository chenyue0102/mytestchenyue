#include "testedithtml.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testedithtml w;
	w.show();
	return a.exec();
}
