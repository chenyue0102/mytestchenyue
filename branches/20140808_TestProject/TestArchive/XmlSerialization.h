#pragma once
#include "Serialization.h"
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

#define DEF_XML_SS_VALUE(aSerialization,classname) \
	CXmlSerialization XmlSerialization(aSerialization,classname); \


#define XML_SS_VALUE(value) \
	XmlSerialization.XmlSSValue(value,#value); \

#define XML_SS_VECTOR_VALUE(value) \
	XmlSerialization.XmlSSVectorValue(value,#value); \


enum XmlFieldType
{
	XmlFieldTypeNone	= 0x00000000,
	XmlFieldTypeBool	= 1,
	XmlFieldTypeChar	= 2,
	XmlFieldTypeShort	= 3,
	XmlFieldTypeInt		= 4,
	XmlFieldTypeLong	= 5,
	XmlFieldTypeFloat	= 6,
	XmlFieldTypeDouble	= 7,
	XmlFieldTypeString	= 8,
	XmlFieldTypeUChar	= 9,
	XmlFieldTypeUShort	= 10,
	XmlFieldTypeUInt	= 11,
	XmlFieldTypeULong	= 12,
	XmlFiendTypeBaseMax	= 999,//基本数据
	XmlFieldTypeStruct	= 1000,	//表示可以序列化的自定义结构体
	XmlFieldTypeVector	= 1001,	//表示vector,list,deque,set
	XmlFieldTypeMap		= 1002,//表示map
	XmlFieldTypeMax,
};

inline BOOL IsNormalFileType(DWORD dwType)
{
	return (dwType >= XmlFieldTypeBool && dwType <XmlFiendTypeBaseMax);
}

#define XML_INNER_SERIALIZATION_VALUE_FUN(Type,FieldType) \
static BOOL	XmlInnerSerializationValue(Type &t,CSerialization &cs, DWORD &dwType) \
{ \
	cs.Serialization(t);\
	dwType = FieldType; \
	return TRUE; \
}\


XML_INNER_SERIALIZATION_VALUE_FUN(bool,XmlFieldTypeBool)
XML_INNER_SERIALIZATION_VALUE_FUN(char,XmlFieldTypeChar)
XML_INNER_SERIALIZATION_VALUE_FUN(short,XmlFieldTypeShort)
XML_INNER_SERIALIZATION_VALUE_FUN(int,XmlFieldTypeInt)
XML_INNER_SERIALIZATION_VALUE_FUN(long,XmlFieldTypeLong)
XML_INNER_SERIALIZATION_VALUE_FUN(float,XmlFieldTypeFloat)
XML_INNER_SERIALIZATION_VALUE_FUN(double,XmlFieldTypeDouble)
XML_INNER_SERIALIZATION_VALUE_FUN(std::string,XmlFieldTypeString)

XML_INNER_SERIALIZATION_VALUE_FUN(unsigned char,XmlFieldTypeUChar)
XML_INNER_SERIALIZATION_VALUE_FUN(unsigned short,XmlFieldTypeUShort)
XML_INNER_SERIALIZATION_VALUE_FUN(unsigned int,XmlFieldTypeUInt)
XML_INNER_SERIALIZATION_VALUE_FUN(unsigned long,XmlFieldTypeULong)

template<typename T>
BOOL	XmlInnerSerializationValue(T &t, CSerialization &cs, DWORD &dwType)
{
	dwType = XmlFieldTypeStruct;
	return t.Serialization(cs);
}

#define XML_INNER_SERIALIZATION_VECTOR_FUN(Type) \
template<typename T> \
static BOOL XmlInnerSerializationVecotr(Type<T> &t, CSerialization &cs, DWORD &dwFatherType, DWORD &dwChildType, DWORD &dwChildType2) \
{ \
	DWORD dwSize = t.size(); \
	dwFatherType = XmlFieldTypeVector; \
	dwChildType2 = XmlFieldTypeNone; \
	DWORD dwTempType = XmlFieldTypeNone; \
	XmlInnerSerializationValue(dwSize,cs, dwTempType); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			Type<T>::value_type onevalue; \
			XmlInnerSerializationValue(onevalue,cs, dwChildType); \
			t.push_back(onevalue); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<T>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			XmlInnerSerializationValue(*itor, cs, dwChildType); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

XML_INNER_SERIALIZATION_VECTOR_FUN(std::vector)
XML_INNER_SERIALIZATION_VECTOR_FUN(std::list)
XML_INNER_SERIALIZATION_VECTOR_FUN(std::deque)


#define XML_INNER_SERIALIZATION_SET_FUN(Type) \
template<typename T> \
static BOOL XmlInnerSerializationVecotr(Type<T> &t, CSerialization &cs, DWORD &dwFatherType, DWORD &dwChildType, DWORD &dwChildType2) \
{ \
	DWORD dwSize = t.size(); \
	dwFatherType = XmlFieldTypeVector; \
	dwChildType2 = XmlFieldTypeNone; \
	DWORD dwTempType = XmlFieldTypeNone; \
	XmlInnerSerializationValue(dwSize,cs, dwTempType); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			Type<T>::value_type onevalue; \
			XmlInnerSerializationValue(onevalue,cs, dwChildType); \
			t.insert(onevalue); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<T>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			T &value= const_cast<T&>(*itor); \
			XmlInnerSerializationValue(value, cs, dwChildType); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

XML_INNER_SERIALIZATION_SET_FUN(std::set)


#define XML_INNER_SERIALIZATION_MAP_FUN(Type) \
template<typename MAPKEY, typename MAPVALUE> \
static BOOL XmlInnerSerializationVecotr(Type<MAPKEY,MAPVALUE> &t, CSerialization &cs, DWORD &dwFatherType, DWORD &dwChildType, DWORD &dwChildType2) \
{ \
	DWORD dwSize = t.size(); \
	dwFatherType = XmlFieldTypeMap; \
	DWORD dwTempType = XmlFieldTypeNone; \
	XmlInnerSerializationValue(dwSize,cs, dwTempType); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			MAPKEY key; \
			MAPVALUE value; \
			XmlInnerSerializationValue(key,cs, dwChildType); \
			XmlInnerSerializationValue(value,cs, dwChildType2); \
			t.insert(std::make_pair(key,value)); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<MAPKEY,MAPVALUE>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			MAPKEY &key = const_cast<MAPKEY &>(itor->first); \
			MAPVALUE &value = itor->second; \
			XmlInnerSerializationValue(key, cs, dwChildType); \
			XmlInnerSerializationValue(value, cs, dwChildType2); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

XML_INNER_SERIALIZATION_MAP_FUN(std::map)



struct XmlSerializationHead
{
	DWORD	dwSectionLen;		//节总长度，包括sizeof(SerializationHead)+dwDataLen+末尾的索引表
	DWORD	dwDataLen;			//数据长度
	XmlSerializationHead():dwSectionLen(0),dwDataLen(0){;}
	BOOL	Serialization(CSerialization &s)
	{
		s.Serialization(dwSectionLen);
		s.Serialization(dwDataLen);
		return TRUE;
	}
};

struct XmlSerializationInfo
{
	DWORD		dwOffset;	//偏移的位置，相对于此节
	DWORD		dwLen;		//这个字段长度
	DWORD		dwType;		//类型，参照枚举XmlFieldType
	DWORD		dwChildType;//如果dwType是vecotr类型，则此为子结构体类型，其他的情况下，无效
	DWORD		dwChildType2;//如果dwType是map的类型，此数据有效，表示map中value类型，dwChildType表示map中key类型
	std::string strName;	//名字
	XmlSerializationInfo():dwOffset(0),dwLen(0),dwType(XmlFieldTypeNone),dwChildType(XmlFieldTypeNone),dwChildType2(XmlFieldTypeNone){;}
	BOOL	Serialization(CSerialization &s)
	{
		s.Serialization(dwOffset);
		s.Serialization(dwLen);
		s.Serialization(dwType);
		s.Serialization(dwChildType);
		s.Serialization(dwChildType2);
		s.Serialization(strName);
		return TRUE;
	}
};
typedef std::vector<XmlSerializationInfo> XmlSerializationInfoArray;
class CXmlSerialization
{
public:
	CXmlSerialization(CSerialization &s, const char *pstrName);
	~CXmlSerialization(void);
public:
	template <typename T>
	BOOL	XmlSSValue(T &t, const char *pstrName)
	{
		DWORD dwType = XmlFieldTypeNone;
		if (enum_Serialization_Type_Read == m_Serialization.GetSerializationType())
		{
			for (DWORD dwIndex = 0; dwIndex < m_SerializationInfoArray.size(); dwIndex++)
			{
				if (m_SerializationInfoArray[dwIndex].strName == pstrName)
				{
					DWORD dwDataOffset = m_SerializationInfoArray[dwIndex].dwOffset + m_dwHeadOffset;
					char *pData = m_Serialization.m_pBuffer + dwDataOffset;
					CSerialization tempSeri(pData, m_Serialization.m_dwBufferLen - dwDataOffset);
					tempSeri.SetSerializationType(enum_Serialization_Type_Read);
					XmlInnerSerializationValue(t, tempSeri, dwType);
					return TRUE;
				}
			}
			return FALSE;
		}
		else
		{
			XmlSerializationInfo Info;
			Info.strName = pstrName;
			Info.dwOffset = m_Serialization.m_dwDataLen - m_dwHeadOffset;
			XmlInnerSerializationValue(t, m_Serialization, dwType);
			Info.dwType = dwType;
			Info.dwLen = m_Serialization.m_dwDataLen - Info.dwOffset - m_dwHeadOffset;
			m_SerializationInfoArray.push_back(Info);
		}
		return TRUE;
	}
	template <typename T>
	BOOL	XmlSSVectorValue(T &t, const char *pstrName)
	{
		DWORD dwFatherType = XmlFieldTypeNone, dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;;
		if (enum_Serialization_Type_Read == m_Serialization.GetSerializationType())
		{
			for (DWORD dwIndex = 0; dwIndex < m_SerializationInfoArray.size(); dwIndex++)
			{
				if (m_SerializationInfoArray[dwIndex].strName == pstrName)
				{
					DWORD dwDataOffset = m_SerializationInfoArray[dwIndex].dwOffset + m_dwHeadOffset;
					char *pData = m_Serialization.m_pBuffer + dwDataOffset;
					CSerialization tempSeri(pData, m_Serialization.m_dwBufferLen - dwDataOffset);
					tempSeri.SetSerializationType(enum_Serialization_Type_Read);
					XmlInnerSerializationVecotr(t, tempSeri, dwFatherType, dwChildType, dwChildType2);
					return TRUE;
				}
			}
			return FALSE;
		}
		else
		{
			XmlSerializationInfo Info;
			Info.strName = pstrName;
			Info.dwOffset = m_Serialization.m_dwDataLen - m_dwHeadOffset;
			XmlInnerSerializationVecotr(t, m_Serialization, dwFatherType, dwChildType, dwChildType2);
			Info.dwType = dwFatherType;
			Info.dwLen = m_Serialization.m_dwDataLen - Info.dwOffset - m_dwHeadOffset;
			Info.dwChildType = dwChildType;
			Info.dwChildType2 = dwChildType2;
			m_SerializationInfoArray.push_back(Info);
		}
		return TRUE;
	}
protected:
	CSerialization		&m_Serialization;
	DWORD				m_dwHeadOffset;
	std::string			m_strObjectName;
protected:
	XmlSerializationInfoArray		m_SerializationInfoArray;
	XmlSerializationHead			m_SerializationHead;
};
