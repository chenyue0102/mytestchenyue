#include "KSPlayer.h"
#include "KSVideoContainer.h"


KSPlayer::KSPlayer(QWidget *parent)
	: QWidget(parent)
	, m_pKSVideoContainer(nullptr)
{
	ui.setupUi(this);

	m_pKSVideoContainer = new KSVideoContainer();
	connect(ui.widgetDoodlingSet, SIGNAL(signalScreenChanged(int)), m_pKSVideoContainer, SLOT(setScreen(int)));

	m_pKSVideoContainer->showDesktop();
	ui.widgetPlayCtrl->setDrawWindow((void*)m_pKSVideoContainer->winId());
}

KSPlayer::~KSPlayer()
{
	delete m_pKSVideoContainer;
	m_pKSVideoContainer = nullptr;
}
