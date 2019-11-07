#include "ObjectMaker.h"
#include <assert.h>
#include <functional>

#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>

#include <QLabel>
#include <QPushButton>

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

#include "MyGraphicsTextItem.h"

namespace ObjectMaker
{
#define CREATE_INFO(className)\
	std::pair<std::string, ObjectCreateInfo>(#className, ObjectCreateInfo(#className, []()->className* {return new className(); }))

struct ObjectCreateInfo
{
	std::string className;
	std::function<QObject*()> createFun;

	ObjectCreateInfo(const std::string &name, std::function<QObject*()> fun)
		: className(name)
		, createFun(fun)
	{}

	static const std::map<std::string, ObjectCreateInfo>& getObjectCreateFuns()
	{
		static std::map<std::string, ObjectCreateInfo> createFuns =
		{
			CREATE_INFO(QGraphicsTextItem),
			CREATE_INFO(QGraphicsProxyWidget),

			CREATE_INFO(QLabel),
			CREATE_INFO(QPushButton),

			CREATE_INFO(MyGraphicsTextItem),
			CREATE_INFO(QSequentialAnimationGroup),
			CREATE_INFO(QPropertyAnimation),
		};
		return createFuns;
	}
};

QObject * createObject(const std::string & type)
{
	QObject *obj = nullptr;
	auto &createFuns = ObjectCreateInfo::getObjectCreateFuns();
	auto iter = createFuns.find(type);
	if (iter != createFuns.end()
		&& iter->second.createFun)
	{
		obj = iter->second.createFun();
	}
	return obj;
}

QObject* createObject(const std::string &type, const std::string &name)
{
	QObject *obj = createObject(type);
	if (nullptr != obj)
	{
		obj->setObjectName(name.c_str());
	}
	return obj;
}

};
