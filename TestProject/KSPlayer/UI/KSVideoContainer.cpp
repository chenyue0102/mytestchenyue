#include "KSVideoContainer.h"
#include <QApplication>
#include <QDesktopWidget>

KSVideoContainer::KSVideoContainer(QWidget *parent)
	: QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
	, m_nScreen(0)
{
}

KSVideoContainer::~KSVideoContainer()
{
}

void KSVideoContainer::setScreen(int nScreen)
{
	m_nScreen = nScreen;
}

void KSVideoContainer::showDesktop()
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
