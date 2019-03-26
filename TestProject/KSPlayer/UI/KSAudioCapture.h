#pragma once

#include <QWidget>

struct KSAudioCaptureData;
class KSAudioCapture : public QWidget
{
	Q_OBJECT

public:
	KSAudioCapture(QWidget *parent = Q_NULLPTR);
	~KSAudioCapture();
public:
	void init();
	void refreshDevices();
public slots:
	void slotPlay();
	void slotStop();
	void slotPause();
	void slotResume();
private:
	KSAudioCaptureData *m_pKSAudioCaptureData;
};
