#include "KSPlayer.h"
#include "KSDoodling.h"
#include "KSPlayerContainer.h"


KSPlayer::KSPlayer(QWidget *parent)
	: QWidget(parent)
	, m_pKSDoodling(nullptr)
	, m_pKSPlayerContainer(nullptr)
{
	ui.setupUi(this);

	m_pKSPlayerContainer = new KSPlayerContainer();
	connect(ui.widgetDoodlingSet, SIGNAL(signalScreenChanged(int)), m_pKSPlayerContainer, SLOT(setScreen(int)));

	m_pKSDoodling = new KSDoodling();

	connect(ui.widgetDoodlingSet, SIGNAL(signalPenChanged(const QPen &)), m_pKSDoodling, SLOT(setPen(const QPen &)));
	connect(ui.widgetDoodlingSet, SIGNAL(signalDoodlingVisilbe(bool)), m_pKSDoodling, SLOT(setDoodlingVisible(bool)));
	connect(ui.widgetDoodlingSet, SIGNAL(signalScreenChanged(int)), m_pKSDoodling, SLOT(setScreen(int)));

	ui.widgetDoodlingSet->init();
	
	m_pKSPlayerContainer->showDesktop();
	ui.widgetPlayCtrl->setDrawWindow((void*)m_pKSPlayerContainer->winId());
}

KSPlayer::~KSPlayer()
{
	delete m_pKSDoodling;
	m_pKSDoodling = nullptr;

	delete m_pKSPlayerContainer;
	m_pKSPlayerContainer = nullptr;
}
