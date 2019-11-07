#include "testanimate.h"
#include <assert.h>
#include <QFile>
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include "AnimationStruct.h"
#include "AnimationLoader.h"
#include "ObjectMaker.h"
#include "PropertyApply.h"


testanimate::testanimate(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonLoad, SIGNAL(clicked()), SLOT(onLoad()));
	QGraphicsScene *scene = new QGraphicsScene;
	ui.graphicsView->setScene(scene);
	ui.graphicsView->setFitSize(400, 300);
	scene->setSceneRect(0, 0, 400, 300);
	scene->setBackgroundBrush(QColor(0, 255, 255));
	//onLoad();
}

QObject* createAndApplyProperty(const AnimationItem &item)
{
	bool ret = false;
	QObject *obj = nullptr;

	do
	{
		obj = ObjectMaker::createObject(item.type, item.name);
		if (nullptr == obj)
		{
			assert(false);
			break;
		}
		for (auto &prop : item.propertys)
		{
			PropertyApply::applyProperty(obj, prop.name, prop.value);
		}
		ret = true;
	} while (false);
	if (!ret)
	{
		delete obj;
		obj = nullptr;
	}
	return obj;
}

QAbstractAnimation* createAndApplyProperty(QObject *itemContainer, const Animation &animation)
{
	bool ret = false;
	QAbstractAnimation *obj = nullptr;

	do
	{
		QObject *tmpObj = ObjectMaker::createObject(animation.type);
		if (nullptr == tmpObj)
		{
			assert(false);
			break;
		}
		if (nullptr == (obj = qobject_cast<QAbstractAnimation*>(tmpObj)))
		{
			delete tmpObj;
			assert(false);
			break;
		}
		
		if (!animation.targetObjectName.empty())
		{
			QPropertyAnimation *propertyAnimation = qobject_cast<QPropertyAnimation*>(obj);
			if (nullptr == propertyAnimation)
			{
				assert(false);
				break;
			}
			if (nullptr == itemContainer)
			{
				assert(false);
				break;
			}
			QObject *targetObj = itemContainer->findChild<QObject*>(QString::fromStdString(animation.targetObjectName));
			if (nullptr == targetObj)
			{
				assert(false);
				break;
			}
			propertyAnimation->setTargetObject(targetObj);
		}
		for (auto &prop : animation.propertys)
		{
			PropertyApply::applyProperty(obj, prop.name, prop.value);
		}
		for (auto &child : animation.children)
		{
			QObject *childObj = createAndApplyProperty(itemContainer, child);
			if (nullptr == childObj)
			{
				assert(false);
				continue;
			}
			childObj->setParent(obj);
		}
		ret = true;
	} while (false);
	if (!ret)
	{
		delete obj;
		obj = nullptr;
	}
	return obj;
}

void testanimate::onLoad()
{
	AnimationInfo info;
	QFile f("test.json");
	do
	{
		if (!f.open(QFile::ReadOnly))
		{
			assert(false);
			break;
		}
		QByteArray data = f.readAll();
		f.close();
		if (!AnimationLoader::parseJson(data.data(), data.size(), info))
		{
			assert(false);
			break;
		}
		QGraphicsScene *scene = ui.graphicsView->scene();
		for (auto &item : info.items)
		{
			QObject *tmpObj = createAndApplyProperty(item);
			if (nullptr == tmpObj)
			{
				assert(false);
				continue;
			}
			QGraphicsObject *obj = qobject_cast<QGraphicsObject*>(tmpObj);
			if (nullptr == obj)
			{
				delete tmpObj;
				assert(false);
				continue;
			}
			
			QObject *proxyWidget = nullptr;
			if (item.pProxyWidget)
			{
				proxyWidget = createAndApplyProperty(*item.pProxyWidget);
			}
			if (nullptr != obj && nullptr != proxyWidget)
			{
				QGraphicsProxyWidget *graphicsProxyWidget = qobject_cast<QGraphicsProxyWidget*>(obj);
				QWidget *widget = qobject_cast<QWidget*>(proxyWidget);
				if (nullptr == graphicsProxyWidget
					|| nullptr == widget)
				{
					delete obj;
					delete proxyWidget;
					assert(false);
					continue;
				}
				graphicsProxyWidget->setWidget(widget);
			}
			scene->addItem(obj);
		}
		QAbstractAnimation *animation = createAndApplyProperty(scene, info.animation);
	} while (false);

}