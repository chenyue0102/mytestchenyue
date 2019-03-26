#pragma once

#include <QWidget>

class KSVideoContainer : public QWidget
{
	Q_OBJECT

public:
	KSVideoContainer(QWidget *parent = 0);
	~KSVideoContainer();
public slots:
	void setScreen(int nScreen);
	void showDesktop();
private:
	int m_nScreen;
};
