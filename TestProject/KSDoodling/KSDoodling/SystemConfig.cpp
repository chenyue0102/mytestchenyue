#include "SystemConfig.h"
#include <QSettings>
#include <QCoreApplication>
#include <QVector>

SystemConfig::SystemConfig()
	: m_mutex()
	, m_penColors()
	, m_strShowShortcut()
	, m_nPenWidth(1)
	, m_maskColor(qRgba(0xff, 0xff, 0xff, 0x01))
	, m_strExitShortcur()
{
	init();
}

SystemConfig::~SystemConfig()
{
}

QList<QRgb> SystemConfig::getPenColors()const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_penColors;
}

QString SystemConfig::getShowShortcut() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_strShowShortcut;
}

int SystemConfig::getPenWidth() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_nPenWidth;
}

QRgb SystemConfig::getMaskColor() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_maskColor;
}

QString SystemConfig::getExitShortcur() const
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return m_strExitShortcur;
}

void SystemConfig::init()
{
	std::lock_guard<std::mutex> lk(m_mutex);

	QString strFilePath = QCoreApplication::applicationDirPath() + QStringLiteral("/system.ini");
	QSettings settings(strFilePath, QSettings::IniFormat);
	settings.setIniCodec("gbk");

	auto strList = settings.value("setting/penColors", QStringList()).toStringList();
	for (auto &str : strList)
	{
		QRgb clr = str.toUInt(nullptr, 16);
		m_penColors.push_back(clr);
	}

	m_strShowShortcut = settings.value("setting/showShortcut", QString()).toString();

	m_nPenWidth = settings.value("setting/penWidth", 1).toInt();

	QString strMaskColor = settings.value("setting/maskColor", 0x01FFFFFF).toString();
	m_maskColor = strMaskColor.toUInt(nullptr, 16);

	m_strExitShortcur = settings.value("setting/exitShortcut", QStringLiteral("Alt+F4")).toString();
}
