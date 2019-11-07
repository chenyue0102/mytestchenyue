#pragma once
#include <QVariant>

namespace PropertyApply
{
QVariant::Type getPropertyType(QObject *obj, const std::string &name);
bool applyProperty(QObject * obj, const std::string & name, const std::string & value);
};

