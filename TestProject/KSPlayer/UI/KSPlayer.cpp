#include "KSPlayer.h"
#include "KSVideoContainer.h"
#include "Single.h"
#include "SystemConfig.h"


KSPlayer::KSPlayer(QWidget *parent)
	: QWidget(parent)
	, m_pKSVideoContainer(nullptr)
{
	ui.setupUi(this);

	m_pKSVideoContainer = new KSVideoContainer();
	connect(ui.widgetDoodlingSet, SIGNAL(signalScreenChanged(int)), m_pKSVideoContainer, SLOT(setScreen(int)));

	auto &setting = Single<SystemConfig>::Instance();
	int nScreen = setting.getScreen();
	m_pKSVideoContainer->setScreen(nScreen);
	//m_pKSVideoContainer->showDesktop();
	ui.widgetVideoCtrl->setDrawWindow((void*)m_pKSVideoContainer->winId());
}

KSPlayer::~KSPlayer()
{
	delete m_pKSVideoContainer;
	m_pKSVideoContainer = nullptr;
}
