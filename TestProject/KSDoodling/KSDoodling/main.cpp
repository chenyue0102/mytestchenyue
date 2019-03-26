#include "KSDoodling.h"
#include <QtWidgets/QApplication>
#include <Windows.h>
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	HANDLE hMutex = CreateMutex(nullptr, FALSE, L"KSDoodling");
	if (nullptr != hMutex
		&& ERROR_ALREADY_EXISTS == GetLastError())
	{
		return -1;
	}

	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(true);
	QDesktopWidget *pDesktopWidget = QApplication::desktop();
	int nScreenCount = pDesktopWidget->screenCount();
	KSDoodling w;
	w.setScreen(1);
	//w.show();
#ifdef _DEBUG
	w.showDesktop();
#endif
	return a.exec();
}
