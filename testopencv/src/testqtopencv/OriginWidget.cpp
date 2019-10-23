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

void OriginWidget::coverImage(const cv::Mat &origin, cv::Mat & m, std::vector<cv::Rect>& r)
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

