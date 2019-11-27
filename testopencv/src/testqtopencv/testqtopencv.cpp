#include "testqtopencv.h"
#include <algorithm>
#include <QImage>
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/legacy/constants_c.h>
#include "BaseWidget.h"
#include "QtOpenCV.h"
#include "WhiteWidget.h"


#define CAMERA_FRAME_RATE 60
#define VIDEO_FRAME_RATE 30

const double SQRT2 = sqrt(2);
template<typename T>
void calcHaar(const T *in, T *out, size_t matSize, size_t countPerLine)
{
	assert((matSize & (matSize - 1)) == 0);
	const int halfSize = matSize / 2;
	//先横向后纵向
	for (int row = 0; row < matSize; row++)
	{
		const T *pIn = in + (row * countPerLine);
		T *pOut = out + (row * countPerLine);
		for (int step = 0; step < halfSize; step++)
		{
			double ave = (static_cast<double>(pIn[2 * step]) + pIn[2 * step + 1]) / 2;
			double diff = (static_cast<double>(pIn[2 * step]) - pIn[2 * step + 1]) / 2;
			pOut[step] = ave;
			pOut[halfSize + step] = diff;
		}
	}
	T *tmp = new T[matSize]();
	//对上次生成的out做纵向运算
	for (int col = 0; col < matSize; col++)
	{
		for (int step = 0; step < halfSize; step++)
		{
			int index = (2 * step) * countPerLine + col;
			int nextRowIndex = (2 * step + 1) * countPerLine + col;
			auto curRowValue = out[index];
			auto nextRowValue = out[nextRowIndex];
			double ave = (static_cast<double>(curRowValue) + nextRowValue) / 2;
			double diff = (static_cast<double>(curRowValue) - nextRowValue) / 2;
			tmp[step] = ave;
			tmp[step + halfSize] = diff;
		}
		for (int i = 0; i < matSize; i++)
		{
			out[i * countPerLine + col] = tmp[i];
		}
	}
	delete[]tmp;
}

template<typename T>
void dcalcHaar(const T *in, T *out, size_t matSize, size_t countPerLine)
{
	assert((matSize & (matSize - 1)) == 0);
	const int halfSize = matSize / 2;
	//先纵向后横向
	for (int col = 0; col < matSize; col++)
	{
		for (int step = 0; step < halfSize; step++)
		{
			int aveIndex = step * countPerLine + col;
			int diffIndex = (step + halfSize) * countPerLine + col;
			auto aveValue = in[aveIndex];
			auto diffValue = in[diffIndex];
			double firstValue = (static_cast<double>(aveValue) + diffValue) / 1;
			double secondValue = (static_cast<double>(aveValue) - diffValue) / 1;
			out[2 * step * countPerLine + col] = firstValue;
			out[(2 * step + 1) * countPerLine + col] = secondValue;
		}
	}
	T *tmp = new T[matSize]();
	//对上一步生成的out做横向运算
	for (int row = 0; row < matSize; row++)
	{
		T *pOut = out + (row * countPerLine);
		for (int step = 0; step < halfSize; step++)
		{
			auto aveValue = pOut[step];
			auto diffValue = pOut[step + halfSize];
			double firstValue = (static_cast<double>(aveValue) + diffValue) / 1;
			double secondValue = (static_cast<double>(aveValue) - diffValue) / 1;
			tmp[2 * step] = firstValue;
			tmp[2 * step + 1] = secondValue;
		}
		for (int i = 0; i < matSize; i++)
		{
			pOut[i] = tmp[i];
		}
	}
	delete[]tmp;
}


template<typename T>
void calcHaar(const T *in, T *out, size_t _Size)
{
	T *tmp = new T[_Size]();
	int len = _Size;
	memcpy(out, in, sizeof(in));
	while (len >= 2)
	{
		for (int i = 0; i < len / 2; i++)
		{
			double ave = (static_cast<double>(out[2 * i]) + out[2 * i + 1]) / 2;
			double diff = (static_cast<double>(out[2 * i]) - out[2 * i + 1]) / 2;
			tmp[i] = ave;
			tmp[len / 2 + i] = diff;
		}
		memcpy(out, tmp, len);
		len /= 2;
	}
	memcpy(out, tmp, sizeof(tmp));
	delete[]tmp;
}

