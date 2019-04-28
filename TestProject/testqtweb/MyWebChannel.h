#pragma once

#include <QWebChannel>

class MyWebChannel : public QWebChannel
{
	Q_OBJECT

public:
	MyWebChannel(QObject *parent);
	~MyWebChannel();
public slots:
	void showMsgBox(const QString &text);
};
