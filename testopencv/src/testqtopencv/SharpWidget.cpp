#include "SharpWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "EnumDefine.h"
#include "WhiteWidget.h"
#include "QtOpenCV.h"

REG_CREATEFUN(EWidgetSharp, SharpWidget);
SharpWidget::SharpWidget(QWidget *parent)
	: BaseWidget(parent)
{
	ui.setupUi(this);
	WhiteWidget::fillTable(256, 2, m_vTable);
}

SharpWidget::~SharpWidget()
{
}

void SharpWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	/*cv::Mat whiteMat = m.clone(), gaussianMat;
	WhiteWidget::makeWhite(whiteMat, m_vTable);

	cv::GaussianBlur(m, gaussianMat, cv::Size(3, 3), 0, 0);*/
	int kernels[] =
	{
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1,
	};
	cv::Mat sharpMat(3, 3, CV_32SC1, kernels);
	cv::filter2D(m, m, -1, sharpMat);

	QImage img = QtOpenCV::Mat2QImage(m);
	ui.labelImage->setPixmap(QPixmap::fromImage(img));
	ui.labelImage->setFixedSize(img.size());
}
