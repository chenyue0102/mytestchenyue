#include "KSPlayerContainer.h"
#include <QApplication>
#include <QDesktopWidget>

KSPlayerContainer::KSPlayerContainer(QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
	, m_nScreen(0)
{
}

KSPlayerContainer::~KSPlayerContainer()
{
}

void KSPlayerContainer::setScreen(int nScreen)
{
	m_nScreen = nScreen;
}

void KSPlayerContainer::showDesktop()
{
	QDesktopWidget *pDesktopWidget = QApplication::desktop();
	if (m_nScreen < 0
		|| m_nScreen >= pDesktopWidget->screenCount())
	{
		m_nScreen = 0;
	}
	QRect rcScreen = pDesktopWidget->screenGeometry(m_nScreen);
	QSize szScreen = rcScreen.size();
	resize(szScreen);
	move(rcScreen.topLeft());

	//showFullScreen();
	show();
	raise();
	activateWindow();
}
