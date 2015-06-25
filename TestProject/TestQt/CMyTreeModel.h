#ifndef CMYTREEMODEL_H
#define CMYTREEMODEL_H

#include <QAbstractItemModel>
#include "UserTreeItem.h"

class CMyTreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	CMyTreeModel(QObject *parent);
	~CMyTreeModel();

public:
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	virtual QHash<int,QByteArray> roleNames() const;
private:
	QHash<int, QByteArray>	m_roleNames;
	TreeItemInfo	*m_rootItem;
};

#endif // CMYTREEMODEL_H
