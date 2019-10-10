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
private:
	void doGaussian(const cv::Mat &origin, cv::Mat &m, int w, int h, double sigmaX, double sigmaY, int opacity);
private:
	Ui::GaussianWidget ui;
};
