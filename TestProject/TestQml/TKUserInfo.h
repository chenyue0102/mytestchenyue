#pragma once
#include "QObject"
#include <QMessageBox>
#include <QAbstractListModel>
#include <assert.h>

struct TKUserInfo
        : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TKUserInfo(QObject *p = NULL): _userID(0){;}

public:
    Q_INVOKABLE QString GetText()const
    {
        return _userNickName;
    }
    Q_PROPERTY(unsigned long userID READ userID WRITE setUserID)
    Q_PROPERTY(QString userNickName READ userNickName WRITE setUserNickName NOTIFY userNickNameChanged)
Q_SIGNALS:
	void userNickNameChanged(const QString &userNickName);
public:
    Q_DISABLE_COPY(TKUserInfo)
    unsigned long userID()const{return _userID;}
    void setUserID(unsigned long id){_userID = id;}
    QString userNickName()const{return _userNickName;}
	void setUserNickName(QString str)
	{
		if (_userNickName != str)
		{
			_userNickName = str;
			emit userNickNameChanged(_userNickName);
		}
	}

    unsigned long   _userID;
    QString     _userNickName;
};

class QContectModel 
	: public QAbstractListModel
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit QContectModel(QObject *parent = 0)
		: QAbstractListModel(parent)
	{
		int nRole = Qt::UserRole;
		m_roleNames.insert(nRole++, "name");
		m_roleNames.insert(nRole++, "groupid");
		m_roleNames.insert(nRole++, "gray");
		m_roleNames.insert(nRole++, "headImage");

		for (int a = 0; a < 20; a++)
		{
			QContectItem ContectItem;
			QVariant vt;
			QString strNickName;
			strNickName = QString(QStringLiteral("Í«≥∆%1")).arg(a);
			ContectItem.push_back(strNickName);
			ContectItem.push_back(a > 10 ? 1: 2);
			ContectItem.push_back(a > 10 ? false: true);
			QString strHeadImage;
			strHeadImage = QString(QStringLiteral("file:///D:\\JJ±»»¸Õ‚Õ¯≤‚ ‘\\LobbyTheme\\HeadImage\\H000%1.jpg")).arg(a + 10);
			ContectItem.push_back(strHeadImage);
			m_ContectItemArray.push_back(ContectItem);
		}
	}
public:
	Q_INVOKABLE virtual int rowCount(const QModelIndex &parent/* = QModelIndex()*/) const
	{
		return m_ContectItemArray.size();
	}
	Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role/* = Qt::DisplayRole*/) const
	{
		if (index.row() < 0 || index.row() >= m_ContectItemArray.size())
			return QVariant();

		if (role == Qt::DisplayRole || role == Qt::EditRole)
		{
			return QVariant("empty role");
		}
		else if (role >= Qt::UserRole)
		{
			auto Item = m_ContectItemArray.at(index.row());
			int nIndex = role - Qt::UserRole;
			if (nIndex < Item.size())
			{
				return Item.at(nIndex);
			}
			else
			{
				assert(false);
				return QVariant();
			}
		}

		return QVariant();
	}
public:
	Q_INVOKABLE virtual QHash<int,QByteArray> roleNames() const
	{
		return m_roleNames;
	}
public:
	bool removeRows(int row, int count, const QModelIndex &parent /*= QModelIndex()*/)
	{
		if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
			return false;

		beginRemoveRows(QModelIndex(), row, row + count - 1);

		for (int r = 0; r < count; ++r)
			m_ContectItemArray.removeAt(row);

		endRemoveRows();

		return true;
	}
	bool insertRows(int row, int count, const QModelIndex &parent /*= QModelIndex()*/)
	{
		if (count < 1 || row < 0 || row > rowCount(parent))
			return false;

		beginInsertRows(QModelIndex(), row, row + count - 1);

		for (int r = 0; r < count; ++r)
		{
			static int a = 30;
			a++;
			QContectItem ContectItem;
			QVariant vt;
			QString strNickName;
			strNickName = QString(QStringLiteral("Í«≥∆%1")).arg(a);
			ContectItem.push_back(strNickName);
			ContectItem.push_back(a > 10 ? 1: 2);
			ContectItem.push_back(a > 10 ? false: true);
			QString strHeadImage;
			strHeadImage = QString(QStringLiteral("file:///D:\\JJ±»»¸Õ‚Õ¯≤‚ ‘\\LobbyTheme\\HeadImage\\H000%1.jpg")).arg(a + 10);
			ContectItem.push_back(strHeadImage);
			m_ContectItemArray.insert(row, ContectItem);
		}

		endInsertRows();

		return true;
	}

	bool setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
	{
		if (index.row() >= 0 && index.row() < m_ContectItemArray.size()
			&& role >= Qt::UserRole) {
				m_ContectItemArray[index.row()].replace(role - Qt::UserRole, value);
				emit dataChanged(index, index, QVector<int>() << role);
				return true;
		}
		return false;
	}
private:
	QHash<int, QByteArray>	m_roleNames;
	typedef QVector<QVariant>	QContectItem;
	QVector<QContectItem>	m_ContectItemArray;
};

class QUINotify
	: public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit QUINotify(QObject *parent=0): QObject(parent){;}
	virtual ~QUINotify(){;}
public:
	Q_INVOKABLE void notifyEvent(unsigned long lType, QString strName)
	{
		extern QContectModel ContectModel;
		if (1 == lType)
		{
			QMessageBox msgBox;
			msgBox.setText(strName);
			msgBox.exec();
			extern TKUserInfo UserInfo;
			UserInfo.setUserNickName(strName);
		}
		else if (2 == lType)
		{
			ContectModel.removeRow(strName.toInt());
		}
		else if (3 == lType)
		{
			ContectModel.insertRows(strName.toInt(), 1, QModelIndex());
		}
		else if (4 == lType)
		{
			ContectModel.setData(ContectModel.index(strName.toInt()), true, Qt::UserRole + 2);
		}
		else if (5 == lType)
		{
			ContectModel.setData(ContectModel.index(strName.toInt()), QVariant(false), Qt::UserRole + 2);
		}
	}
private:
	Q_DISABLE_COPY(QUINotify)
};