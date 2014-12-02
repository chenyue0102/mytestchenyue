#include "stdafx.h"
#include <assert.h>
#include <string.h>
#include "Serialization.h"

// ����Ĭ�ϳ���
#define DEF_BUFFER_LEN	2048

CSerialization::CSerialization()
{
	m_iSerializationType = enum_Serialization_Type_Default;
	m_iBufferCreateType = enum_Buffer_Create_Type_Inside;
	m_pBuffer = (char*)malloc(DEF_BUFFER_LEN);
	memset(m_pBuffer, 0, DEF_BUFFER_LEN);
	m_dwBufferLen = DEF_BUFFER_LEN;
	m_dwDataLen = 0;
}

CSerialization::CSerialization(char* pBuffer, DWORD dwBufferLen)
{
	m_iSerializationType = enum_Serialization_Type_Default;
	m_iBufferCreateType = enum_Buffer_Create_Type_OutSide;
	m_pBuffer = pBuffer;
	m_dwBufferLen = dwBufferLen;
	m_dwDataLen = 0;
}

CSerialization::~CSerialization()
{
	m_iSerializationType = enum_Serialization_Type_Default;
	if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)
	{
		free((void*)m_pBuffer);
	}
	m_pBuffer = NULL;
	m_dwBufferLen = 0;
	m_dwDataLen = 0;
}

// �������л�����
void CSerialization::SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)
{
	m_iSerializationType = iSerializationType;
}

// ��ȡ���л�����
ENUM_SERIALIZATION_TYPE CSerialization::GetSerializationType()
{
	return m_iSerializationType;
}

// ���л��޷����ַ�
void CSerialization::Serialization(char& byValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(unsigned char)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&byValue, m_pBuffer + m_dwDataLen, sizeof(unsigned char));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &byValue, sizeof(unsigned char));
	}

	m_dwDataLen += sizeof(unsigned char);
}

// ���л��޷����ַ�
void CSerialization::Serialization(unsigned char& byValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(unsigned char)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&byValue, m_pBuffer + m_dwDataLen, sizeof(unsigned char));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &byValue, sizeof(unsigned char));
	}

	m_dwDataLen += sizeof(unsigned char);
}

// ���л�bool����
void CSerialization::Serialization(bool& bValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(bool)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&bValue, m_pBuffer + m_dwDataLen, sizeof(bool));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &bValue, sizeof(bool));
	}

	m_dwDataLen += sizeof(bool);
}

// ���л��з��Ŷ�����
void CSerialization::Serialization(short& sValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(short)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&sValue, m_pBuffer + m_dwDataLen, sizeof(short));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &sValue, sizeof(short));
	}

	m_dwDataLen += sizeof(short);
}

// ���л��޷��Ŷ�����
void CSerialization::Serialization(unsigned short& sValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(unsigned short)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&sValue, m_pBuffer + m_dwDataLen, sizeof(unsigned short));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &sValue, sizeof(unsigned short));
	}

	m_dwDataLen += sizeof(unsigned short);
}

// ���л��з�������
void CSerialization::Serialization(int& iValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(int)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&iValue, m_pBuffer + m_dwDataLen, sizeof(int));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &iValue, sizeof(int));
	}

	m_dwDataLen += sizeof(int);
}

// ���л��޷�������
void CSerialization::Serialization(unsigned int& iValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(unsigned int)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&iValue, m_pBuffer + m_dwDataLen, sizeof(unsigned int));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &iValue, sizeof(unsigned int));
	}

	m_dwDataLen += sizeof(unsigned int);
}

// ���л��з��ų�����
void CSerialization::Serialization(long& lValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(long)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&lValue, m_pBuffer + m_dwDataLen, sizeof(long));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &lValue, sizeof(long));
	}

	m_dwDataLen += sizeof(long);
}

// ���л��޷��ų�����
void CSerialization::Serialization(unsigned long& lValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(unsigned long)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&lValue, m_pBuffer + m_dwDataLen, sizeof(unsigned long));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &lValue, sizeof(unsigned long));
	}

	m_dwDataLen += sizeof(unsigned long);
}

// ���л�64λ������
void CSerialization::Serialization(long long& i64Value)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(long long)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&i64Value, m_pBuffer + m_dwDataLen, sizeof(long long));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &i64Value, sizeof(long long));
	}

	m_dwDataLen += sizeof(long long);
}

// ���л�����������
void CSerialization::Serialization(float& fValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(float)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&fValue, m_pBuffer + m_dwDataLen, sizeof(float));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &fValue, sizeof(float));
	}

	m_dwDataLen += sizeof(float);
}

// ���л�˫��������
void CSerialization::Serialization(double& dValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(double)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += m_dwBufferLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&dValue, m_pBuffer + m_dwDataLen, sizeof(double));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &dValue, sizeof(double));
	}

	m_dwDataLen += sizeof(double);
}

// ���л��ַ���
void CSerialization::Serialization(char* pValue, DWORD dwValueLen, DWORD dwDataLen)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (pValue == NULL || dwDataLen > dwValueLen)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + dwDataLen))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			// Ҫ����ĳ���
			DWORD dwLen = m_dwBufferLen * 2;
			if (dwLen < dwDataLen)
				dwLen = dwDataLen;

			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen + dwLen);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += dwLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(pValue, m_pBuffer + m_dwDataLen, dwDataLen);
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, pValue, dwDataLen);
	}

	m_dwDataLen += dwDataLen;
}

// ���л��ַ���
void CSerialization::Serialization(string& strValue)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}
	DWORD dwDataLen = strValue.size();;
	if (m_dwBufferLen < (m_dwDataLen + dwDataLen + sizeof(DWORD)))
	{
		if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// �ⲿ����Ļ���
		{
			throw(-1);
		}
		else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// �ڲ�����Ļ���
		{
			// Ҫ����ĳ���
			DWORD dwLen = m_dwBufferLen * 2;
			if (dwLen < dwDataLen + sizeof(DWORD))
				dwLen = dwDataLen + sizeof(DWORD);

			m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen + dwLen);
			if (m_pBuffer == NULL)
			{
				assert(false);
				throw(-1);
			}
			m_dwBufferLen += dwLen;
		}
	}

	if (m_iSerializationType == enum_Serialization_Type_Read)	// ��ȡ����
	{
		memcpy(&dwDataLen, m_pBuffer + m_dwDataLen, sizeof(DWORD));
		strValue.append(m_pBuffer + m_dwDataLen + sizeof(DWORD), dwDataLen);
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &dwDataLen, sizeof(DWORD));
		memcpy(m_pBuffer + m_dwDataLen + sizeof(DWORD), strValue.c_str(), dwDataLen);
	}

	m_dwDataLen += dwDataLen + sizeof(DWORD);
}

// ȡ������
char* CSerialization::GetData()
{
	return m_pBuffer;
}

// ȡ�����ݳ���
DWORD CSerialization::GetDataLen()
{
	return m_dwDataLen;
}

DWORD CSerialization::GetBufferLen()
{
	return m_dwBufferLen;
}