#pragma once
#include "AnimationStruct.h"

namespace AnimationLoader
{
QObject* createObject(const QString &type, const QString &name, const std::vector<AnimationProperty> &propertys);
};

