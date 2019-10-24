#include "WhiteWidget.h"
#include <math.h>
#include <type_traits>
#include "EnumDefine.h"
#include "QtOpenCV.h"
#include <cuda_runtime.h>
#include <helper_cuda.h>

REG_CREATEFUN(EWidgetGWhite, WhiteWidget);
WhiteWidget::WhiteWidget(QWidget *parent)
	: BaseWidget(parent)
	, m_beta(0)
	, m_mapTable(0)
{
	ui.setupUi(this);
}

WhiteWidget::~WhiteWidget()
{
	if (nullptr != m_mapTable)
	{
		checkCudaErrors(cudaFree(m_mapTable));
		m_mapTable = nullptr;
	}
}

void WhiteWidget::coverImage(const cv::Mat & origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::Mat>(origin, m, rcs);
}

void WhiteWidget::coverImage(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::cuda::GpuMat>(origin, m, rcs);
}

void fillCuda()
{

}

template<typename MATTYPE>
void WhiteWidget::coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs)
{
	int beta = ui.lineEditBeta->text().toInt();
	if (beta > 1)
	{
		if (beta != m_beta)
		{
			m_beta = beta;
			fillTable(256, beta, m_vTable);
			if (nullptr != m_mapTable)
			{
				checkCudaErrors(cudaFree(m_mapTable));
				m_mapTable = nullptr;
			}
			checkCudaErrors(cudaMalloc(&m_mapTable, sizeof(int) * m_vTable.size()));
			checkCudaErrors(cudaMemcpy(m_mapTable, &m_vTable[0], sizeof(int) * m_vTable.size(), cudaMemcpyHostToDevice));
		}
		//if (rcs.empty())
		{
			makeWhite(m);
		}
		/*else
		{
			for (auto &r : rcs)
			{
				MATTYPE tmpM = m(r);
				makeWhite(tmpM, m_vTable);
			}
		}*/
	}
	if (ui.checkBoxRender->isChecked())
	{
		QImage img = QtOpenCV::Mat2QImage(m);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
}

void WhiteWidget::fillTable(int count, int beta, std::vector<int> &vTable)
{
	vTable.clear();
	for (int i = 0; i < count; i++)
	{
		vTable.push_back(getWhiteValue(i, 0, 0x000000ff, beta));
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

void WhiteWidget::makeWhite(cv::Mat & m)
{
	for (int row = 0; row < m.rows; row++)
	{
		for (int col = 0; col < m.cols; col++)
		{
			for (int i = 0; i < 3; i++)
			{
				auto v = m.at<cv::Vec3b>(row, col)[i];
				if (v >= 0 && v < m_vTable.size())
				{
					m.at<cv::Vec3b>(row, col)[i] = m_vTable[v];
				}
				else
				{
					assert(false);
				}
			}
		}
	}
}

extern "C" void doMakeWhiteGPU(cv::cuda::GpuMat & origin, const int *mapTable);
void WhiteWidget::makeWhite(cv::cuda::GpuMat & m)
{
	doMakeWhiteGPU(m, m_mapTable);
}
