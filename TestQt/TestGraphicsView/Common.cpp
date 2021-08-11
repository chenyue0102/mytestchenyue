#include <assert.h>
#include <QPainter>
#include "Common.h"

namespace Common
{
	/*
	左上 上 右上
	左中 中 右中
	坐下 下 右下
	*/
void drawPixmap(QPainter *painter, const QPixmap &bmp, const QMargins &margin, const QRect &des, const QRect &srctmp)
{
	if (nullptr == painter)
	{
		assert(false);
		return;
	}
	painter->save();
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	QRect src = srctmp;
	if (src.isEmpty())
	{
		src = QRect(QPoint(0, 0), bmp.size());
	}
	//左上
	QRect drawSrc = QRect(src.left(), src.top(), margin.left(), margin.top());
	QRect drawDes = QRect(des.left(), des.top(), margin.left(), margin.top());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//上
	drawSrc = QRect(src.left() + margin.left(), src.top(), src.width() - margin.left() - margin.right(), margin.top());
	drawDes = QRect(des.left() + margin.left(), des.top(), des.width() - margin.left() - margin.right(), margin.top());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//右上
	drawSrc = QRect(src.left() + src.width() - margin.right(), src.top(), margin.right(), margin.top());
	drawDes = QRect(des.left() + des.width() - margin.right(), des.top(), margin.right(), margin.top());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//左中
	drawSrc = QRect(src.left(), src.top() + margin.top(), margin.left(), src.height() - margin.top() - margin.bottom());
	drawDes = QRect(des.left(), des.top() + margin.top(), margin.left(), des.height() - margin.top() - margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//中
	drawSrc = QRect(src.left() + margin.left(), src.top() + margin.top(), src.width() - margin.left() - margin.right(), src.height() - margin.top() - margin.bottom());
	drawDes = QRect(des.left() + margin.left(), des.top() + margin.top(), des.width() - margin.left() - margin.right(), des.height() - margin.top() - margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//右中
	drawSrc = QRect(src.left() + src.width() - margin.right(), src.top() + margin.top(), margin.right(), src.height() - margin.top() - margin.bottom());
	drawDes = QRect(des.left() + des.width() - margin.right(), des.top() + margin.top(), margin.right(), des.height() - margin.top() - margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//左下
	drawSrc = QRect(src.left(), src.top() + src.height() - margin.bottom(), margin.left(), margin.bottom());
	drawDes = QRect(des.left(), des.top() + des.height() - margin.bottom(), margin.left(), margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//下
	drawSrc = QRect(src.left() + margin.left(), src.top() + src.height() - margin.bottom(), src.width() - margin.left() - margin.right(), margin.bottom());
	drawDes = QRect(des.left() + margin.left(), des.top() + des.height() - margin.bottom(), des.width() - margin.left() - margin.right(), margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	//右下
	drawSrc = QRect(src.left() + src.width() - margin.right(), src.top() + src.height() - margin.bottom(), margin.right(), margin.bottom());
	drawDes = QRect(des.left() + des.width() - margin.right(), des.top() + des.height() - margin.bottom(), margin.right(), margin.bottom());
	painter->drawPixmap(drawDes, bmp, drawSrc);

	painter->restore();
}

void drawPixmap(QPainter *painter, const QPixmap &bmp, const QMargins &margin, const QRect &des)
{
	return drawPixmap(painter, bmp, margin, des, QRect());
}

QPixmap scale(const QPixmap &bmp, const QMargins &margin, const QRect &src, int width, int height)
{
	QPixmap dest(width, height);
	QPainter painter;
	painter.begin(&dest);
	drawPixmap(&painter, bmp, margin, QRect(0, 0, width, height), src);
	painter.end();
	return dest;
}
}
