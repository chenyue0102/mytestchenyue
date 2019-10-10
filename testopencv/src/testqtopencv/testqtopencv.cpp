#include "testqtopencv.h"
#include <QImage>
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "BaseWidget.h"
#include "QtOpenCV.h"

testqtopencv::testqtopencv(QWidget *parent)
	: QWidget(parent)
	, m_flowLayout(new FlowLayout())
{
	ui.setupUi(this);
	ui.widgetContainer->setLayout(m_flowLayout);
	connect(ui.pushButtonLoad, SIGNAL(clicked()), SLOT(onLoadImage()));
}

void testqtopencv::onLoadImage()
{
	do
	{
		QString strFileName = QFileDialog::getOpenFileName(this);
		if (strFileName.isEmpty())
		{
			break;
		}
		QImage img;
		if (!img.load(strFileName))
		{
			break;
		}
		m_imgSize = img.size();
		m_originMat = QtOpenCV::QImage2Mat(img);
		if (m_originMat.type() == CV_8UC4)
		{
			cv::cvtColor(m_originMat, m_originMat, cv::COLOR_RGBA2RGB);
		}
		cv::Mat tmpMat = m_originMat.clone();

		int value1 = 3;
		int value2 = 3;
		int dx = value1 * 5;    //双边滤波参数之一
		double fc = value1*12.5; //双边滤波参数之一
		int p = 50;//透明度
		cv::Mat temp1, temp2, temp3, temp4;

		//双边滤波
		bilateralFilter(tmpMat, temp1, dx, fc, fc);

		temp2 = (temp1 - tmpMat + 128);

		//高斯模糊
		GaussianBlur(temp2, temp3, cv::Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

		cv::Mat temp5 = (2 * temp3 - 255);
		temp4 = m_originMat + 2 * temp3 - 255;

		cv::Mat dst = (m_originMat*(100 - p) + temp4*p) / 100;

		cv::namedWindow("test");
		cv::imshow("temp1", temp1);
		cv::imshow("temp2", temp2);
		cv::imshow("temp3", temp3);
		cv::imshow("temp4", temp4);
		cv::imshow("temp5", temp5);
		cv::imshow("dst", dst);
		cv::imshow("m_originMat", m_originMat);
	} while (false);
}

void testqtopencv::onAddWidget()
{
	do
	{
		auto pSender = sender();
		if (nullptr == pSender)
		{
			assert(false);
			break;
		}
		int type = pSender->property("type").toInt();
		if (0 == type)
		{
			assert(0);
			break;
		}
		addWidget(type);
	} while (false);
	
}

void testqtopencv::onParamChanged()
{
	auto children = ui.widgetContainer->findChildren<BaseWidget*>();
	m_tmpMat = m_originMat.clone();
	std::vector<cv::Rect> r;
	for (auto w : children)
	{
		w->coverImage(m_originMat, m_tmpMat, r);
	}
}

void testqtopencv::addWidget(int id)
{
	QWidget *w = BaseWidget::createWidget(id);
	if (nullptr != w)
	{
		int width = ui.lineEditWidth->text().toInt();
		int height = ui.lineEditHeight->text().toInt();
		w->setFixedSize(width, height);
		connect(w, SIGNAL(paramChanged()), SLOT(onParamChanged()));
		m_flowLayout->addWidget(w);

		onParamChanged();
	}
}
