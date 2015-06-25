#pragma once
#include <QVariant>
#include <assert.h>
#include <QPixmapCache>

enum EnumTreeItemType
{
	EnumTreeItemTypeNone,
	EnumTreeItemTypeGroup,
	EnumTreeItemTypeUser,
};


enum EnumUserProperty
{
	EnumUserPropertyNone,
	EnumUserPropertyType,
	EnumUserPropertyID,
	EnumUserPropertyNickName,
	EnumUserPropertyHeadImagePath,
	EnumUserPropertyHeadImage,
	EnumUserPropertyGrayHeadImage,
	EnumUserPropertyVisiable,
	EnumUserPropertyGray,
};

class TreeItemInfo
{
public:
	TreeItemInfo(EnumTreeItemType _ItemType, TreeItemInfo *_parent)
		:ItemType(_ItemType), parent(nullptr)
		, nID(0)
	{
		setParent(_parent);
	}
	virtual ~TreeItemInfo()
	{
		if (nullptr != parent)
		{
			parent->removeChild(this);
			parent = nullptr;
		}
	}

	virtual void setID(int _nID)
	{
		nID = _nID;
		setItemData(EnumUserPropertyID, nID);
	}
	virtual int getID()const
	{
		return nID;
	}
	virtual void appendChild(TreeItemInfo *childItem)
	{
		assert(false);
		return;
	}
	virtual void removeChild(TreeItemInfo *childItem)
	{
		assert(false);
		return ;
	}
	virtual TreeItemInfo* child(int row)
	{
		return nullptr;
	}
	QVariant getHeadImage()
	{
		QVariant vtResult;
		auto itor = m_property.find(EnumUserPropertyHeadImagePath);
		if (itor != m_property.end())
		{
			QPixmap image;
			QString strImagePath = itor.value().toString();
			if (m_QPixmapCache.find(strImagePath, &image))
			{
				vtResult = image;
			}
			else
			{
				if (image.load(strImagePath))
				{
					QImage::Format f = image.toImage().format();
					m_QPixmapCache.insert(strImagePath, image);
					vtResult = image;
				}
			}
		}
		return vtResult;
	}

	QVariant getGrayHeadImage()
	{
		QVariant vtResult;
		auto itor = m_property.find(EnumUserPropertyHeadImagePath);
		if (itor != m_property.end())
		{
			QPixmap image;
			QString strImagePath = itor.value().toString() + QStringLiteral(".gray");
			if (m_QPixmapCache.find(strImagePath, &image))
			{
				vtResult = image;
			}
			else
			{
				QVariant vtTemp = getHeadImage();
				if (vtTemp.canConvert<QPixmap>())
				{
					QPixmap SourcePixmap = vtTemp.value<QPixmap>();
					QImage SourceImage = SourcePixmap.toImage();
					QImage DestImage(SourceImage.width(), SourceImage.height(), SourceImage.format());
					const unsigned char *pSourceBytes = SourceImage.bits();
					unsigned char *pDestBytes = DestImage.bits();
					assert(SourceImage.byteCount() == (SourceImage.width() * SourceImage.height() * 4));
					if (SourceImage.byteCount() == DestImage.byteCount())
					{
						int nLimit = SourceImage.width() * SourceImage.height() * 4;
						for (int nIndex = 0; nIndex < nLimit; nIndex += 4)
						{
							unsigned char uGrayValue = ((unsigned int)pSourceBytes[nIndex] * 11 + pSourceBytes[nIndex + 1] * 16 + pSourceBytes[nIndex + 2] * 5) / 32;
							pDestBytes[nIndex] = pDestBytes[nIndex + 1] = pDestBytes[nIndex + 2] = uGrayValue;
							pDestBytes[nIndex + 3] = pSourceBytes[nIndex + 3];
						}
						QPixmap GrayPixmap = QPixmap::fromImage(DestImage, Qt::ColorOnly);
						GrayPixmap.fromImage(DestImage);
						vtResult.setValue(GrayPixmap);
						m_QPixmapCache.insert(strImagePath, GrayPixmap);
					}
				}
			}
		}
		return vtResult;
	}

	virtual QVariant getItemData(int nType)
	{
		QVariant vtResult;
		if (EnumUserPropertyHeadImage == nType)
		{
			vtResult = getHeadImage();
		}
		else if (EnumUserPropertyGrayHeadImage == nType)
		{
			vtResult = getGrayHeadImage();
		}
		else
		{
			auto itor = m_property.find(nType);
			if (itor != m_property.end())
			{
				vtResult = itor.value();
			}
		}
		return vtResult;
	}

	virtual void setItemData(int nType, QVariant vt)
	{
		if (EnumUserPropertyHeadImagePath == nType)
		{
			m_property[nType] = vt;
		}
		else
		{
			m_property[nType] = vt;
		}
	}

	virtual int childCount()
	{
		return 0;
	}
	virtual int childItemIndex(TreeItemInfo *item)
	{
		return 0;
	}
	virtual int row()
	{
		if (parent)
		{
			return parent->childItemIndex(this);
		}
		else
		{
			return 0;
		}
	}

	EnumTreeItemType GetType(){return ItemType;}
	TreeItemInfo* GetParent(){return parent;}

protected:
	void setParent(TreeItemInfo *_parent)
	{
		if (_parent == parent)
		{
			return;
		}
		if (nullptr != parent)
		{
			parent->removeChild(this);
		}
		parent = _parent;
		if (nullptr != parent)
		{
			parent->appendChild(this);
		}
	}
protected:
	int		nID;
	EnumTreeItemType ItemType;
	TreeItemInfo *parent;
	QMap<int, QVariant> m_property;

	QPixmapCache m_QPixmapCache;
};

class GroupTreeItemInfo
	: public TreeItemInfo
{
public:
	GroupTreeItemInfo(TreeItemInfo *_parent)
		:TreeItemInfo(EnumTreeItemTypeGroup, _parent)
	{
		setItemData(EnumUserPropertyType, EnumTreeItemTypeGroup);
	}
	virtual ~GroupTreeItemInfo()
	{
		std::vector<TreeItemInfo*> tempChildItems = childItems;
		for (int nIndex = 0; nIndex < tempChildItems.size(); nIndex++)
		{
			TreeItemInfo *pOneChildItem = tempChildItems[nIndex];
			delete pOneChildItem;
		}
	}

	virtual void appendChild(TreeItemInfo *childItem)
	{
		childItems.push_back(childItem);
		return;
	}
	virtual void removeChild(TreeItemInfo *childItem)
	{
		for (auto itor = childItems.begin(); itor != childItems.end(); ++itor)
		{
			if ((*itor) == childItem)
			{
				childItems.erase(itor);
				break;
			}
		}
		return ;
	}
	virtual TreeItemInfo* child(int row)
	{
		assert(row < childItems.size());
		return childItems[row];
	}


	virtual int childCount()
	{
		return childItems.size();
	}
	virtual int childItemIndex(TreeItemInfo *item)
	{
		int nItemIndex = 0;
		for (auto itor = childItems.begin(); itor != childItems.end(); ++itor, ++nItemIndex)
		{
			if (*itor == item)
			{
				break;
			}
		}
		return nItemIndex;
	}
	
	std::vector<TreeItemInfo*> childItems;
};

class UserTreeItemInfo
	: public TreeItemInfo
{
public:
	UserTreeItemInfo(TreeItemInfo *_parent):TreeItemInfo(EnumTreeItemTypeUser, _parent)
	{
		setItemData(EnumUserPropertyType, EnumTreeItemTypeUser);
	}
};
