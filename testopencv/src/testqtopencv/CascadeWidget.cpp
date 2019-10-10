#include "CascadeWidget.h"
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include "EnumDefine.h"
#include "QtOpenCV.h"

REG_CREATEFUN(EWidgetCascade, CascadeWidget);
CascadeWidget::CascadeWidget(QWidget *parent)
	: BaseWidget(parent)
	, m_bLoadCascade(false)
{
	ui.setupUi(this);
	connect(ui.pushButtonLoadCascade, SIGNAL(clicked()), SLOT(onLoadCascade()));
	connect(ui.pushButtonClear, SIGNAL(clicked()), SLOT(onClearCascade()));
}

CascadeWidget::~CascadeWidget()
{
}

void CascadeWidget::coverImage(const cv::Mat &origin, cv::Mat & m, std::vector<cv::Rect>& rcs)
{
	if (m_bLoadCascade)
	{
		std::vector<cv::Rect> tmpRects;
		cv::Mat grayMat;
		cv::cvtColor(m, grayMat, CV_BGR2GRAY);

		m_cascade.detectMultiScale(m, tmpRects, 1.1, 2, 0);
		rcs.insert(rcs.end(), tmpRects.begin(), tmpRects.end());

		cv::Mat tmpMat = m.clone();
		for (auto &rc : tmpRects)
		{
			cv::rectangle(tmpMat, rc, cv::Scalar(255, 0, 0));
		}
		QImage img = QtOpenCV::Mat2QImage(tmpMat);
		ui.labelImage->setPixmap(QPixmap::fromImage(img));
		ui.labelImage->setFixedSize(img.size());
	}
	else
	{
		ui.labelImage->setPixmap(QPixmap());
	}
}

void CascadeWidget::onLoadCascade()
{
	QString strFileName = QFileDialog::getOpenFileName(this);
	if (!strFileName.isEmpty())
	{
		m_bLoadCascade = m_cascade.load(strFileName.toStdString());
		emit paramChanged();
	}
}

void CascadeWidget::onClearCascade()
{
	m_bLoadCascade = false;
	emit paramChanged();
}
