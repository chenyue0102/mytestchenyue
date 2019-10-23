#include "BilateralWidget.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/cudaimgproc.hpp>
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
	coverImage<cv::Mat>(origin, m, rcs, cv::bilateralFilter);
}

void BilateralWidget::coverImage(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, std::vector<cv::Rect>& rcs)
{
	auto fun = [](cv::InputArray src, cv::OutputArray dst, int kernel_size, float sigma_color, float sigma_spatial, int borderMode)
	{
		cv::cuda::bilateralFilter(src, dst, kernel_size, sigma_color, sigma_spatial);
	};
	coverImage<cv::cuda::GpuMat>(origin, m, rcs, fun);
}

template<typename MATTYPE, typename BILATERALFILTERFUN>
void BilateralWidget::coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs, BILATERALFILTERFUN fun)
{
	MATTYPE bilateralMat;
	int d = ui.lineEditD->text().toInt();
	double sigmaColor = ui.lineEditSigmaColor->text().toDouble();
	double sigmaSpace = ui.lineEditSigmaSpace->text().toDouble();
	int borderType = ui.lineEditBorderType->text().toInt();
	if (rcs.empty())
	{
		fun(m, bilateralMat, d, sigmaColor, sigmaSpace, borderType);
		bilateralMat.copyTo(m);
	}
	else
	{
		for (auto &rc : rcs)
		{
			MATTYPE tmpMat = m(rc);
			fun(tmpMat, bilateralMat, d, sigmaColor, sigmaSpace, borderType);
			bilateralMat.copyTo(tmpMat);
		}
	}
	if (ui.checkBoxRender->isChecked())
	{
		QImage img = QtOpenCV::Mat2QImage(m);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
}