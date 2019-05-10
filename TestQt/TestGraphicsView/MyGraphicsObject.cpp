#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "MyGraphicsObject.h"


MyGraphicsObject::MyGraphicsObject(QGraphicsItem *parent)
	: QGraphicsObject(parent)
{
}

MyGraphicsObject::~MyGraphicsObject()
{
}

void MyGraphicsObject::setSize(const QSizeF & sz)
{
	m_size = sz;
}

QRectF MyGraphicsObject::boundingRect(void) const
{
	qreal penWidth = 1;
	qreal radius = 0;
	return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
		m_size.width() + penWidth, m_size.height() + penWidth);
}
static void qt_graphicsItem_highlightSelected(
	QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
	if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
		return;

	const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
	if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
		return;

	qreal itemPenWidth;
	switch (item->type()) {
	case QGraphicsEllipseItem::Type:
		itemPenWidth = static_cast<QGraphicsEllipseItem *>(item)->pen().widthF();
		break;
	case QGraphicsPathItem::Type:
		itemPenWidth = static_cast<QGraphicsPathItem *>(item)->pen().widthF();
		break;
	case QGraphicsPolygonItem::Type:
		itemPenWidth = static_cast<QGraphicsPolygonItem *>(item)->pen().widthF();
		break;
	case QGraphicsRectItem::Type:
		itemPenWidth = static_cast<QGraphicsRectItem *>(item)->pen().widthF();
		break;
	case QGraphicsSimpleTextItem::Type:
		itemPenWidth = static_cast<QGraphicsSimpleTextItem *>(item)->pen().widthF();
		break;
	case QGraphicsLineItem::Type:
		itemPenWidth = static_cast<QGraphicsLineItem *>(item)->pen().widthF();
		break;
	default:
		itemPenWidth = 1.0;
	}
	const qreal pad = itemPenWidth / 2;

	const qreal penWidth = 0; // cosmetic pen

	const QColor fgcolor = option->palette.windowText().color();
	const QColor bgcolor( // ensure good contrast against fgcolor
		fgcolor.red()   > 127 ? 0 : 255,
		fgcolor.green() > 127 ? 0 : 255,
		fgcolor.blue()  > 127 ? 0 : 255);

	painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

	painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}
void MyGraphicsObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QRect rc = option->rect;
	painter->fillRect(rc, QColor(0, 0, 0));

	QPainterPath path;
	//path.cubicTo(QPointF(100, 0), QPointF(0, 100), QPointF(100, 100));
	path.quadTo(QPointF(0, 100), QPoint(200, 100));
	//painter->setBrush(myGradient);
	//painter->setPen(myPen);
	painter->setPen(QColor(255, 255, 0));
	painter->drawPath(path);

	if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
		qt_graphicsItem_highlightSelected(this, painter, option);
}
