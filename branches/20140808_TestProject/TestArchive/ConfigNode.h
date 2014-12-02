#pragma once
#include "XmlSerialization.h"
#include <boost/shared_ptr.hpp>
#include <map>


struct ConfigNodeBase
{
	ConfigNodeBase(): m_dwType(XmlFieldTypeNone){;}
	virtual ~ConfigNodeBase(){;}
	DWORD		m_dwType;
};

typedef std::map<std::string, boost::shared_ptr<ConfigNodeBase> > ConfigNameNodeArray;
typedef std::vector<boost::shared_ptr<ConfigNodeBase> > ConfigNodeArray;

struct ConfigNormalNode  : public ConfigNodeBase
{
public:
	BOOL	PutValue(DWORD dwType, std::string &strValue);
public:
	std::string		m_strValue;
};

struct ConfigStructNode : public ConfigNodeBase
{
	BOOL	FindNode(const std::string &strName, boost::shared_ptr<ConfigNodeBase> &pNodeBase);
	BOOL	InsertNode(const std::string &strName, boost::shared_ptr<ConfigNodeBase> &pNodeBase);
	ConfigNameNodeArray		m_ConfigNameNodeArray;
};

struct ConfigVector
{
	ConfigNodeArray			m_ConfigNodeArray;
};