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
		double scaleX = ui.lineEditX->text().toDouble();
		double scaleY = ui.lineEditY->text().toDouble();
		std::vector<cv::Rect> tmpRects;
		cv::Mat grayMat;
		cv::cvtColor(m, grayMat, CV_BGR2GRAY);

		m_cascade.detectMultiScale(m, tmpRects, 1.1, 2, 0);

		cv::Size matSize = m.size();
		std::for_each(tmpRects.begin(), tmpRects.end(), [scaleX, scaleY, matSize](cv::Rect &r)
		{
			int w = r.width * scaleX;
			int h = r.height * scaleY;
			r.x = r.x + (r.width - w) / 2;
			if (r.x < 0)
			{
				r.x = 0;
			}
			r.width = w;
			if (r.x + r.width > matSize.width)
			{
				r.width = matSize.width - r.x;
			}

			r.y = r.y + (r.height - h) / 2;
			if (r.y < 0)
			{
				r.y = 0;
			}
			r.height = h;
			if (r.y + r.height > matSize.height)
			{
				r.height = matSize.height - r.y;
			}

		});
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
