#include "BilateralWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "EnumDefine.h"
#include "QtOpenCV.h"

REG_CREATEFUN(EWidgetBilateral, BilateralWidget);
BilateralWidget::BilateralWidget(QWidget *parent)
	: BaseWidget(parent)
{
	ui.setupUi(this);
}

BilateralWidget::~BilateralWidget()
{
}

void BilateralWidget::coverImage(const cv::Mat &origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	cv::Mat bilateralMat;
	int value = 5;
	int dx = value * 5;
	double fc = value * 12.5;
	if (rcs.empty())
	{
		cv::bilateralFilter(m, bilateralMat, dx, fc, fc);
		bilateralMat.copyTo(m);
	}
	else
	{
		for (auto &rc : rcs)
		{
			cv::Mat tmpMat = m(rc);
			cv::bilateralFilter(tmpMat, bilateralMat, dx, fc, fc);
			bilateralMat.copyTo(tmpMat);
		}
	}
	QImage img = QtOpenCV::Mat2QImage(m);
	ui.labelImage->setPixmap(QPixmap::fromImage(img));
	ui.labelImage->setFixedSize(img.size());
}
