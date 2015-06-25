#include "CloseActionTemplate.h"
#include <QEvent>
#include <QVariant>


CCloseActionFunction::CCloseActionFunction(QObject *parent)
	: QObject(parent)
{
	parent->installEventFilter(this);
}


CCloseActionFunction::~CCloseActionFunction(void)
{

}

bool CCloseActionFunction::eventFilter(QObject *p, QEvent *e)
{
	if (e->type() == QEvent::Close)
	{
		if (m_CallbackFun)
		{
			QVariant vt = p->property("exitcode");
			int nResult = vt.toInt();
			m_CallbackFun(nResult);
		}
		p->removeEventFilter(this);
	}
	return __super::eventFilter(p,e);
}
