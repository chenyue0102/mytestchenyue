#pragma once
#include <QObject>
namespace ObjectMaker
{
QObject * createObject(const std::string & type);
QObject* createObject(const std::string &type, const std::string &name);
};

