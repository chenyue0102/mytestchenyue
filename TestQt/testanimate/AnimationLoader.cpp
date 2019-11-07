#include "AnimationLoader.h"
#include <assert.h>
#include "json/value.h"
#include "json/reader.h"
#include "AnimationStruct.h"

namespace AnimationLoader
{
//
bool parseAnimation(Json::Value &node, Animation &animation)
{
	if (node.isObject())
	{
		for (auto iter = node.begin(); iter != node.end(); ++iter)
		{
			std::string name = iter.name();
			
			if (name == "type")
			{
				animation.type = iter->asString();
			}
			else if (name == "targetObjectName")
			{
				animation.targetObjectName = iter->asString();
			}
			else if (name == "childred")
			{
				if (!iter->isArray())
				{
					assert(false);
					continue;
				}
				for (Json::ArrayIndex i = 0; i < (*iter).size(); i++)
				{
					Animation child;
					if (!parseAnimation((*iter)[i], child))
					{
						assert(false);
						continue;
					}
					animation.children.push_back(child);
				}
			}
			else
			{
				if (!iter->isString())//ÊôÐÔ±ØÐëÊÇ×Ö·û´®
				{
					assert(false);
					continue;
				}
				AnimationProperty prop;
				prop.name = name;
				prop.value = iter->asString();
				animation.propertys.push_back(prop);
			}
		}
		return !animation.type.empty();
	}
	else
	{
		assert(false);
		return false;
	}
}

bool parseItem(Json::Value &node, AnimationItem &item)
{
	if (node.isObject())
	{
		for (auto iter = node.begin(); iter != node.end(); ++iter)
		{
			std::string name = iter.name();
			if (name == "proxyWidget")
			{
				if (!iter->isObject())
				{
					assert(false);
					continue;
				}
				AnimationItem proxyItem;
				if (!parseItem((*iter), proxyItem))
				{
					assert(false);
					continue;
				}
				item.pProxyWidget.reset(new AnimationItem());
				*(item.pProxyWidget) = proxyItem;
			}
			else
			{
				if (!iter->isString())//ÊôÐÔ±ØÐëÊÇ×Ö·û´®
				{
					assert(false);
					continue;
				}
				std::string value = iter->asString();
				if (name == "name")
				{
					item.name = value;
				}
				else if (name == "type")
				{
					item.type = value;
				}
				else
				{
					AnimationProperty prop;
					prop.name = name;
					prop.value = value;
					item.propertys.push_back(prop);
				}
			}
		}
		return !item.name.empty() && !item.type.empty();
	}
	else
	{
		assert(false);
		return false;
	}
}

bool parseJson(const char *pData, int length, AnimationInfo &info)
{
	bool ret = false;
	do
	{
		Json::Value value;
		Json::Reader r;
		if (!r.parse(pData, pData + length, value))
		{
			assert(false);
			break;
		}
		Json::Value itemsNode = value["item"];
		if (!itemsNode.isArray())
		{
			assert(false);
			break;
		}

		for (Json::ArrayIndex i = 0; i < itemsNode.size(); i++)
		{
			Json::Value &node = itemsNode[i];
			AnimationItem item;
			if (!parseItem(node, item))
			{
				assert(false);
				continue;
			}
			info.items.push_back(item);
		}

		Json::Value animation = value["animation"];
		if (!parseAnimation(animation, info.animation))
		{
			assert(false);
			break;
		}
		ret = true;
	} while (false);
	return ret;
}

}
