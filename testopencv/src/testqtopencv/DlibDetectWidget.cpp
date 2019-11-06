#include "DlibDetectWidget.h"
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaimgproc.hpp>
#include "EnumDefine.h"
#include "QtOpenCV.h"

#define FACE_DETECT_WIDTH 480

REG_CREATEFUN(EWidgetDlibDetect, DlibDetectWidget);
DlibDetectWidget::DlibDetectWidget(QWidget *parent)
	: BaseWidget(parent)
	, m_bLoadCascade(false)
{
	ui.setupUi(this);
}

DlibDetectWidget::~DlibDetectWidget()
{
}

void DlibDetectWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{

}

void DlibDetectWidget::coverImage(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, std::vector<cv::Rect>& rcs)
{
	if (!m_bLoadCascade)
	{
		return;
	}
	cv::cuda::GpuMat tmpMat;
	float ratio = (float)m.cols / FACE_DETECT_WIDTH;
	int ratioHeight = 0;
	if (ratio != 0.0)
	{
		ratioHeight = m.rows / ratio;
	}
	cv::cuda::resize(m, tmpMat, cv::Size(FACE_DETECT_WIDTH, ratioHeight));
	//cv::cuda::GpuMat tmpMat2;
	//cv::cuda::cvtColor(tmpMat, tmpMat2, CV_BGR2GRAY);
	cv::Mat cpuMat;
	tmpMat.download(cpuMat);
	dlib::matrix<dlib::rgb_pixel> dimg;
	dlib::assign_image(dimg, dlib::cv_image<dlib::rgb_pixel>(cpuMat));
	std::vector<dlib::mmod_rect> faces = m_gpuDetector(dimg);

	cv::Mat drawMat;
	m.download(drawMat);
	for (auto &rc : faces)
	{
		cv::Rect r(rc.rect.left() * ratio, rc.rect.top() * ratio, rc.rect.width() * ratio, rc.rect.height() * ratio);
		cv::rectangle(drawMat, r, cv::Scalar(255, 0, 0));
	}

	//dlib::GPUImage myImage;
	//auto faces2 = m_gpuDetector(myImage);
	/*dlib::array2d<dlib::rgb_pixel> arrimg;
	dlib::assign_image(arrimg, dlib::cv_image<dlib::rgb_pixel>(cpuMat));
	auto faces2 = m_gpuDetector(arrimg);*/

	if (ui.checkBoxRender->isChecked())
	{
		QImage img = QtOpenCV::Mat2QImage(drawMat);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
}

void DlibDetectWidget::loadFile()
{
	QString strFileName = QFileDialog::getOpenFileName(this);
	if (!strFileName.isEmpty())
	{
		dlib::deserialize(strFileName.toStdString().c_str()) >> m_gpuDetector;
		m_bLoadCascade = true;
	}
}
