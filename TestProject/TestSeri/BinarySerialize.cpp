#include <assert.h>
#include <string.h>
#include "BinarySerialize.h"

// ����Ĭ�ϳ���
#define DEF_BUFFER_LEN	2048

//����string����
#define MAX_STRING_LENGTH	(1024 * 1024 * 10)

CBinarySerialize::CBinarySerialize()
{
	m_iSerializeType = EnumSerializeIONone;
	m_iBufferCreateType = enum_Buffer_Create_Type_Inside;
	m_pBuffer = (char*)malloc(DEF_BUFFER_LEN);
	memset(m_pBuffer, 0, DEF_BUFFER_LEN);
	m_dwBufferLen = DEF_BUFFER_LEN;
	m_dwDataLen = 0;
}

CBinarySerialize::~CBinarySerialize()
{
	m_iSerializeType = EnumSerializeIONone;
	if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)
	{
		free((void*)m_pBuffer);
	}
	m_pBuffer = NULL;
	m_dwBufferLen = 0;
	m_dwDataLen = 0;
}

// �������л�����
void CBinarySerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
}

// ��ȡ���л�����
EnumSerializeIO CBinarySerialize::GetSerializeType()
{
	return m_iSerializeType;
}

EnumSerializeFormat CBinarySerialize::GetSerializeFormat()
{
	return EnumSerializeFormatBinary;
}

bool CBinarySerialize::SetData(const char *pstrText, unsigned long ulDataLength)
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
void CBinarySerialize::Serialize(bool& bValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&bValue, m_pBuffer + m_dwDataLen, sizeof(bool));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &bValue, sizeof(bool));
	}

	m_dwDataLen += sizeof(bool);
}

// ���л��޷����ַ�
void CBinarySerialize::Serialize(char& cValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&cValue, m_pBuffer + m_dwDataLen, sizeof(char));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &cValue, sizeof(char));
	}

	m_dwDataLen += sizeof(unsigned char);
}

// ���л��޷����ַ�
void CBinarySerialize::Serialize(unsigned char& byValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&byValue, m_pBuffer + m_dwDataLen, sizeof(unsigned char));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &byValue, sizeof(unsigned char));
	}

	m_dwDataLen += sizeof(unsigned char);
}

// ���л��з��Ŷ�����
void CBinarySerialize::Serialize(short& sValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&sValue, m_pBuffer + m_dwDataLen, sizeof(short));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &sValue, sizeof(short));
	}

	m_dwDataLen += sizeof(short);
}

// ���л��޷��Ŷ�����
void CBinarySerialize::Serialize(unsigned short& sValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&sValue, m_pBuffer + m_dwDataLen, sizeof(unsigned short));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &sValue, sizeof(unsigned short));
	}

	m_dwDataLen += sizeof(unsigned short);
}

// ���л��з�������
void CBinarySerialize::Serialize(int& iValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&iValue, m_pBuffer + m_dwDataLen, sizeof(int));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &iValue, sizeof(int));
	}

	m_dwDataLen += sizeof(int);
}

// ���л��޷�������
void CBinarySerialize::Serialize(unsigned int& iValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&iValue, m_pBuffer + m_dwDataLen, sizeof(unsigned int));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &iValue, sizeof(unsigned int));
	}

	m_dwDataLen += sizeof(unsigned int);
}

// ���л��з��ų�����
void CBinarySerialize::Serialize(long& lValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&lValue, m_pBuffer + m_dwDataLen, sizeof(long));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &lValue, sizeof(long));
	}

	m_dwDataLen += sizeof(long);
}

// ���л��޷��ų�����
void CBinarySerialize::Serialize(unsigned long& lValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&lValue, m_pBuffer + m_dwDataLen, sizeof(unsigned long));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &lValue, sizeof(unsigned long));
	}

	m_dwDataLen += sizeof(unsigned long);
}

// ���л�64λ������
void CBinarySerialize::Serialize(long long& i64Value, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&i64Value, m_pBuffer + m_dwDataLen, sizeof(long long));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &i64Value, sizeof(long long));
	}

	m_dwDataLen += sizeof(long long);
}

// ���л�U64λ������
void CBinarySerialize::Serialize(unsigned long long& Value, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&Value, m_pBuffer + m_dwDataLen, sizeof(unsigned long long));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &Value, sizeof(unsigned long long));
	}

	m_dwDataLen += sizeof(unsigned long long);
}

// ���л�����������
void CBinarySerialize::Serialize(float& fValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&fValue, m_pBuffer + m_dwDataLen, sizeof(float));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &fValue, sizeof(float));
	}

	m_dwDataLen += sizeof(float);
}

// ���л�˫��������
void CBinarySerialize::Serialize(double& dValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&dValue, m_pBuffer + m_dwDataLen, sizeof(double));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &dValue, sizeof(double));
	}

	m_dwDataLen += sizeof(double);
}

// ���л�˫��������
void CBinarySerialize::Serialize(long double& ldValue, const char *)
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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		memcpy(&ldValue, m_pBuffer + m_dwDataLen, sizeof(long double));
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, &ldValue, sizeof(long double));
	}

	m_dwDataLen += sizeof(double);
}

// ���л��ַ���
void CBinarySerialize::Serialize(std::string& strValue, const char *)
{
	if (m_pBuffer == NULL || m_dwBufferLen == 0)
	{
		assert(false);
		return;
	}

	DWORD dwDataLen = (DWORD)strValue.size();
	Serialize(dwDataLen, nullptr);

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

	if (m_iSerializeType == EnumSerializeIORead)	// ��ȡ����
	{
		strValue.append(m_pBuffer + m_dwDataLen, dwDataLen);
	}
	else if (m_iSerializeType == EnumSerializeIORead)	// д������
	{
		memcpy(m_pBuffer + m_dwDataLen, strValue.c_str(), dwDataLen);
	}

	m_dwDataLen += dwDataLen;
}

// ȡ������
const char* CBinarySerialize::GetData()
{
	return m_pBuffer;
}

// ȡ�����ݳ���
DWORD CBinarySerialize::GetDataLen()
{
	return m_dwDataLen;
}

void CBinarySerialize::BeginSerializeStruct(const char *)
{
	return;
}

void CBinarySerialize::EndSerializeStruct(const char *)
{
	return;
}

void CBinarySerialize::BeginSerializeArray(unsigned long & ulCount, const char *)
{
	//д��/��ȡ���鳤��
	return Serialize(ulCount, nullptr);
}

void CBinarySerialize::EndSerializeArray(const char *)
{
	return;
}

void CBinarySerialize::BeginSerializeArrayItem(unsigned long, const char *)
{
	return;
}

void CBinarySerialize::EndSerializeArrayItem(unsigned long, const char *)
{
	return;
}
