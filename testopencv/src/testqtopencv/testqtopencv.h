#pragma once

#include <QtWidgets/QWidget>
#include "ui_testqtopencv.h"
#include <opencv2/core/core.hpp>
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
private:
	void addWidget(int id);
private:
	Ui::testqtopencvClass ui;
	QSize m_imgSize;
	cv::Mat m_originMat, m_tmpMat;
	FlowLayout *m_flowLayout;
};
