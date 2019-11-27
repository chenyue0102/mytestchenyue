#include "QtOpenCV.h"
#include <assert.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/cudacodec.hpp>

namespace QtOpenCV
{
QImage Mat2QImage(const cv::Mat & mat)
{
	QImage img;
	auto t = mat.type();
	switch (t)
	{
	case CV_8UC1:
	{
		QImage tmp(mat.cols, mat.rows, QImage::Format_Indexed8);
		tmp.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			tmp.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = tmp.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;//mat.step [0]一行元素字节数 [1]一个元素字节数
		}
		img = tmp;
	}
	break;
	case CV_8UC3:
	{
		QImage tmp(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		img = tmp.rgbSwapped();
	}
	break;
	case CV_8UC4:
	{
		img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
	}
	break;
	default:
	{
		assert(false);
	}
	break;
	}
	return img;
}

class MyMat : public cv::Mat
{

};
cv::Mat QImage2Mat(const QImage & img)
{
	cv::Mat mat;
	auto f = img.format();
	switch (f)
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	{
		cv::Mat tmp(img.height(), img.width(), CV_8UC4, (void*)img.constBits(), img.bytesPerLine());
		mat = tmp.clone();//tmp内部直接使用了img的内存，需要clone下，解出与img的依赖
	}
	break;
	case QImage::Format_RGB888:
	{
		cv::Mat tmp(img.height(), img.width(), CV_8UC3, (void*)img.constBits(), img.bytesPerLine());
		cv::cvtColor(tmp, mat, cv::COLOR_BGR2RGB);
	}
	break;
	case QImage::Format_Grayscale8:
	{
		cv::Mat tmp(img.height(), img.width(), CV_8UC1, (void*)img.constBits(), img.bytesPerLine());
		mat = tmp.clone();//tmp内部直接使用了img的内存，需要clone下，解出与img的依赖
		break;
	}
	default:
	{
		assert(false);
	}
	break;
	}
	return mat;
}
QImage Mat2QImage(const cv::cuda::GpuMat & mat)
{
	cv::Mat m;
	mat.download(m);
	return Mat2QImage(m);
}
}
