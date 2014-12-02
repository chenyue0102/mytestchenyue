#include "StdAfx.h"
#include "SafeSerialization.h"


CSafeSerialization::CSafeSerialization(CSerialization &s)
	: m_Serialization(s)
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
		InnerSerializationVecotr(m_SerializationInfoArray, tempSeri);
	}
	else
	{
		SerializationHead Head;
		Head.Serialization(s);
	}
}

CSafeSerialization::~CSafeSerialization(void)
{
	if (enum_Serialization_Type_Read == m_Serialization.GetSerializationType())
	{
		m_Serialization.m_dwDataLen = m_dwHeadOffset + m_SerializationHead.dwSectionLen;
	}
	else
	{
		DWORD dwDataOffset = m_Serialization.m_dwDataLen;
		InnerSerializationVecotr(m_SerializationInfoArray, m_Serialization);
		DWORD dwSectionOffset = m_Serialization.m_dwDataLen;
		m_SerializationHead.dwSectionLen = dwSectionOffset - m_dwHeadOffset;
		m_SerializationHead.dwDataLen = dwDataOffset - m_dwHeadOffset - sizeof(SerializationHead);
		memcpy(m_Serialization.m_pBuffer + m_dwHeadOffset, &m_SerializationHead, sizeof(m_SerializationHead));
	}
}
