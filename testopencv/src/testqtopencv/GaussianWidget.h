#pragma once

#include "BaseWidget.h"
#include "ui_GaussianWidget.h"

class GaussianWidget : public BaseWidget
{
	Q_OBJECT

public:
	GaussianWidget(QWidget *parent = Q_NULLPTR);
	~GaussianWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &r)override;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs)override;
public:
	template<typename MATTYPE>
	void coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs);
private:
	void doGaussian(const cv::Mat &origin, cv::Mat &m, int w, int h, double sigmaX, double sigmaY, int opacity);
	void doGaussian(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, int w, int h, double sigmaX, double sigmaY, int opacity);
private:
	Ui::GaussianWidget ui;
};
