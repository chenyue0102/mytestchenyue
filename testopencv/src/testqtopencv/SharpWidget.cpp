#include "SharpWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "EnumDefine.h"
#include "WhiteWidget.h"

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
	cv::Mat whiteMat = m.clone(), gaussianMat;
	WhiteWidget::makeWhite(whiteMat, m_vTable);

	cv::GaussianBlur(m, gaussianMat, cv::Size(3, 3), 0, 0);
}
