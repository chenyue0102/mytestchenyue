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
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &r)override;
private:
	Ui::BilateralWidget ui;
};
