#include "PropertyApply.h"
#include <assert.h>
#include <QMetaProperty>
#include <QPropertyAnimation>
#include "TypeCover.h"


namespace PropertyApply
{
void test()
{

}
QVariant::Type getPropertyType(QObject *obj, const std::string &name)
{
	QVariant::Type type = QVariant::Invalid;

	do
	{
		if (nullptr == obj)
		{
			assert(false);
			break;
		}
		const QMetaObject *metaObj = obj->metaObject();
		if (nullptr == metaObj)
		{
			assert(false);
			break;
		}
		int indexProperty = metaObj->indexOfProperty(name.c_str());
		if (-1 == indexProperty)
		{
			assert(false);
			break;
		}
		QMetaProperty metaProperty = metaObj->property(indexProperty);
		type = metaProperty.type();
	} while (false);
	return type;
}

bool applyProperty(QObject * obj, const std::string & name, const std::string & value)
{
	bool ret = false;
	do
	{
		if (nullptr == obj)
		{
			assert(false);
			break;
		}
		if (name.empty()
			|| value.empty())
		{
			assert(false);
			break;
		}
		if (name == "startValue"
			|| name == "endValue")
		{
			QPropertyAnimation *propertyAnimation = qobject_cast<QPropertyAnimation*>(obj);
			if (nullptr != propertyAnimation)
			{
				QByteArray propertyName = propertyAnimation->propertyName();
				QObject *targetObj = propertyAnimation->targetObject();
				if (nullptr != targetObj)
				{
					propertyAnimation->setProperty(name.c_str(), TypeCover::cover(getPropertyType(targetObj, propertyName.data()), value));
					break;
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				assert(false);
			}
		}
		QVariant v = TypeCover::cover(getPropertyType(obj, name), value);
		obj->setProperty(name.c_str(), v);
		ret = true;
	} while (false);
	return ret;
}
}
