#include "SystemConfig.h"
#include <QSettings>
#include <QCoreApplication>
#include <QVector>

#define KEY_PENWIDTH "setting/penWidth"
#define KEY_SCREEN "setting/screen"

#define INIT_SETTINGS \
QString strFilePath = QCoreApplication::applicationDirPath() + QStringLiteral("/setting.ini");\
QSettings settings(strFilePath, QSettings::IniFormat);\
settings.setIniCodec("gbk");

SystemConfig::SystemConfig()
	: m_penColors()
	, m_strShowShortcut()
	, m_nPenWidth(1)
	, m_maskColor(qRgba(0xff, 0xff, 0xff, 0x01))
	, m_nScreen(0)
{
	init();
}

SystemConfig::~SystemConfig()
{
}

QList<QRgb> SystemConfig::getPenColors()const
{
	return m_penColors;
}

QString SystemConfig::getShowShortcut() const
{
	return m_strShowShortcut;
}

int SystemConfig::getPenWidth() const
{
	return m_nPenWidth;
}

void SystemConfig::setPenWidth(int nPenWidth)
{
	m_nPenWidth = nPenWidth;
	INIT_SETTINGS;
	settings.setValue(KEY_PENWIDTH, nPenWidth);
}

QRgb SystemConfig::getMaskColor() const
{
	return m_maskColor;
}

int SystemConfig::getScreen() const
{
	return m_nScreen;
}

void SystemConfig::setScreen(int nScreen)
{
	m_nScreen = nScreen;
	INIT_SETTINGS;
	settings.setValue(KEY_SCREEN, nScreen);
}

void SystemConfig::init()
{
	INIT_SETTINGS;

	auto strList = settings.value("setting/penColors", QStringList()).toStringList();
	for (auto &str : strList)
	{
		QRgb clr = str.toUInt(nullptr, 16);
		m_penColors.push_back(clr);
	}

	m_strShowShortcut = settings.value("setting/showShortcut", QString()).toString();

	m_nPenWidth = settings.value(KEY_PENWIDTH, 1).toInt();

	QString strMaskColor = settings.value("setting/maskColor", 0x01FFFFFF).toString();
	m_maskColor = strMaskColor.toUInt(nullptr, 16);

	m_nScreen = settings.value(KEY_SCREEN, 0L).toInt();
}
