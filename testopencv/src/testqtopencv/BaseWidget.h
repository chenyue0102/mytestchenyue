#pragma once
#include <functional>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cuda.hpp>

typedef std::function<QWidget*()> CREATE_FUN;
class BaseWidget : public QWidget
{
	Q_OBJECT
Q_SIGNALS :
	void paramChanged();
public:
	BaseWidget(QWidget *parent = Q_NULLPTR);
	~BaseWidget();
public:
	static void addCreateFun(int id, CREATE_FUN fun);
	static QWidget* createWidget(int id);
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs) = 0;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs) {};
};
struct AutoCreator
{
	AutoCreator(int id, CREATE_FUN fun)
	{
		BaseWidget::addCreateFun(id, fun);
	}
	~AutoCreator()
	{

	}
};
#define REG_CREATEFUN(id, className) \
	static AutoCreator g_##id = AutoCreator(id, []()->className*{return new className;});