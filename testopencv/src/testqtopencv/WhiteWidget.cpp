#include "WhiteWidget.h"
#include <math.h>
#include "EnumDefine.h"
#include "QtOpenCV.h"

REG_CREATEFUN(EWidgetGWhite, WhiteWidget);
WhiteWidget::WhiteWidget(QWidget *parent)
	: BaseWidget(parent)
	, m_beta(0)
{
	ui.setupUi(this);
}

WhiteWidget::~WhiteWidget()
{
}

void WhiteWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& r)
{
	int beta = ui.lineEditBeta->text().toInt();
	if (beta > 1)
	{
		if (beta != m_beta)
		{
			m_beta = beta;
			fillTable(256, beta);
		}
		for (int row = 0; row < m.rows; row++)
		{
			for (int col = 0; col < m.cols; col++)
			{
				m.at<cv::Vec3b>(row, col)[0] = m_vTable[m.at<cv::Vec3b>(row, col)[0]];
				m.at<cv::Vec3b>(row, col)[1] = m_vTable[m.at<cv::Vec3b>(row, col)[1]];
				m.at<cv::Vec3b>(row, col)[2] = m_vTable[m.at<cv::Vec3b>(row, col)[2]];
			}
		}
	}
	QImage img = QtOpenCV::Mat2QImage(m);
	ui.labelImage->setPixmap(QPixmap::fromImage(img));
	ui.labelImage->setFixedSize(img.size());
}

void WhiteWidget::fillTable(int count, int beta)
{
	m_vTable.clear();
	for (int i = 0; i < count; i++)
	{
		m_vTable.push_back(getWhiteValue(i, 0, 0x000000ff, beta));
	}
}

int WhiteWidget::getWhiteValue(int v, int minValue, int maxValue, int beta)
{
	int ret = 0;
	int distance = maxValue - minValue;
	if (minValue >= 0
		&& maxValue > 0
		&& distance > 0
		&& beta > 1)
	{
		int tmpV = v - minValue;
		int tmpMin = 0;
		int tmpMaxValue = maxValue - minValue;
		double dValue = static_cast<double>(tmpV) / distance;
		double dWhiteValue = getWhiteRatio(dValue, beta);
		ret = dWhiteValue * distance + minValue;
		ret = std::min(maxValue, ret);
		ret = std::max(minValue, ret);
	}
	else
	{
		assert(false);
	}
	return ret;
}

double WhiteWidget::getWhiteRatio(double d, int beta)
{
	double ret;
	if (d >= 0.0 
		&& d <= 1.0
		&& beta > 1)
	{
		ret = std::log(d * (beta - 1) + 1) / std::log(beta);
	}
	else
	{
		assert(false);
	}
	return ret;
}
