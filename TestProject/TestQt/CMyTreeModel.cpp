#include "CMyTreeModel.h"
#include <sstream>
#include "UserTreeItem.h"
#include <QImage>

CMyTreeModel::CMyTreeModel(QObject *parent)
	: QAbstractItemModel(parent)
	, m_rootItem(nullptr)
{
	m_roleNames.insert(Qt::UserRole + EnumUserPropertyNickName, "nickname");
	m_roleNames.insert(Qt::UserRole + EnumUserPropertyHeadImagePath, "headimage");

	m_rootItem = new GroupTreeItemInfo(nullptr);
	
	GroupTreeItemInfo *pFriend = new GroupTreeItemInfo(m_rootItem);
	pFriend->setID(1);
	pFriend->setItemData(EnumUserPropertyNickName, QStringLiteral("好友"));
	for (int a = 10;a < 20; a++)
	{
		UserTreeItemInfo *pUserInfo = new UserTreeItemInfo(pFriend);
		QString str = QString(QStringLiteral("昵称%1")).arg(a);
		pUserInfo->setItemData(EnumUserPropertyNickName, str);
		pUserInfo->setID(a);
		pUserInfo->setItemData(EnumUserPropertyHeadImagePath, 
			//QStringLiteral("d:\\1.png"));
			QString(QStringLiteral("D:\\JJ比赛外网\\LobbyTheme\\HeadImage\\H000%1.jpg")).arg(a));
		pUserInfo->setItemData(EnumUserPropertyVisiable, true);
		pUserInfo->setItemData(EnumUserPropertyGray, false);
	}
	
	GroupTreeItemInfo *pblacklist = new GroupTreeItemInfo(m_rootItem);
	pblacklist->setID(2);
	pblacklist->setItemData(EnumUserPropertyNickName, QStringLiteral("黑名单"));
	for (int a = 521;a < 530; a++)
	{
		UserTreeItemInfo *pUserInfo = new UserTreeItemInfo(pblacklist);
		QString str = QString(QStringLiteral("昵称%1")).arg(a);
		pUserInfo->setItemData(EnumUserPropertyNickName, str);
		pUserInfo->setID(a);
		pUserInfo->setItemData(EnumUserPropertyHeadImagePath, QString(QStringLiteral("D:\\JJ比赛外网\\LobbyTheme\\HeadImage\\H000%1.jpg")).arg(a - 490));
		pUserInfo->setItemData(EnumUserPropertyVisiable, true);
	}
}

CMyTreeModel::~CMyTreeModel()
{
	delete m_rootItem;
	m_rootItem = nullptr;
}

int CMyTreeModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	TreeItemInfo *parentItem = nullptr;
	if (!parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TreeItemInfo*>(parent.internalPointer());

	return parentItem->childCount();
}

int CMyTreeModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}

QModelIndex CMyTreeModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	TreeItemInfo *parentItem;

	if (!parent.isValid())
		parentItem = m_rootItem;
	else
		parentItem = static_cast<TreeItemInfo*>(parent.internalPointer());

	TreeItemInfo *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex CMyTreeModel::parent(const QModelIndex &index) const
{
	TreeItemInfo *childItem = static_cast<TreeItemInfo*>(index.internalPointer());
	TreeItemInfo *parentItem = childItem->GetParent();

	if (parentItem == m_rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

QVariant CMyTreeModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	TreeItemInfo *item = static_cast<TreeItemInfo*>(index.internalPointer());
	if (role >= Qt::UserRole)
	{
		return item->getItemData(role - Qt::UserRole);
	}
	else
	{
		return QVariant();
	}
	/*if (Qt::DisplayRole == role)
	{
		return item->getItemData(EnumUserPropertyNickName);
	}
	else if (Qt::DecorationRole == role)
	{
		QImage image(item->getItemData(EnumUserPropertyHeadImage).toString());
		return image;
	}
	else
	{
		return QVariant();
	}*/
}

QHash<int,QByteArray> CMyTreeModel::roleNames() const
{
	return m_roleNames;
}

bool CMyTreeModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	if (index.isValid())
	{
		auto pItem = reinterpret_cast<TreeItemInfo*>(index.internalPointer());
		if (pItem->GetType() == EnumTreeItemTypeUser)
		{
			pItem->setItemData(role - Qt::UserRole, value);
			emit dataChanged(index, index, QVector<int>() << role);
		}
		return true;
	}
	else
	{
		return false;
	}
}
