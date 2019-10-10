#include "GaussianWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "EnumDefine.h"
#include "QtOpenCV.h"

REG_CREATEFUN(EWidgetGaussian, GaussianWidget);
GaussianWidget::GaussianWidget(QWidget *parent)
	: BaseWidget(parent)
{
	ui.setupUi(this);
}

GaussianWidget::~GaussianWidget()
{
}

void GaussianWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& r)
{
	cv::Mat gaussianMat, tmpMat, tmpMat2;
	int value2 = 3;
	if (r.empty())
	{
		tmpMat = (m - origin + 128);
		
		cv::GaussianBlur(tmpMat, gaussianMat, cv::Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);
		tmpMat = origin + 2 * gaussianMat - 255;
		m = (origin * (100 - 50) + tmpMat * 50) / 100;

		QImage img = QtOpenCV::Mat2QImage(m);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
	else
	{

	}
}
