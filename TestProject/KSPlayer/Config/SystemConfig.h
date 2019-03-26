#pragma once
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
	void setPenWidth(int nPenWidth);
	QRgb getMaskColor()const;
	int getScreen()const;
	void setScreen(int nScreen);
private:
	void init();
private:
	QList<QRgb> m_penColors;
	QString m_strShowShortcut;
	int m_nPenWidth;
	QRgb m_maskColor;
	int m_nScreen;
};

