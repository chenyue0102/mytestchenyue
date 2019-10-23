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

void GaussianWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::Mat>(origin, m, rcs);
}

void GaussianWidget::coverImage(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::cuda::GpuMat>(origin, m, rcs);
}

template<typename MATTYPE>
void GaussianWidget::coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs)
{
	int w = 0, h = 0;
	double sigmaX = ui.lineEditSigmaX->text().toDouble();
	double sigmaY = ui.lineEditSigmaY->text().toDouble();
	int opacity = ui.lineEditOpacity->text().toInt();
	QString strSize = ui.lineEditSize->text();
	QStringList sizeArray = strSize.split(QChar(L','));
	if (2 == sizeArray.size())
	{
		w = sizeArray[0].toInt();
		h = sizeArray[1].toInt();
	}
	//ÆæÊý
	assert(w & 0x00000001 != 0 && h & 0x00000001 != 0);
	if (rcs.empty())
	{
		doGaussian(origin, m, w, h, sigmaX, sigmaY, opacity);
	}
	else
	{
		for (auto &r : rcs)
		{
			MATTYPE oriMat, processedMat;
			oriMat = origin(r);
			processedMat = m(r);
			doGaussian(oriMat, processedMat, w, h, sigmaX, sigmaY, opacity);
		}
	}
	if (ui.checkBoxRender->isChecked())
	{
		QImage img = QtOpenCV::Mat2QImage(m);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
}

void GaussianWidget::doGaussian(const cv::Mat & origin, cv::Mat & m, int w, int h, double sigmaX, double sigmaY, int opacity)
{
	cv::Mat gaussianMat, tmpMat, tmpMat2;
	tmpMat = (m - origin + 128);

	cv::GaussianBlur(tmpMat, gaussianMat, cv::Size(w, h), sigmaX, sigmaY);
	tmpMat = origin + 2 * gaussianMat - 256;
	m = (origin * (100 - opacity) + tmpMat * opacity) / 100;
}

extern "C"
{
	void doGaussianGPU(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, int w, int h, double sigmaX, double sigmaY, int opacity);
}
void GaussianWidget::doGaussian(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, int w, int h, double sigmaX, double sigmaY, int opacity)
{
	doGaussianGPU(origin, m, w, h, sigmaX, sigmaY, opacity);
}
