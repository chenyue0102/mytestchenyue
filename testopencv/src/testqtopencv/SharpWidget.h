#pragma once
#include <vector>
#include "BaseWidget.h"
#include "ui_SharpWidget.h"

class SharpWidget : public BaseWidget
{
	Q_OBJECT

public:
	SharpWidget(QWidget *parent = Q_NULLPTR);
	~SharpWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs)override;
private:
	Ui::SharpWidget ui;
	std::vector<int> m_vTable;
};
