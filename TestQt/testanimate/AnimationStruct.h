#pragma once
#include <QString>
#include <QVariant>

struct AnimationProperty
{
	QString name;
	QString value;
};

struct AnimationItem
{
	QString itemType;
	QString itemName;
	std::vector<AnimationProperty> propertys;
};

struct Animation
{
	QString type;
	QString itemName;

};