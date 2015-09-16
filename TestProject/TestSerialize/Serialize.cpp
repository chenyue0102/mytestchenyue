#include "Serialize.h"
#include <assert.h>

#define INIT_WRITE_BUFFER_SIZE		8

#define MAX_ONE_OBJECT_SIZE	(1024 * 1024 * 50)
CSerialize::CSerialize(void)
	: m_EnumSerializeType(EnumSerializeTypeNone)
	, m_pReadBuffer(nullptr)
	, m_ulReadBufferLength(0)
	, m_ulReadBufferOffset(0)
	, m_pWriteBuffer(nullptr)
	, m_ulWriteBufferLength(0)
	, m_ulWriteBufferOffset(0)
{
}


CSerialize::~CSerialize(void)
{
	if (nullptr != m_pWriteBuffer)
	{
		free(m_pWriteBuffer);
		m_pWriteBuffer = nullptr;
	}
}

EnumSerializeType CSerialize::GetSerializeType()
{
	return m_EnumSerializeType;
}

bool CSerialize::SetSerializeType(EnumSerializeType SerializeType)
{
	m_EnumSerializeType = SerializeType;
	if (EnumSerializeTypeNone == m_EnumSerializeType)
	{
		assert(false);
		return false;
	}
	else
	{
		if (EnumSerializeTypeWrite == m_EnumSerializeType)
		{
			if (nullptr == m_pWriteBuffer)
			{
				m_ulWriteBufferLength = INIT_WRITE_BUFFER_SIZE;
				m_pWriteBuffer = malloc(m_ulWriteBufferLength);
			}
			m_ulWriteBufferOffset = 0;
		}
		return true;
	}
}

bool CSerialize::SetSerializeReadBuffer(const void *pBuffer, unsigned long ulBufferLength)
{
	if (0 == pBuffer || 0 == ulBufferLength)
	{
		assert(false);
		return false;
	}
	m_pReadBuffer = pBuffer;
	m_ulReadBufferLength = ulBufferLength;
	m_ulReadBufferOffset = 0;
	return true;
}

const void * CSerialize::GetWriteBuffer()
{
	assert(EnumSerializeTypeWrite == m_EnumSerializeType);
	return m_pWriteBuffer;
}

unsigned long CSerialize::GetWriteBufferLength()
{
	assert(EnumSerializeTypeWrite == m_EnumSerializeType);
	return m_ulWriteBufferOffset;
}

bool CSerialize::Serialize(bool &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(char &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(unsigned char &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(short &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(unsigned short &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(int &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(unsigned int &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(long &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(unsigned long &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(long long &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(unsigned long long &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(float &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(double &Value)
{
	return Serialize(&Value, sizeof(Value));
}

bool CSerialize::Serialize(void *pBuffer, unsigned long ulBufferLen)
{
	bool bRes = false;

	do 
	{
		if (nullptr == pBuffer)
		{
			assert(false);
			break;
		}
		if (EnumSerializeTypeRead == m_EnumSerializeType)
		{
			bRes = SerializeRead(pBuffer, ulBufferLen);
		}
		else if (EnumSerializeTypeWrite == m_EnumSerializeType)
		{
			bRes = SerializeWrite(pBuffer, ulBufferLen);
		}
		else
		{
			assert(false);
			break;
		}
	} while (false);
	
	return bRes;
}

bool CSerialize::SerializeRead(void *pBuffer, unsigned long ulBufferLen)
{
	bool bRes = false;

	do 
	{
		if (nullptr == pBuffer)
		{
			assert(false);
			break;
		}
		if (nullptr == m_pReadBuffer)
		{
			assert(false);
			break;
		}
		if (m_ulReadBufferOffset + ulBufferLen > m_ulReadBufferLength)
		{
			assert(false);
			break;
		}
		memcpy(pBuffer, reinterpret_cast<const char*>(m_pReadBuffer) + m_ulReadBufferOffset, ulBufferLen);
		m_ulReadBufferOffset += ulBufferLen;
		bRes = true;
	} while (false);

	return bRes;
}

bool CSerialize::SerializeWrite(const void *pBuffer, unsigned long ulBufferLen)
{
	bool bRes = false;

	do 
	{
		if (nullptr == pBuffer)
		{
			assert(false);
			break;
		}
		if (nullptr == m_pWriteBuffer)
		{
			assert(false);
			break;
		}
		if (ulBufferLen > MAX_ONE_OBJECT_SIZE)
		{
			assert(false);
			break;
		}
		if (m_ulWriteBufferOffset + ulBufferLen > m_ulWriteBufferLength)
		{
			unsigned long ulNeedAllocLength = m_ulWriteBufferOffset + ulBufferLen;
			while (m_ulWriteBufferLength < ulNeedAllocLength)
			{
				m_ulWriteBufferLength *= 2;
			}
			m_pWriteBuffer = realloc(m_pWriteBuffer, m_ulWriteBufferLength);
		}
		memcpy(reinterpret_cast<char*>(m_pWriteBuffer) + m_ulWriteBufferOffset, pBuffer, ulBufferLen);
		m_ulWriteBufferOffset += ulBufferLen;
		bRes = true;
	} while (false);

	return bRes;
}
