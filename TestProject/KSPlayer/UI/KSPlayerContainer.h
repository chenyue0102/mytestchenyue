#pragma once

#include <QWidget>

class KSPlayerContainer : public QWidget
{
	Q_OBJECT

public:
	KSPlayerContainer(QWidget *parent = 0);
	~KSPlayerContainer();
public slots:
	void setScreen(int nScreen);
	void showDesktop();
private:
	int m_nScreen;
};
