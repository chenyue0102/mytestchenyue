#pragma once
#include "Serialization.h"
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

#define DEF_SS_VALUE(aSerialization) \
	CSafeSerialization SafeSerialization(aSerialization); \


#define SS_VALUE(value) \
	SafeSerialization.SSValue(value,#value); \

#define SS_VECTOR_VALUE(value) \
	SafeSerialization.SSVectorValue(value,#value); \





#define INNER_SERIALIZATION_VALUE_FUN(Type) \
static BOOL	InnerSerializationValue(Type &t,CSerialization &cs) \
{ \
	cs.Serialization(t);\
	return TRUE; \
}\


INNER_SERIALIZATION_VALUE_FUN(bool)
INNER_SERIALIZATION_VALUE_FUN(char)
INNER_SERIALIZATION_VALUE_FUN(short)
INNER_SERIALIZATION_VALUE_FUN(int)
INNER_SERIALIZATION_VALUE_FUN(long)
INNER_SERIALIZATION_VALUE_FUN(float)
INNER_SERIALIZATION_VALUE_FUN(double)
INNER_SERIALIZATION_VALUE_FUN(std::string)

INNER_SERIALIZATION_VALUE_FUN(unsigned char)
INNER_SERIALIZATION_VALUE_FUN(unsigned short)
INNER_SERIALIZATION_VALUE_FUN(unsigned int)
INNER_SERIALIZATION_VALUE_FUN(unsigned long)

template<typename T>
BOOL	InnerSerializationValue(T &t, CSerialization &cs)
{
	return t.Serialization(cs);
}

#define INNER_SERIALIZATION_VECTOR_FUN(Type) \
template<typename T> \
static BOOL InnerSerializationVecotr(Type<T> &t, CSerialization &cs) \
{ \
	DWORD dwSize = t.size(); \
	InnerSerializationValue(dwSize,cs); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			Type<T>::value_type onevalue; \
			InnerSerializationValue(onevalue,cs); \
			t.push_back(onevalue); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<T>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			InnerSerializationValue(*itor, cs); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

INNER_SERIALIZATION_VECTOR_FUN(std::vector)
INNER_SERIALIZATION_VECTOR_FUN(std::list)
INNER_SERIALIZATION_VECTOR_FUN(std::deque)

#define INNER_SERIALIZATION_MAP_FUN(Type) \
template<typename MAPKEY, typename MAPVALUE> \
static BOOL InnerSerializationVecotr(Type<MAPKEY,MAPVALUE> &t, CSerialization &cs) \
{ \
	DWORD dwSize = t.size(); \
	InnerSerializationValue(dwSize,cs); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			MAPKEY key; \
			MAPVALUE value; \
			InnerSerializationValue(key,cs); \
			InnerSerializationValue(value,cs); \
			t.insert(std::make_pair(key,value)); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<MAPKEY,MAPVALUE>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			MAPKEY &key = const_cast<MAPKEY &>(itor->first); \
			MAPVALUE &value = itor->second; \
			InnerSerializationValue(key, cs); \
			InnerSerializationValue(value, cs); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

INNER_SERIALIZATION_MAP_FUN(std::map)

#define INNER_SERIALIZATION_SET_FUN(Type) \
template<typename T> \
static BOOL InnerSerializationVecotr(Type<T> &t, CSerialization &cs) \
{ \
	DWORD dwSize = t.size(); \
	InnerSerializationValue(dwSize,cs); \
	if (enum_Serialization_Type_Read == cs.GetSerializationType()) \
	{ \
		for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++) \
		{ \
			Type<T>::value_type onevalue; \
			InnerSerializationValue(onevalue,cs); \
			t.insert(onevalue); \
		}\
	} \
	else if(enum_Serialization_Type_Write == cs.GetSerializationType())\
	{ \
		for (Type<T>::iterator itor = t.begin(); itor != t.end(); ++itor)\
		{ \
			T &value= const_cast<T&>(*itor); \
			InnerSerializationValue(value, cs); \
		} \
	} \
	else \
	{ \
		return FALSE; \
	} \
	return TRUE; \
} \

INNER_SERIALIZATION_SET_FUN(std::set)

class CSafeSerialization
{
public:
	CSafeSerialization(CSerialization &s);
	~CSafeSerialization(void);
	struct SerializationHead
	{
		DWORD	dwSectionLen;		//节总长度，包括sizeof(SerializationHead)+dwDataLen+末尾的索引表
		DWORD	dwDataLen;			//数据长度
		SerializationHead():dwSectionLen(0),dwDataLen(0){;}
		BOOL	Serialization(CSerialization &s)
		{
			s.Serialization(dwSectionLen);
			s.Serialization(dwDataLen);
			return TRUE;
		}
	};
	struct SerializationInfo
	{
		DWORD		dwOffset;	//偏移的位置，相对于此节
		std::string strName;	//名字
		SerializationInfo():dwOffset(0){;}
		BOOL	Serialization(CSerialization &s)
		{
			s.Serialization(dwOffset);
			s.Serialization(strName);;
			return TRUE;
		}
	};
public:
	template <typename T>
	BOOL	SSValue(T &t, const char *pstrName)
	{
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
					InnerSerializationValue(t, tempSeri);
					return TRUE;
				}
			}
			return FALSE;
		}
		else
		{
			SerializationInfo Info;
			Info.strName = pstrName;
			Info.dwOffset = m_Serialization.m_dwDataLen - m_dwHeadOffset;
			InnerSerializationValue(t, m_Serialization);
			m_SerializationInfoArray.push_back(Info);
		}
		return TRUE;
	}

	template <typename T>
	BOOL	SSVectorValue(T &t, const char *pstrName)
	{
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
					InnerSerializationVecotr(t, tempSeri);
					return TRUE;
				}
			}
			return FALSE;
		}
		else
		{
			SerializationInfo Info;
			Info.strName = pstrName;
			Info.dwOffset = m_Serialization.m_dwDataLen - m_dwHeadOffset;
			InnerSerializationVecotr(t, m_Serialization);
			m_SerializationInfoArray.push_back(Info);
		}
		return TRUE;
	}
protected:
	CSerialization		&m_Serialization;
	DWORD				m_dwHeadOffset;
protected:
	typedef std::vector<SerializationInfo> SerializationInfoArray;
	SerializationInfoArray		m_SerializationInfoArray;
	SerializationHead			m_SerializationHead;
};

