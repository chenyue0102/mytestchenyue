#include "MyQuickWidget.h"
#include <assert.h>
#include <QQuickItem>
#include <QQmlContext>


MyQuickWidget::MyQuickWidget(QWidget *parent)
	: QQuickWidget(parent)
{
	connect(this, &QQuickWidget::statusChanged, this, [this](QQuickWidget::Status status) 
	{
		if (status == Ready)
		{
			//QQuickWidget������qml���õĴ�С������С�����������ٵ����£�Ȼ���������ű��ʣ�֧��qml����
			QWidget *parent = parentWidget();
			if (nullptr != parent)
			{
				resize(parent->size());
			}
			setQmlSize();
		}
	});
}

MyQuickWidget::~MyQuickWidget()
{
}

void MyQuickWidget::setQmlSize()
{
	QQuickItem *obj = rootObject();
	if (nullptr != obj)
	{
		QSize sz = size();
		//QMetaObject::invokeMethod(obj, "setContainerSize", Q_ARG(QVariant, QVariant(sz.width())), Q_ARG(QVariant, QVariant(sz.height())));
	}
}

void MyQuickWidget::resizeEvent(QResizeEvent *event)
{
	__super::resizeEvent(event);
	setQmlSize();
}