#include "StdAfx.h"
#include "XmlSerialization.h"


CXmlSerialization::CXmlSerialization(CSerialization &s, const char *pstrName)
	: m_Serialization(s)
	, m_strObjectName(pstrName)
	, m_dwHeadOffset(s.m_dwDataLen)
{
	if (enum_Serialization_Type_Read == s.GetSerializationType())
	{
		//构造索引表
		char *pData = s.m_pBuffer + m_dwHeadOffset;
		memcpy(&m_SerializationHead, pData, sizeof(m_SerializationHead));
		char *pSerializationInfo = pData + sizeof(m_SerializationHead) + m_SerializationHead.dwDataLen;
		CSerialization tempSeri(pSerializationInfo, m_SerializationHead.dwSectionLen - sizeof(m_SerializationHead) - m_SerializationHead.dwDataLen);
		tempSeri.SetSerializationType(enum_Serialization_Type_Read);
		DWORD dwType = XmlFieldTypeNone, dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;;
		XmlInnerSerializationVecotr(m_SerializationInfoArray, tempSeri, dwType, dwChildType, dwChildType2);
	}
	else
	{
		XmlSerializationHead Head;
		Head.Serialization(s);
	}
}


CXmlSerialization::~CXmlSerialization(void)
{
	if (enum_Serialization_Type_Read == m_Serialization.GetSerializationType())
	{
		m_Serialization.m_dwDataLen = m_dwHeadOffset + m_SerializationHead.dwSectionLen;
	}
	else
	{
		DWORD dwDataOffset = m_Serialization.m_dwDataLen;
		DWORD dwType = XmlFieldTypeNone, dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;;
		XmlInnerSerializationVecotr(m_SerializationInfoArray, m_Serialization, dwType, dwChildType, dwChildType2);
		DWORD dwSectionOffset = m_Serialization.m_dwDataLen;
		m_SerializationHead.dwSectionLen = dwSectionOffset - m_dwHeadOffset;
		m_SerializationHead.dwDataLen = dwDataOffset - m_dwHeadOffset - sizeof(m_SerializationHead);
		memcpy(m_Serialization.m_pBuffer + m_dwHeadOffset, &m_SerializationHead, sizeof(m_SerializationHead));
	}
}
