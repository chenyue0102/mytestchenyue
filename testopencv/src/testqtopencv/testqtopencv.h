#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include "ui_testqtopencv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/cuda.hpp>
#include "flowlayout.h"
#include "FPS.h"

class testqtopencv : public QWidget
{
	Q_OBJECT

public:
	testqtopencv(QWidget *parent = Q_NULLPTR);
public Q_SLOTS:
	void onLoadImage();
	void onAddWidget();
	void onParamChanged();
	void onDeleteWidget();
	void onOpenCamera();
	void onRefreshCamera();
	void onOpenVideo();
	void onRefreshVideo();
private:
	void addWidget(int id);
	void doRefreshWidgets();
private:
	Ui::testqtopencvClass ui;
	QSize m_imgSize;
	cv::Mat m_originMat, m_tmpMat;
	cv::cuda::GpuMat m_originMatGPU, m_tmpMatGPU;
	FlowLayout *m_flowLayout;
	cv::VideoCapture m_cameraCapture;
	cv::VideoCapture m_videoCapture;
	QTimer m_timerRefreshCamera;
	QTimer m_timerRefreshVideo;
	FPS m_fps;
	int m_lastFPS;
};