#include "CMyDelegate.h"
#include "UserTreeItem.h"
#include <QPainter>
#include <qglobal.h>
#include <QApplication>
#include <QTreeView>
#include <QHelpEvent>


CMyDelegate::CMyDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

CMyDelegate::~CMyDelegate()
{

}

QSize CMyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize size = __super::sizeHint(option, index);
	if (index.isValid())
	{
		auto myModel = index.model();
		int nType = myModel->data(index, Qt::UserRole + EnumUserPropertyType).toInt();
		if (EnumTreeItemTypeGroup == nType)
		{
			size.setHeight(24);
		}
		else
		{
			if (myModel->data(index, Qt::UserRole + EnumUserPropertyVisiable).toBool())
			{
				if (!myModel->property("SmallHeadImage").toBool())
				{
					auto pTreeView = qobject_cast<const QTreeView*>(option.widget);
					if (pTreeView->currentIndex() == index)
					{
						size.setHeight(70);
					}
					else
					{
						size.setHeight(50);
					}
				}
				else
				{
					auto pTreeView = qobject_cast<const QTreeView*>(option.widget);
					if (pTreeView->currentIndex() == index)
					{
						size.setHeight(40);
					}
					else
					{
						size.setHeight(30);
					}
				}
			}
			else
			{
				size.setHeight(0);
			}
		}
	}
	
	return size;
}

void CMyDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
	return __super::drawDisplay(painter, option, rect, text);
}

void CMyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.isValid())
	{
		auto myModel = index.model();
		int nType = myModel->data(index, Qt::UserRole + EnumUserPropertyType).toInt();
		if (nType == EnumTreeItemTypeUser)
		{
			bool bvisible = myModel->data(index, Qt::UserRole + EnumUserPropertyVisiable).toBool();
			if (bvisible)
			{
				QVariant vtGray = myModel->data(index, Qt::UserRole + EnumUserPropertyGray);
				bool bGray = vtGray.toBool();
				QVariant vt;
				if (bGray)
				{
					vt = myModel->data(index, Qt::UserRole + EnumUserPropertyGrayHeadImage);
				}
				else
				{
					vt = myModel->data(index, Qt::UserRole + EnumUserPropertyHeadImage);
				}
				QPixmap image = vt.value<QPixmap>();
				int nHeight = 40;
				if (myModel->property("SmallHeadImage").toBool())
				{
					nHeight = 20;
				}
				QRect rc(option.rect.left(), option.rect.top() + 5, nHeight, nHeight);

				drawBackground(painter, option, index);
				painter->drawPixmap(rc, image);

				//painter->fillRect(rc, QBrush(Qt::darkBlue,Qt::Dense3Pattern));

				QRect rcText(rc.right(), rc.top(), option.rect.width() - nHeight, 20);

				QVariant vtText = myModel->data(index, Qt::UserRole + EnumUserPropertyNickName);
				painter->drawText(rcText, vtText.toString());

				auto pTreeView = qobject_cast<const QTreeView*>(option.widget);
				if (pTreeView->currentIndex() == index)
				{
					QRect rcText(option.rect.left(), option.rect.top() + 50, option.rect.width(), 20);
					QString strTipText = QString(QStringLiteral("当前条目:%1")).arg(vtText.toString());
					painter->drawText(rcText, strTipText);
				}
			}
		}
		else
		{
			auto state = option.state;
			QString strState;
			if (state & QStyle::State_Open)
			{
				strState=QStringLiteral("下拉");
			}
			else
			{
				strState=QStringLiteral("收起");
			}
			QRect rcText(option.rect.left() + 10, option.rect.top(), option.rect.width() - 10, 24);
			QVariant vtText = myModel->data(index, Qt::UserRole + EnumUserPropertyNickName);
			painter->drawText(rcText, strState + vtText.toString());
		}
	}
	else
	{
		return __super::paint(painter, option, index);
	}
}

void CMyDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (option.showDecorationSelected)
	{
		auto myModel = index.model();
		int nType = myModel->data(index, Qt::UserRole + EnumUserPropertyType).toInt();
		if (nType == EnumTreeItemTypeUser)
		{
			if (option.state & QStyle::State_Selected)
			{
				QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
					? QPalette::Normal : QPalette::Disabled;
				if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
					cg = QPalette::Inactive;

				painter->fillRect(option.rect, QColor(252,234,164));
			}
			else if (option.state & QStyle::State_MouseOver)
			{
				QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
					? QPalette::Normal : QPalette::Disabled;
				if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
					cg = QPalette::Inactive;

				painter->fillRect(option.rect, QColor(252,240,194));
			}
		}
		else
		{
			return;
		}
	}
}

QVector<int> CMyDelegate::paintingRoles() const
{
	QVector<int> v;
	v << Qt::UserRole << (Qt::UserRole + 1);
	return v;
}

bool CMyDelegate::eventFilter(QObject *pObject, QEvent *pEvent)
{
	if (QEvent::MouseButtonRelease == pEvent->type())
	{
		QTreeView *pTreeView = qobject_cast<QTreeView*>(pObject->parent());
		auto currentIndex = pTreeView->currentIndex();
		if (currentIndex.isValid())
		{
			auto myModel = currentIndex.model();
			int nType = myModel->data(currentIndex, Qt::UserRole + EnumUserPropertyType).toInt();
			if (nType == EnumTreeItemTypeGroup)
			{
				pTreeView->setExpanded(currentIndex, !pTreeView->isExpanded(currentIndex));
			}
		}
	}
	else if (QEvent::ToolTip == pEvent->type())
	{
		QHelpEvent *p = static_cast<QHelpEvent*>(pEvent);
		QTreeView *pTreeView = qobject_cast<QTreeView*>(pObject->parent());
		auto index = pTreeView->indexAt(p->pos());
		if (index.isValid())
		{
			auto p = index.model();
			//p->data(index, )
			//TreeItemInfo *pInfo = index.internalPointer();
		}
	}
	return __super::eventFilter(pObject, pEvent);
}

void CMyDelegate::MyCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	emit sizeHintChanged(current);
	emit sizeHintChanged(previous);
}
