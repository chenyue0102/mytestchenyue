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
			//QQuickWidget会依照qml设置的大小调整大小，这里重新再调整下，然后设置缩放比率，支持qml缩放
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