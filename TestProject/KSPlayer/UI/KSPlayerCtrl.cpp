#include "KSPlayerCtrl.h"
#include <assert.h>
#include <QFileDialog>
#include <QTimer>
#include <QDebug>
#include "ui_KSPlayerCtrl.h"
#include "vlc.h"


struct KSPlayerCtrlData
{
	Ui::KSPlayerCtrl ui;
	void *m_pDrawWindow;
	libvlc_instance_t		* m_Instance;
	libvlc_media_player_t	* m_MediaPlayer;
	libvlc_media_t          * m_Media;
	libvlc_time_t	m_totalTime;
	QTimer timer;
	bool bSliderPressed;

	KSPlayerCtrlData()
		: ui()
		, m_pDrawWindow(nullptr)
		, m_Instance(nullptr)
		, m_MediaPlayer(nullptr)
		, m_Media(nullptr)
		, m_totalTime(0)
		, timer()
		, bSliderPressed(false)
	{

	}
};
KSPlayerCtrl::KSPlayerCtrl(QWidget *parent)
	: QWidget(parent)
	, m_pKSPlayerCtrlData(new KSPlayerCtrlData)
{
	auto &ui = m_pKSPlayerCtrlData->ui;
	ui.setupUi(this);

	auto &timer = m_pKSPlayerCtrlData->timer;
	timer.setSingleShot(false);
	timer.setInterval(50);

	connect(&timer, SIGNAL(timeout()), SLOT(slotRefreshSlider()));
	connect(ui.pushButtonOpen, SIGNAL(clicked()), SLOT(slotOpen()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), SLOT(slotStop()));
	connect(ui.pushButtonPause, SIGNAL(clicked()), SLOT(slotPause()));
	connect(ui.pushButtonPlay, SIGNAL(clicked()), SLOT(slotPlay()));
	connect(ui.pushButtonResume, SIGNAL(clicked()), SLOT(slotResume()));
	connect(ui.horizontalSlider, SIGNAL(sliderReleased()), SLOT(slotSliderReleased()));
	connect(ui.horizontalSlider, SIGNAL(sliderPressed()), SLOT(slotSliderPressed()));
	connect(ui.horizontalSlider, SIGNAL(signalClick(int)), SLOT(slotSliderMoved(int)));
}

KSPlayerCtrl::~KSPlayerCtrl()
{
	delete m_pKSPlayerCtrlData;
	m_pKSPlayerCtrlData = nullptr;
}

void KSPlayerCtrl::setDrawWindow(void *pDrawWindow)
{
	m_pKSPlayerCtrlData->m_pDrawWindow = pDrawWindow;
}

void KSPlayerCtrl::init(const QString & strFileName)
{
	destroy();
	bool bRet = false;
	auto &m_Instance = m_pKSPlayerCtrlData->m_Instance;
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	auto &m_Media = m_pKSPlayerCtrlData->m_Media;

	do
	{
		//启动视频时不显示OSD
		char sNoOsd[10] = "--no-osd";

		//方法一
		const char * vlc_args[32] = { "" };
		int vlc_args_num = 0;
		vlc_args[vlc_args_num++] = sNoOsd;
		if ((m_Instance = libvlc_new(vlc_args_num, vlc_args)) == nullptr)
		{
			assert(false);
			break;
		}
		std::string strFilePath = strFileName.toStdString();
		if ((m_Media = libvlc_media_new_path(m_Instance, strFilePath.c_str())) == nullptr)
		{
			assert(false);
			break;
		}
		if ((m_MediaPlayer = libvlc_media_player_new_from_media(m_Media)) == nullptr)
		{
			assert(false);
			break;
		}
		libvlc_media_parse(m_Media);
		libvlc_media_player_set_hwnd(m_MediaPlayer, m_pKSPlayerCtrlData->m_pDrawWindow);
		m_pKSPlayerCtrlData->m_totalTime = libvlc_media_get_duration(m_Media);
		m_pKSPlayerCtrlData->timer.start();

		bRet = true;
	} while (false);
	if (!bRet)
	{
		destroy();
	}
}

void KSPlayerCtrl::destroy()
{
	auto &m_Instance = m_pKSPlayerCtrlData->m_Instance;
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	auto &m_Media = m_pKSPlayerCtrlData->m_Media;

	m_pKSPlayerCtrlData->timer.stop();
	if (m_Media)
	{
		libvlc_media_release(m_Media);
		m_Media = NULL;
	}

	if (m_MediaPlayer)
	{
		libvlc_media_player_release(m_MediaPlayer);
		m_MediaPlayer = NULL;
	}

	if (m_Instance)
	{
		libvlc_release(m_Instance);
		m_Instance = NULL;
	}
}

void KSPlayerCtrl::slotPlay()
{
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_play(m_MediaPlayer);
	}
}

void KSPlayerCtrl::slotStop()
{
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_stop(m_MediaPlayer);
	}
}

void KSPlayerCtrl::slotPause()
{
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_pause(m_MediaPlayer);
	}
}

void KSPlayerCtrl::slotOpen()
{
#if 0
	QString strFileName = QFileDialog::getOpenFileName(this, QStringLiteral("打开视频"), QStringLiteral(""), QStringLiteral("视频文件 (*.avi *.mp4 *.wmv"));
	strFileName = strFileName.replace(QChar(L'/'), QChar(L'\\'));
	if (!strFileName.isEmpty())
	{
		init(strFileName);
	}
#endif
	init(QStringLiteral("C:\\Users\\EDZ\\Desktop\\软件\\v1080.mp4"));
}

void KSPlayerCtrl::slotResume()
{
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_play(m_MediaPlayer);
	}
}

void KSPlayerCtrl::slotRefreshSlider()
{
	auto &ui = m_pKSPlayerCtrlData->ui;
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	auto &m_totalTime = m_pKSPlayerCtrlData->m_totalTime;

	if (nullptr != m_MediaPlayer
		&& !m_pKSPlayerCtrlData->bSliderPressed
		&& 0 != m_totalTime)
	{
		libvlc_time_t curTime = libvlc_media_player_get_time(m_MediaPlayer);
		libvlc_time_t pos = curTime * ui.horizontalSlider->maximum() / m_totalTime;
		ui.horizontalSlider->setValue(pos);
	}
}

void KSPlayerCtrl::slotSliderPressed()
{
	m_pKSPlayerCtrlData->bSliderPressed = true;
}

void KSPlayerCtrl::slotSliderReleased()
{
	m_pKSPlayerCtrlData->bSliderPressed = false;
	auto &ui = m_pKSPlayerCtrlData->ui;
	int position = ui.horizontalSlider->sliderPosition();
	return slotSliderMoved(position);
}

void KSPlayerCtrl::slotSliderMoved(int position)
{
	auto &ui = m_pKSPlayerCtrlData->ui;
	auto &m_MediaPlayer = m_pKSPlayerCtrlData->m_MediaPlayer;
	auto &m_totalTime = m_pKSPlayerCtrlData->m_totalTime;
	int maximum = ui.horizontalSlider->maximum();

	if (nullptr != m_MediaPlayer
		&& 0 != m_totalTime
		&& 0 != maximum)
	{
		libvlc_time_t curTime = m_totalTime * position / maximum;
		libvlc_media_player_set_time(m_MediaPlayer, curTime);
		slotRefreshSlider();
	}
}
