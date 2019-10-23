#pragma once

#include <QWidget>
#include "BaseWidget.h"
#include "ui_BilateralWidget.h"

class BilateralWidget : public BaseWidget
{
	Q_OBJECT
public:
	BilateralWidget(QWidget *parent = Q_NULLPTR);
	~BilateralWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs)override;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs)override;
public:
	template<typename MATTYPE, typename BILATERALFILTERFUN>
	void coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs, BILATERALFILTERFUN fun);
private:
	Ui::BilateralWidget ui;
};
