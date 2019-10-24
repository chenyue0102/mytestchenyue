#include "OriginWidget.h"
#include "QtOpenCV.h"
#include "EnumDefine.h"

REG_CREATEFUN(EWidgetOrigin, OriginWidget);
OriginWidget::OriginWidget(QWidget *parent)
	: BaseWidget(parent)
	, m_width(0)
	, m_height(0)
{
	ui.setupUi(this);
	connect(ui.pushButtonRefresh, SIGNAL(clicked()), SIGNAL(paramChanged()));
}

OriginWidget::~OriginWidget()
{
}

void OriginWidget::coverImage(const cv::Mat &origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::Mat>(origin, m, rcs);
}

void OriginWidget::coverImage(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, std::vector<cv::Rect>& rcs)
{
	coverImage<cv::cuda::GpuMat>(origin, m, rcs);
}

template<typename MATTYPE>
void OriginWidget::coverImage(const MATTYPE &origin, MATTYPE &m, std::vector<cv::Rect> &rcs)
{
	if (ui.checkBoxRender->isChecked())
	{
		QImage img = QtOpenCV::Mat2QImage(origin);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
	if (m_width != m.cols
		|| m_height != m.rows)
	{
		m_width = m.cols;
		m_height = m.rows;
		ui.labelSize->setText(QStringLiteral("%1X%2").arg(m_width).arg(m_height));
	}
}