#pragma once
#include <QObject>
#include <functional>

class CCloseActionFunction
	: public QObject
{
	Q_OBJECT
public:
	CCloseActionFunction(QObject *parent);
	~CCloseActionFunction(void);
public:
	virtual bool eventFilter(QObject *, QEvent *);
	std::function<void(int nResult)> m_CallbackFun;
};

