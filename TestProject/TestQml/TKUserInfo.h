#pragma once
#include "QObject"
#include <QMessageBox>
#include <QAbstractListModel>

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
			QMessageBox msgBox;
			msgBox.setText(strName);
			msgBox.exec();
			extern TKUserInfo UserInfo;
			UserInfo.setUserNickName(strName);
		}
private:
	Q_DISABLE_COPY(QUINotify)
};

class QContectModel 
	: public QAbstractListModel
{
	Q_OBJECT
public:
	explicit QContectModel(QObject *parent = 0)
		: QAbstractListModel(parent)
	{

	}

private:
	QHash<int, QByteArray>	m_roleNames;
	typedef QVector<QVariant>	QContectItem;
	QVector<QContectItem>	m_ContectItemArray;
};