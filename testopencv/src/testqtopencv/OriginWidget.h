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
	void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &r);
private:
	Ui::OriginWidget ui;
	int m_width;
	int m_height;
};
