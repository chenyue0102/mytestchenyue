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
	void initMovie(const QString &strFileName);
	void destroyMovie();
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
	Q_DISABLE_COPY(KSPlayerCtrl)
	KSPlayerCtrlData *m_pData;
};
