#pragma once

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "BaseWidget.h"
#include "ui_CascadeWidget.h"

class CascadeWidget : public BaseWidget
{
	Q_OBJECT

public:
	CascadeWidget(QWidget *parent = Q_NULLPTR);
	~CascadeWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &r)override;
public Q_SLOTS:
	void onLoadCascade();
	void onClearCascade();
private:
	Ui::CascadeWidget ui;
	cv::CascadeClassifier m_cascade;
	bool m_bLoadCascade;
};
