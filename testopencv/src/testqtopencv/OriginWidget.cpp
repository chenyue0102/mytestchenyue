#include "OriginWidget.h"
#include "QtOpenCV.h"
#include "EnumDefine.h"

REG_CREATEFUN(EWidgetOrigin, OriginWidget);
OriginWidget::OriginWidget(QWidget *parent)
	: BaseWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonRefresh, SIGNAL(clicked()), SIGNAL(paramChanged()));
}

OriginWidget::~OriginWidget()
{
}

void OriginWidget::coverImage(const cv::Mat &origin, cv::Mat & m, std::vector<cv::Rect>& r)
{
	QImage img = QtOpenCV::Mat2QImage(origin);
	ui.labelImage->setPixmap(QPixmap::fromImage(img));
	ui.labelImage->setFixedSize(img.size());
}

