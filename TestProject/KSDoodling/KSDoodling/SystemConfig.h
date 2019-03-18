#pragma once
#include <mutex>
#include <QRgb>
#include <QList>

class SystemConfig
{
public:
	SystemConfig();
	~SystemConfig();
public:
	QList<QRgb> getPenColors()const;
	QString getShowShortcut()const;
	int getPenWidth()const;
private:
	void init();
private:
	mutable std::mutex m_mutex;
	QList<QRgb> m_penColors;
	QString m_strShowShortcut;
	int m_nPenWidth;
};

