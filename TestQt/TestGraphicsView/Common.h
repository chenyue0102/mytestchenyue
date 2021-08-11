#pragma once
#include <QPixmap>
namespace Common
{
QPixmap scale(const QPixmap &bmp, const QMargins &margin, const QRect &src, int width, int height);
void drawPixmap(QPainter *painter, const QPixmap &bmp, const QMargins &margin, const QRect &des, const QRect &srctmp);
void drawPixmap(QPainter *painter, const QPixmap &bmp, const QMargins &margin, const QRect &des);
};