template<typename T, size_t _Size>
void calcHaar(const T(&in)[_Size], T(&out)[_Size])
{
	static_assert((_Size & (_Size - 1)) == 0, "");
	return calcHaar(in, out, _Size);
}

template<typename T>
void dcalcHaar(const T *in, T *out, size_t _Size)
{
	T *tmp = new T[_Size]();
	int len = 1;
	memcpy(out, in, sizeof(in));
	while (len * 2 <= _Size)
	{
		for (int i = 0; i < len; i++)
		{
			T first = out[i] + out[len + i];
			T second = out[i] - out[len + i];
			tmp[2 * i] = first;
			tmp[2 * i + 1] = second;
		}
		memcpy(out, tmp, len * 2);
		len *= 2;
	}
	delete[]tmp;
}

template<typename T, size_t _Size>
void dcalcHaar(const T(&in)[_Size], T(&out)[_Size])
{
	static_assert((_Size & (_Size - 1)) == 0, "");
	return dcalcHaar(in, out, _Size);
}

template<typename T>
T setMark(const T &v, bool bin, T &mask)
{
	if (bin)
	{
		return v | mask;
	}
	else
	{
		return v & (~mask);
	}
}

template<typename T>
bool isMask(const T &v, T &mask)
{
	return v & mask;
}
template<typename T>
T diff(const T &v1, const T &v2)
{
	return v1 >= v2 ? v1 - v2 : v2 - v1;
}

testqtopencv::testqtopencv(QWidget *parent)
	: QWidget(parent)
	, m_flowLayout(new FlowLayout())
	, m_videoCapture()
	, m_lastFPS()
{
	ui.setupUi(this);
	ui.widgetContainer->setLayout(m_flowLayout);
	connect(ui.pushButtonLoad, SIGNAL(clicked()), SLOT(onLoadImage()));
	m_timerRefreshCamera.setInterval(1000 / CAMERA_FRAME_RATE);
	connect(&m_timerRefreshCamera, SIGNAL(timeout()), SLOT(onRefreshCamera()));

	m_timerRefreshVideo.setInterval(1000 / VIDEO_FRAME_RATE);
	connect(&m_timerRefreshVideo, SIGNAL(timeout()), SLOT(onRefreshVideo()));
}

