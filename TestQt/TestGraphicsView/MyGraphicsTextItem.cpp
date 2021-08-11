#include <assert.h>
#include <QStyleOptionGraphicsItem>
#include "MyGraphicsTextItem.h"
#include "Common.h"

struct ItemImage
{
	QPixmap bkImage;
	QMargins bkMargin;
	QRect rcSource;
};
struct MyGraphicsTextItemData
{
	std::map<MyGraphicsTextItem::EImage, ItemImage> images;
};
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsItem *parent/* = Q_NULLPTR*/)
	: QGraphicsTextItem(parent)
	, m_pData(new MyGraphicsTextItemData())
{

}

MyGraphicsTextItem::MyGraphicsTextItem(const QString &text, QGraphicsItem *parent/* = Q_NULLPTR*/)
	: QGraphicsTextItem(text, parent)
	, m_pData(new MyGraphicsTextItemData())
{

}
MyGraphicsTextItem::~MyGraphicsTextItem()
{
	delete m_pData;
	m_pData = nullptr;
}

//设置背景图片
void MyGraphicsTextItem::setPixmap(EImage type, const QPixmap &bmp)
{
	m_pData->images[type].bkImage = bmp;
}

//设置九宫格拉伸margins
void MyGraphicsTextItem::setPixmapMargins(EImage type, const QMargins &margins)
{
	m_pData->images[type].bkMargin = margins;
}

//如果图片是个多帧图片，取图片的位置
void MyGraphicsTextItem::setSourceRect(EImage type, const QRect &rc)
{
	m_pData->images[type].rcSource = rc;
}

void MyGraphicsTextItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	do
	{
		if (nullptr == option)
		{
			assert(false);
			break;
		}
		QStyle::State state = option->state;
		QRect rc = option->exposedRect.toAlignedRect();
		//先绘制禁用
		if (!(state & QStyle::State_Enabled))
		{
			if (drawPixmap(EImageDisabled, painter, rc))
			{
				break;
			}
		}
		//绘制选中
		if (state & QStyle::State_Selected)
		{
			if (drawPixmap(EImageSelected, painter, rc))
			{
				break;
			}
		}
		if (state & QStyle::State_MouseOver)
		{
			if (drawPixmap(EImageHover, painter, rc))
			{
				break;
			}
		}
		drawPixmap(EImageNormal, painter, rc);
	} while (false);
	__super::paint(painter, option, widget);
}

bool MyGraphicsTextItem::drawPixmap(EImage type, QPainter *painter, const QRect &rect)
{
	bool ret = false;

	do
	{
		if (nullptr == painter)
		{
			assert(false);
			break;
		}
		auto iter = m_pData->images.find(type);
		if (iter == m_pData->images.end())
		{
			break;
		}
		auto &info = iter->second;
		if (info.bkImage.isNull())
		{
			assert(false);
			break;
		}
		Common::drawPixmap(painter, info.bkImage, info.bkMargin, rect, info.rcSource);
	} while (false);
	
	return ret;
}
