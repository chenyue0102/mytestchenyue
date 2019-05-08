#pragma once

#include <QWebChannel>

class MyWebChannel : public QWebChannel
{
	Q_OBJECT

public:
	MyWebChannel(QObject *parent);
	~MyWebChannel();

};
