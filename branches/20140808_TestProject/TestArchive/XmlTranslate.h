#pragma once
#include "XmlSerialization.h"
#include "Markup.h"
#include "ConfigNode.h"

#define MAX_XML_DEPTH		(30)
#define TAB_STRING			('\t')
#define CHILD_NAME			("child")
#define CHILD_KEY_NAME		("key")
#define CHILD_VALUE_NAME	("value")
#define ATTRIBUTE_TYPE		("type")
#define CHILD_TYPE			("childtype")
#define CHILD_TYPE2			("childtype2")
#define XML_ROOT_NAME		("root")

class CXmlTranslate
{
public:
	CXmlTranslate(void);
	~CXmlTranslate(void);
public:
	BOOL	ToXml(char *pBuffer, DWORD dwLen, std::string &strXml);
	BOOL	FromXml(char *pBuffer, DWORD dwLen, std::string &strData);
	BOOL	NodeToXml(ConfigStructNode *pNodeBase, std::string &strXml);
public:
	BOOL	NodeToStream(ConfigNodeBase *pNodeBase, std::string &strData);
	BOOL	NormalNodeToStream(ConfigNormalNode *pNodeNormal);
protected:
	BOOL	ParseStructNode(ConfigStructNode *pNodeStruct);
protected:
	BOOL	ParseOneField(CSerialization &GlobalSeri);
	BOOL	ParseFieldInfo(char *pBuffer, DWORD dwLen, XmlSerializationInfoArray &InfoArray);
	BOOL	ParseBaseValue(CSerialization &GlobalSeri, DWORD dwChildType, const char *pChildName = CHILD_NAME);
	BOOL	ParseStructValue(CSerialization &GlobalSeri, const char *pChildName = CHILD_NAME);
	BOOL	ParseMapInfo(CSerialization &GlobalSeri, XmlSerializationInfo &Info);
protected:
	BOOL	ParseXmlStructValue(CMarkup &xml, CSerialization &GlobalSeri);
	BOOL	ParseXmlBaseValue(CSerialization &GlobalSeri, DWORD dwType, const std::string &strValue);
private:
	BOOL	AppendTabString(std::string &strText);
private:
	std::vector<std::string>	m_strXmlDepthText;
	DWORD	m_dwDepth;		//表示当前进入的深度
};

