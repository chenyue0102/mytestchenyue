#pragma once
#include <limits>
#include "BaseWidget.h"
#include "ui_WhiteWidget.h"

class WhiteWidget : public BaseWidget
{
	Q_OBJECT

public:
	WhiteWidget(QWidget *parent = Q_NULLPTR);
	~WhiteWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs)override;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs)override;
public:
	template<typename MATTYPE>
	void coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs);
public:
	static int getWhiteValue(int value, int minValue, int maxValue, int beta);
	static double getWhiteRatio(double d, int beta);
	static void fillTable(int count, int beta, std::vector<int> &vTable);
	void makeWhite(cv::Mat &m);
	void makeWhite(cv::cuda::GpuMat &m);
private:
	Ui::WhiteWidget ui;
	std::vector<int> m_vTable;
	int *m_mapTable;
	int m_beta;
};
