#include "KSDoodling.h"
#include <assert.h>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPushButton>
#include "Single.h"
#include "SystemConfig.h"

#define BMP_BORDER_RESERVED 2
#define PROPERTY_COLOR "penColor"

KSDoodling::KSDoodling(QWidget *parent)
	: QWidget(parent, Qt::Tool | Qt::FramelessWindowHint)
	, m_bMousePressed(false)
	, m_pen(QPen(QBrush(QColor(255, 0, 0)), 2, Qt::SolidLine))
	, m_objectArray()
	, m_showShortcut()
	, m_tmpImg()
	, m_ptLastPos()
	, m_nLeft(0)
	, m_nRight(0)
	, m_nTop(0)
	, m_nBottom(0)
	, ui()
{
	ui.setupUi(this);

	auto &systemConfig = Single<SystemConfig>::Instance();
	QList<QRgb> penColors = systemConfig.getPenColors();
	for (auto &clr : penColors)
	{
		QPushButton *pBtnPenColor = new QPushButton;
		pBtnPenColor->setFixedSize(20, 20);
		pBtnPenColor->setStyleSheet(QStringLiteral("QPushButton{background-color:rgba(%1,%2,%3,%4);}")
			.arg(qRed(clr)).arg(qGreen(clr)).arg(qBlue(clr)).arg(qAlpha(clr)));
		pBtnPenColor->setProperty(PROPERTY_COLOR, clr);
		connect(pBtnPenColor, SIGNAL(clicked()), this, SLOT(slotClickPenColor()));
		ui.horizontalLayoutPenColor->addWidget(pBtnPenColor);
	}
	m_pen.setWidth(systemConfig.getPenWidth());
	ui.spinBoxPenWidth->setValue(m_pen.width());
	connect(ui.spinBoxPenWidth, SIGNAL(valueChanged(int)), this, SLOT(slotPenWidthChanged(int)));

	m_showShortcut.setKey(QKeySequence(systemConfig.getShowShortcut()));
	connect(&m_showShortcut, SIGNAL(activated()), this, SLOT(slotShowShortcut()));

	setAttribute(Qt::WA_TranslucentBackground, true);
	setMouseTracking(true);
}

void KSDoodling::showDesktop()
{
	QSize sz = QApplication::desktop()->screenGeometry().size();
	resize(sz);
	if (m_tmpImg.size() != sz)
	{
		m_tmpImg = QImage(sz, QImage::Format_ARGB32);
	}
	m_tmpImg.fill(QColor(255, 255, 255, 0));
	m_objectArray.clear();
	move(QPoint(0, 0));

	showFullScreen();
}

void KSDoodling::calcMinRect(const QPoint & dotPos)
{
	if (m_nLeft > dotPos.x())
	{
		m_nLeft = dotPos.x();
	}
	if (m_nRight < dotPos.x())
	{
		m_nRight = dotPos.x();
	}
	if (m_nTop > dotPos.y())
	{
		m_nTop = dotPos.y();
	}
	if (m_nBottom < dotPos.y())
	{
		m_nBottom = dotPos.y();
	}
}

void KSDoodling::slotClickPenColor()
{
	auto pSender = sender();
	if (nullptr == pSender)
	{
		assert(false);
		return;
	}
	QRgb clr = pSender->property(PROPERTY_COLOR).toUInt();
	m_pen.setColor(QColor(clr));
}

void KSDoodling::slotShowShortcut()
{
	if (isVisible())
	{
		m_objectArray.clear();
		m_tmpImg.fill(QColor(255, 255, 255, 0));
		repaint();
		hide();
	}
	else
	{
		showDesktop();
	}
}

void KSDoodling::slotPenWidthChanged(int nPenWidth)
{
	m_pen.setWidth(nPenWidth);
}

void KSDoodling::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
#ifdef _DEBUG
	QColor clr = QColor(0, 0, 255, 80);
#else
	QColor clr = QColor(255, 255, 255, 1);
#endif
	
	painter.fillRect(this->rect(), clr);

	for (auto &obj : m_objectArray)
	{
		if (obj.type == EnumObjectBitmap)
		{
			painter.drawPixmap(obj.rc, obj.bmp);
		}
	}

	if (m_bMousePressed)
	{
		painter.drawImage(0, 0, m_tmpImg);
	}
}

void KSDoodling::mousePressEvent(QMouseEvent * event)
{
	__super::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
	{
		m_bMousePressed = true;
		m_nLeft = width();
		m_nTop = height();
		m_nRight = 0;
		m_nBottom = 0;
		m_ptLastPos = event->pos();
		calcMinRect(m_ptLastPos);
	}
}

void KSDoodling::mouseReleaseEvent(QMouseEvent * event)
{
	__super::mouseReleaseEvent(event);
	m_bMousePressed = false;
	if (m_nLeft <= m_nRight
		&& m_nTop <= m_nBottom)
	{
		int nWidth = m_nRight - m_nLeft + 2 * BMP_BORDER_RESERVED;
		int nHeight = m_nBottom - m_nTop + 2 * BMP_BORDER_RESERVED;
		QPoint ptTopLeft(m_nLeft - BMP_BORDER_RESERVED, m_nTop - BMP_BORDER_RESERVED);
		QImage img = m_tmpImg.copy(ptTopLeft.x(), ptTopLeft.y(), nWidth, nHeight);
		KSObjectInfo obj;
		obj.type = EnumObjectBitmap;
		obj.bmp = QPixmap::fromImage(img);
		obj.rc = QRect(ptTopLeft, QSize(nWidth, nHeight));
		m_objectArray.push_back(obj);

		m_tmpImg.fill(QColor(255, 255, 255, 0));
	}
}

void KSDoodling::mouseMoveEvent(QMouseEvent * event)
{
	__super::mouseMoveEvent(event);
	if (m_bMousePressed
		&& event->buttons() & Qt::LeftButton)
	{
		QPoint curPos = event->pos();
		QPainter painter;
		QPen pen = m_pen;

		painter.begin(&m_tmpImg);
		painter.setPen(pen);
		painter.drawLine(m_ptLastPos, curPos);
		painter.end();

		int rad = (pen.width() / 2) + 2;
		update(QRect(m_ptLastPos, curPos).normalized()
			.adjusted(-rad, -rad, +rad, +rad));

		m_ptLastPos = curPos;
		calcMinRect(m_ptLastPos);
	}
}
