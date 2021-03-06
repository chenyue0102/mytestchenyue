#include "KSDoodling.h"
#include <assert.h>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPushButton>

#define BMP_BORDER_RESERVED 2

KSDoodling::KSDoodling(QWidget *parent)
	: QWidget(parent, Qt::Tool | Qt::FramelessWindowHint)
	, m_bMousePressed(false)
	, m_pen(QPen(QBrush(QColor(255, 0, 0)), 2, Qt::SolidLine))
	, m_objectArray()
	, m_tmpImg()
	, m_ptLastPos()
	, m_nLeft(0)
	, m_nRight(0)
	, m_nTop(0)
	, m_nBottom(0)
	, m_bkClr(0xff, 0xff, 0xff, 0x01)
	, m_nScreen(0)
{
	setAttribute(Qt::WA_TranslucentBackground, true);
	setMouseTracking(true);
}

void KSDoodling::showDesktop()
{
	QDesktopWidget *pDesktopWidget = QApplication::desktop();
	if (m_nScreen < 0
		|| m_nScreen >= pDesktopWidget->screenCount())
	{
		m_nScreen = 0;
	}
	QRect rcScreen = pDesktopWidget->screenGeometry(m_nScreen);
	QSize szScreen = rcScreen.size();
	resize(szScreen);
	if (m_tmpImg.size() != szScreen)
	{
		m_tmpImg = QImage(szScreen, QImage::Format_ARGB32);
	}
	m_tmpImg.fill(QColor(255, 255, 255, 0));
	m_objectArray.clear();
	move(rcScreen.topLeft());

	//showFullScreen();
	setWindowFlags(static_cast<Qt::WindowFlags>(windowFlags() | Qt::WA_AlwaysStackOnTop));
	show();
	raise();
	activateWindow();
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

void KSDoodling::setScreen(int nScreen)
{
	m_nScreen = nScreen;
}

void KSDoodling::setPen(const QPen &pen)
{
	m_pen = pen;
}

void KSDoodling::setDoodlingVisible(bool bVisible)
{
	if (bVisible)
	{
		showDesktop();
	}
	else
	{
		m_objectArray.clear();
		m_tmpImg.fill(QColor(255, 255, 255, 0));
		repaint();
		setWindowFlags(static_cast<Qt::WindowFlags>(windowFlags() & ~Qt::WA_AlwaysStackOnTop));
		hide();
	}
}

void KSDoodling::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	
	painter.fillRect(this->rect(), m_bkClr);

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