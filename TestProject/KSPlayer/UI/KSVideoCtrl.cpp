#include "KSVideoCtrl.h"
#include <assert.h>
#include <QFileDialog>
#include <QTimer>
#include <QDebug>
#include "ui_KSVideoCtrl.h"
#include "vlc.h"


struct KSVideoCtrlData
{
	Ui::KSVideoCtrl ui;
	void *m_pDrawWindow;
	libvlc_instance_t		* m_Instance;
	libvlc_media_player_t	* m_MediaPlayer;
	libvlc_media_t          * m_Media;
	libvlc_time_t	m_totalTime;
	QTimer timer;
	bool bSliderPressed;			//是否按下了滑动条，按下的时候，不更新滑动条当前位置

	KSVideoCtrlData()
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
KSVideoCtrl::KSVideoCtrl(QWidget *parent)
	: QWidget(parent)
	, m_pData(new KSVideoCtrlData)
{
	auto &ui = m_pData->ui;
	ui.setupUi(this);

	auto &timer = m_pData->timer;
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

KSVideoCtrl::~KSVideoCtrl()
{
	close();
	delete m_pData;
	m_pData = nullptr;
}

void KSVideoCtrl::setDrawWindow(void *pDrawWindow)
{
	m_pData->m_pDrawWindow = pDrawWindow;
}

void KSVideoCtrl::open(const QString &strName, EVideoSrc videoSrc)
{
	close();
	bool bRet = false;
	auto &m_Instance = m_pData->m_Instance;
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	auto &m_Media = m_pData->m_Media;

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
		std::string strTempName = strName.toStdString();
		if (EVideoSrcFile == videoSrc)
		{
			if ((m_Media = libvlc_media_new_path(m_Instance, strTempName.c_str())) == nullptr)
			{
				assert(false);
				break;
			}
		}
		else if (EVideoSrcDevice == videoSrc)
		{
			std::string strDevice = "dshow://";
			if ((m_Media = libvlc_media_new_location(m_Instance, strDevice.c_str())) == nullptr)
			{
				assert(false);
				break;
			}
			std::string strOption = ":dshow-adev=" + strName.toStdString();
			libvlc_media_add_option(m_Media, strOption.c_str());
		}
		else
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
		if (nullptr != m_pData->m_pDrawWindow)
		{
			libvlc_media_player_set_hwnd(m_MediaPlayer, m_pData->m_pDrawWindow);
		}
		m_pData->m_totalTime = libvlc_media_get_duration(m_Media);
		if (0 != m_pData->m_totalTime)
		{
			m_pData->timer.start();
		}

		bRet = true;
	} while (false);
	if (!bRet)
	{
		close();
	}
}

void KSVideoCtrl::close()
{
	auto &m_Instance = m_pData->m_Instance;
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	auto &m_Media = m_pData->m_Media;

	m_pData->timer.stop();
	m_pData->m_totalTime = 0;
	m_pData->bSliderPressed = false;
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

void KSVideoCtrl::slotPlay()
{
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_play(m_MediaPlayer);
	}
}

void KSVideoCtrl::slotStop()
{
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_stop(m_MediaPlayer);
	}
}

void KSVideoCtrl::slotPause()
{
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_pause(m_MediaPlayer);
	}
}

void KSVideoCtrl::slotOpen()
{
#if 0
	QString strFileName = QFileDialog::getOpenFileName(this, QStringLiteral("打开视频"), QStringLiteral(""), QStringLiteral("视频文件 (*.avi *.mp4 *.wmv"));
	strFileName = strFileName.replace(QChar(L'/'), QChar(L'\\'));
	if (!strFileName.isEmpty())
	{
		open(strFileName, EVideoSrcFile);
	}
#endif
	//open(QStringLiteral("C:\\Users\\EDZ\\Desktop\\软件\\v1080.mp4"), EVideoSrcFile);
	open(QStringLiteral("麦克风 (Realtek High Definition Audio)"), EVideoSrcDevice);
}

void KSVideoCtrl::slotResume()
{
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	if (m_MediaPlayer)
	{
		libvlc_media_player_play(m_MediaPlayer);
	}
}

void KSVideoCtrl::slotRefreshSlider()
{
	auto &ui = m_pData->ui;
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	auto &m_totalTime = m_pData->m_totalTime;

	if (nullptr != m_MediaPlayer
		&& 0 != m_totalTime)
	{
		libvlc_time_t curTime = libvlc_media_player_get_time(m_MediaPlayer);
		if (!m_pData->bSliderPressed)
		{
			libvlc_time_t pos = curTime * ui.horizontalSlider->maximum() / m_totalTime;
			ui.horizontalSlider->setValue(pos);
		}
		if (curTime >= m_totalTime)
		{
			emit playFinished();
			m_pData->timer.stop();
		}
	}
}

void KSVideoCtrl::slotSliderPressed()
{
	m_pData->bSliderPressed = true;
}

void KSVideoCtrl::slotSliderReleased()
{
	m_pData->bSliderPressed = false;
	auto &ui = m_pData->ui;
	int position = ui.horizontalSlider->sliderPosition();
	return slotSliderMoved(position);
}

void KSVideoCtrl::slotSliderMoved(int position)
{
	auto &ui = m_pData->ui;
	auto &m_MediaPlayer = m_pData->m_MediaPlayer;
	auto &m_totalTime = m_pData->m_totalTime;
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
