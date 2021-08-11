#pragma once

#include <QGraphicsTextItem>

struct MyGraphicsTextItemData;
class MyGraphicsTextItem : public QGraphicsTextItem
{
	Q_OBJECT
public:
	enum EImage
	{
		EImageNone,
		EImageNormal,
		EImageHover,
		EImageSelected,
		EImageDisabled,
	};
public:
	explicit MyGraphicsTextItem(QGraphicsItem *parent = Q_NULLPTR);
	explicit MyGraphicsTextItem(const QString &text, QGraphicsItem *parent = Q_NULLPTR);
	~MyGraphicsTextItem();
public:
	//设置背景图片
	void setPixmap(EImage type, const QPixmap &bmp);
	//设置九宫格拉伸margins
	void setPixmapMargins(EImage type, const QMargins &margins);
	//如果图片是个多帧图片，取图片的位置
	void setSourceRect(EImage type, const QRect &rc);
public:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
	bool drawPixmap(EImage type, QPainter *painter, const QRect &rect);
private:
	MyGraphicsTextItemData *m_pData;
};
