#pragma once

#include <QWidget>

struct KSPlayerCtrlData;
class KSPlayerCtrl : public QWidget
{
	Q_OBJECT

public:
	KSPlayerCtrl(QWidget *parent = Q_NULLPTR);
	~KSPlayerCtrl();
public:
	void setDrawWindow(void *pDrawWindow);
	void init(const QString &strFileName);
	void destroy();
public slots:
	void slotPlay();
	void slotStop();
	void slotPause();
	void slotOpen();
	void slotResume();
	void slotRefreshSlider();
	void slotSliderPressed();
	void slotSliderReleased();
	void slotSliderMoved(int position);
private:
	KSPlayerCtrlData *m_pKSPlayerCtrlData;
};
