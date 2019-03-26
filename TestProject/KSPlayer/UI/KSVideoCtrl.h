#pragma once

#include <QWidget>

struct KSVideoCtrlData;
class KSVideoCtrl : public QWidget
{
	Q_OBJECT
public:
	enum EVideoSrc
	{
		EVideoSrcFile,
		EVideoSrcDevice,
	};
public:
	KSVideoCtrl(QWidget *parent = Q_NULLPTR);
	~KSVideoCtrl();
public:
	void setDrawWindow(void *pDrawWindow);
	void open(const QString &strName, EVideoSrc videoSrc);
	void close();
Q_SIGNALS:
	void playFinished();
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
	Q_DISABLE_COPY(KSVideoCtrl)
	KSVideoCtrlData *m_pData;
};
