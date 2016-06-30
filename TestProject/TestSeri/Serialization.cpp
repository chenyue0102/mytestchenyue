#include <assert.h>
#include <string.h>
#include "Serialization.h"

// ����Ĭ�ϳ���
#define DEF_BUFFER_LEN	2048

//����string����
#define MAX_STRING_LENGTH	(1024 * 1024 * 10)

CSerialization::CSerialization()
{
	m_iSerializationType = enum_Serialization_Type_Default;
	m_iBufferCreateType = enum_Buffer_Create_Type_Inside;
	m_pBuffer = (char*)malloc(DEF_BUFFER_LEN);
	memset(m_pBuffer, 0, DEF_BUFFER_LEN);
	m_dwBufferLen = DEF_BUFFER_LEN;
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

EnumSerializeFormat CSerialization::GetSerializeFormat()
{
	return EnumSerializeFormatBinary;
}

bool CSerialization::SetData(const char *pstrText, unsigned long ulDataLength)
{
	if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)
	{
		free((void*)m_pBuffer);
		m_pBuffer = nullptr;
	}
	m_iBufferCreateType = enum_Buffer_Create_Type_OutSide;
	m_pBuffer = const_cast<char*>(pstrText);
	m_dwBufferLen = ulDataLength;
	m_dwDataLen = 0;
	return true;
}

// ���л�bool����
void CSerialization::Serialization(bool& bValue, const char *)
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

// ���л��޷����ַ�
void CSerialization::Serialization(char& cValue, const char *)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(char)))
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
		memcpy(&cValue, m_pBuffer + m_dwDataLen, sizeof(char));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &cValue, sizeof(char));
	}

	m_dwDataLen += sizeof(unsigned char);
}

// ���л��޷����ַ�
void CSerialization::Serialization(unsigned char& byValue, const char *)
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

// ���л��з��Ŷ�����
void CSerialization::Serialization(short& sValue, const char *)
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
void CSerialization::Serialization(unsigned short& sValue, const char *)
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
void CSerialization::Serialization(int& iValue, const char *)
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
void CSerialization::Serialization(unsigned int& iValue, const char *)
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
void CSerialization::Serialization(long& lValue, const char *)
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
void CSerialization::Serialization(unsigned long& lValue, const char *)
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
void CSerialization::Serialization(long long& i64Value, const char *)
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

// ���л�U64λ������
void CSerialization::Serialization(unsigned long long& Value, const char *)
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
		memcpy(&Value, m_pBuffer + m_dwDataLen, sizeof(unsigned long long));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &Value, sizeof(unsigned long long));
	}

	m_dwDataLen += sizeof(unsigned long long);
}

// ���л�����������
void CSerialization::Serialization(float& fValue, const char *)
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
void CSerialization::Serialization(double& dValue, const char *)
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

// ���л�˫��������
void CSerialization::Serialization(long double& ldValue, const char *)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	if (m_dwBufferLen < (m_dwDataLen + sizeof(long double)))
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
		memcpy(&ldValue, m_pBuffer + m_dwDataLen, sizeof(long double));
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &ldValue, sizeof(long double));
	}

	m_dwDataLen += sizeof(double);
}

// ���л��ַ���
void CSerialization::Serialization(string& strValue, const char *)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	DWORD dwDataLen = (DWORD)strValue.size();
	Serialization(dwDataLen, nullptr);

	if (dwDataLen > MAX_STRING_LENGTH)
	{
		assert(false);
		throw -1;
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
		strValue.append(m_pBuffer + m_dwDataLen, dwDataLen);
	}
	else if (m_iSerializationType == enum_Serialization_Type_Write)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, strValue.c_str(), dwDataLen);
	}

	m_dwDataLen += dwDataLen;
}

// ȡ������
const char* CSerialization::GetData()
{
	return m_pBuffer;
}

// ȡ�����ݳ���
DWORD CSerialization::GetDataLen()
{
	return m_dwDataLen;
}

void CSerialization::BeginSerlizeStruct(const char *)
{
	return;
}

void CSerialization::EndSerlizeStruct(const char *)
{
	return;
}

void CSerialization::BeginSerlizeArray(unsigned long & ulCount, const char *)
{
	//д��/��ȡ���鳤��
	return Serialization(ulCount, nullptr);
}

void CSerialization::EndSerlizeArray(const char *)
{
	return;
}

void CSerialization::BeginSerlizeArrayItem(unsigned long, const char *)
{
	return;
}

void CSerialization::EndSerlizeArrayItem(unsigned long, const char *)
{
	return;
}
