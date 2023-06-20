#include "tcpclient.h"
#include <QApplication>
#ifdef WIN32
#include <winsock.h>
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#ifdef WIN32
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	tcpclient w;
	w.show();
	return a.exec();
}