void testqtopencv::onLoadImage()
{
	do
	{
		QImage imgori;
		imgori.load("lena512color.tiff");
		imgori = imgori.convertToFormat(QImage::Format_Grayscale8);
		std::string strData;
		strData.append((char*)imgori.constBits(), imgori.width() * imgori.height());

		std::vector<double> haarOrigin, haarResult, calcOrigin;
		std::copy(strData.begin(), strData.end(), std::insert_iterator<std::vector<double>>(haarOrigin, haarOrigin.end()));
		haarResult.resize(strData.size(), 0);
		calcOrigin.resize(strData.size(), 0);

		const int step = 8;
		double *pin = &haarOrigin[0];
		double *pout = &haarResult[0];
		int countPerLine = imgori.width();
		for (int row = 0; row < imgori.height();row += step)
		{
			for (int col = 0; col < imgori.width(); col += step)
			{
				int offset = row * countPerLine + col;
				calcHaar(pin + offset, pout + offset, step, countPerLine);
			}
		}
		pin = &haarResult[0];
		pout = &calcOrigin[0];
		for (int row = 0; row < imgori.height(); row += step)
		{
			for (int col = 0; col < imgori.width(); col += step)
			{
				int offset = row * countPerLine + col;
				dcalcHaar(pin + offset, pout + offset, step, countPerLine);
			}
		}
		std::string after;
		std::copy(calcOrigin.begin(), calcOrigin.end(), std::insert_iterator<std::string>(after, after.end()));
		
		/*char cm = 1 << 6;
		bool bm = isMask(strout[1], cm);
		bm = true;
		strout[1] = setMark(strout[1], bm, cm);
		
		for (int i = 0; i < strData.size(); i += step)
		{
			dcalcHaar(strout.data() + i, &after[0] + i, step);
		}*/
		QImage img2((unsigned char*)after.data(), imgori.width(), imgori.height(), imgori.width(), QImage::Format_Grayscale8);
		cv::imshow("origin", QtOpenCV::QImage2Mat(imgori));
		cv::imshow("new", QtOpenCV::QImage2Mat(img2));
		break;
		QString strFileName = QFileDialog::getOpenFileName(this);
		if (strFileName.isEmpty())
		{
			break;
		}
		m_originMat = cv::imread(strFileName.toStdString());
		if (m_originMat.empty())
		{
			break;
		}
		int type = m_originMat.type();
		int type1 = CV_8UC4;
		int type2 = CV_8UC3;
		if (m_originMat.type() == CV_8UC4)
		{
			cv::cvtColor(m_originMat, m_originMat, cv::COLOR_RGBA2RGB);
		}
		cv::Mat tmp;
		cv::cvtColor(m_originMat, tmp, cv::COLOR_BGR2GRAY);
		//cv::imshow("gray", tmp);
		//Canny 有2个阈值，可能阈值与绝对阈值
		cv::Canny(tmp, tmp, 10, 100, 3, true);
		//cv::imshow("canny", tmp);
		int y = 0, x = 1;
		cv::Vec3b pt = m_originMat.at<cv::Vec3b>(y, x);
		uchar blue = pt[0];
		uchar green = pt[1];
		uchar red = pt[2];
		//cv::GaussianBlur(m_originMat, tmp, cv::Size(5, 5), 3, 3);
		//cv::imshow("tmp1", tmp);
		//高斯模糊并降低图片采样率
		//cv::pyrDown(m_originMat, tmp);
		//cv::imshow("tmp2", tmp);
		if (ui.checkBoxGPU->isChecked())
		{
			m_originMatGPU.upload(m_originMat);
		}


		break;
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
		//bilateralFilter(tmpMat, temp1, dx, fc, fc);
		temp1 = tmpMat;

		cv::Mat whiteMat = temp1.clone();
		for (int row = 0; row < whiteMat.rows; row++)
		{
			for (int col = 0; col < whiteMat.cols; col++)
			{
				for (int i = 0; i < 3; i++)
				{
					int v = whiteMat.at<cv::Vec3b>(row, col)[i];
					v += 10;
					v = std::min(v, 255);
					whiteMat.at<cv::Vec3b>(row, col)[i] = v;
				}
			}
		}


		cv::Mat gaussianMat;
		GaussianBlur(temp1, gaussianMat, cv::Size(5, 5), 0, 0);
		cv::Mat sharpMask = temp1 - gaussianMat;

		cv::Mat sharpMat = temp1.clone();
		int opt = 50;
		int threshold = 10;
		for (int row = 0; row < temp1.rows; row++)
		{
			for (int col = 0; col < temp1.cols; col++)
			{
				auto &item = sharpMask.at<cv::Vec3b>(row, col);
				int opt = ((int)item[0] + item[1] + item[2])*10000/ (3 * 256);
				if (opt > 100) opt = 100;
				if (opt > 0)
				{
					for (int i = 0; i < 3; i++)
					{
						sharpMat.at<cv::Vec3b>(row, col)[i] = (int)sharpMat.at<cv::Vec3b>(row, col)[i] * (100 - opt) / 100 + whiteMat.at<cv::Vec3b>(row, col)[i]*opt / 100;
					}
					
				}
				else
				{
					//sharpMat.at<cv::Vec3b>(row, col) = (sharpMat.at<cv::Vec3b>(row, col) * (100 - opt) + whiteMat.at<cv::Vec3b>(row, col)*opt) / 100;
				}
			}
		}
		cv::imshow("temp1", temp1);
		cv::imshow("whiteMat", whiteMat);
		cv::imshow("sharpMat", sharpMat);
		temp1 = sharpMat;
		temp2 = (temp1 - tmpMat + 128);

		//高斯模糊
		GaussianBlur(temp2, temp3, cv::Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

		cv::Mat temp5 = (2 * temp3 - 255);
		temp4 = m_originMat + 2 * temp3 - 255;

		cv::Mat dst = (m_originMat*(100 - p) + temp4*p) / 100;

		//cv::namedWindow("test");
		/*cv::imshow("temp1", temp1);
		cv::imshow("temp2", temp2);
		cv::imshow("temp3", temp3);
		cv::imshow("temp4", temp4);
		cv::imshow("temp5", temp5);
		*/
		//cv::imshow("test", m_originMat);
		cv::imshow("dst", dst);
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
	doRefreshWidgets();
}

void testqtopencv::onDeleteWidget()
{
	auto children = ui.widgetContainer->findChildren<BaseWidget*>();
	if (!children.isEmpty())
	{
		children.back()->deleteLater();
	}
}

void testqtopencv::onOpenCamera()
{
	if (!m_cameraCapture.isOpened())
	{
		if (!m_cameraCapture.open(0))
		{
			assert(false);
		}
	}
	if (!m_timerRefreshCamera.isActive())
	{
		double d = m_cameraCapture.get(CV_CAP_PROP_FPS);
		if (d > 0.0)
		{
			int n = 1000 / d;
			m_timerRefreshCamera.start(n);
		}
		else
		{
			m_timerRefreshCamera.start();
		}
	}
}

void testqtopencv::onRefreshCamera()
{
	if (m_cameraCapture.read(m_originMat))
	{
		doRefreshWidgets();
	}
}

void testqtopencv::onOpenVideo()
{
	if (m_videoCapture.isOpened())
	{
		m_videoCapture.release();
	}
	QString strFileName = QFileDialog::getOpenFileName(this);
	if (!strFileName.isEmpty())
	{
		if (m_videoCapture.open(strFileName.toStdString()))
		{
			if (!m_timerRefreshVideo.isActive())
			{
				m_timerRefreshVideo.start();
			}
		}
	}
}

void testqtopencv::onRefreshVideo()
{
	if (m_videoCapture.isOpened())
	{
		if (m_videoCapture.read(m_originMat))
		{
			doRefreshWidgets();
		}
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
		//connect(w, SIGNAL(paramChanged()), SLOT(onParamChanged()));
		m_flowLayout->addWidget(w);

		onParamChanged();
	}
}

void testqtopencv::doRefreshWidgets()
{
	int fps = m_fps.fps();
	if (m_lastFPS != fps)
	{
		m_lastFPS = fps;
		ui.labelFPS->setText(QStringLiteral("FPS:%1").arg(m_lastFPS));
	}
	auto children = ui.widgetContainer->findChildren<BaseWidget*>();

	if (m_originMat.rows == 0
		|| m_originMat.cols == 0)
	{
		return;
	}
	if (ui.checkBoxGPU->isChecked())
	{
		cv::cuda::registerPageLocked(m_originMat);
		m_originMatGPU.upload(m_originMat);
		m_tmpMatGPU = m_originMatGPU.clone();
		std::vector<cv::Rect> r;
		for (auto w : children)
		{
			w->coverImage(m_originMatGPU, m_tmpMatGPU, r);
		}
		cv::cuda::unregisterPageLocked(m_originMat);
	}
	else
	{
		m_tmpMat = m_originMat.clone();
		std::vector<cv::Rect> r;
		for (auto w : children)
		{
			w->coverImage(m_originMat, m_tmpMat, r);
		}
	}
}
