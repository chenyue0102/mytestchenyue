#pragma once

#include <vector>
#include "BaseWidget.h"
#include "ui_OriginWidget.h"

class OriginWidget : public BaseWidget
{
	Q_OBJECT

public:
	OriginWidget(QWidget *parent = Q_NULLPTR);
	~OriginWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs)override;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs)override;
public:
	template<typename MATTYPE>
	void coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs);
private:
	Ui::OriginWidget ui;
	int m_width;
	int m_height;
};
