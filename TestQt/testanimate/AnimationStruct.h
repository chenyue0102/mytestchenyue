#pragma once
#include <memory>
#include <QString>
#include <QVariant>

struct AnimationProperty
{
	std::string name;
	std::string value;
};
//¶¯»­¿Ø¼þ
struct AnimationItem
{
	std::string type;
	std::string name;
	std::vector<AnimationProperty> propertys;
	std::shared_ptr<AnimationItem> pProxyWidget;
};
//¶¯»­
struct Animation
{
	std::string type;
	std::string targetObjectName;
	std::vector<AnimationProperty> propertys;
	std::vector<Animation> children;
};

struct AnimationInfo
{
	std::vector<AnimationItem> items;
	Animation animation;
};