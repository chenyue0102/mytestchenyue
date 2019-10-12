#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include "ui_testqtopencv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include "flowlayout.h"

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
private:
	void addWidget(int id);
	void doRefreshWidgets();
private:
	Ui::testqtopencvClass ui;
	QSize m_imgSize;
	cv::Mat m_originMat, m_tmpMat;
	FlowLayout *m_flowLayout;
	cv::VideoCapture m_videoCapture;
	QTimer m_timerRefreshCamera;
};
