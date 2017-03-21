#include <assert.h>
#include <string.h>
#include "BinarySerialize.h"
#include "SerializeString.h"

// 缓存默认长度
#define DEF_BUFFER_LEN	2048

//最大的string长度
#define MAX_STRING_LENGTH	(1024 * 1024 * 10)

CBinarySerialize::CBinarySerialize()
{
	m_iSerializeType = EnumSerializeIONone;
	m_iBufferCreateType = enum_Buffer_Create_Type_Inside;
	m_pBuffer = (char*)malloc(DEF_BUFFER_LEN);
	memset(m_pBuffer, 0, DEF_BUFFER_LEN);
	m_dwBufferLen = DEF_BUFFER_LEN;
	m_dwDataLen = 0;
	m_SerializeStringCode = EnumSerializeStringCodeNone;
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

// 设置序列化类型
bool CBinarySerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
	return true;
}

// 获取序列化类型
EnumSerializeIO CBinarySerialize::GetSerializeType()
{
	return m_iSerializeType;
}

EnumSerializeFormat CBinarySerialize::GetSerializeFormat()
{
	return EnumSerializeFormatBinary;
}

bool CBinarySerialize::SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)
{
	m_SerializeStringCode = SerializeStringCode;
	return true;
}

EnumSerializeStringCode CBinarySerialize::GetSerializeStringCode()
{
	return m_SerializeStringCode;
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

// 序列化bool类型
bool CBinarySerialize::Serialize(bool& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化无符号字符
bool CBinarySerialize::Serialize(char& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化无符号字符
bool CBinarySerialize::Serialize(unsigned char& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化有符号短整型
bool CBinarySerialize::Serialize(short& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化无符号短整型
bool CBinarySerialize::Serialize(unsigned short& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化有符号整型
bool CBinarySerialize::Serialize(int& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化无符号整型
bool CBinarySerialize::Serialize(unsigned int& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化有符号长整型
bool CBinarySerialize::Serialize(long& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化无符号长整型
bool CBinarySerialize::Serialize(unsigned long& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化64位长整型
bool CBinarySerialize::Serialize(long long& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化U64位长整型
bool CBinarySerialize::Serialize(unsigned long long& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化单精度类型
bool CBinarySerialize::Serialize(float& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化双精度类型
bool CBinarySerialize::Serialize(double& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化双精度类型
bool CBinarySerialize::Serialize(long double& Value, const char *)
{
	return InnerSerialize(Value);
}

// 序列化字符串
bool CBinarySerialize::Serialize(CSerializeString& strValue, const char *)
{
	bool bRes = false;

	do 
	{
		if (m_pBuffer == NULL || m_dwBufferLen == 0)
		{
			assert(false);
			break;
		}

		suint32 dwDataLen = static_cast<suint32>(strValue.size());
		if (!InnerSerialize(dwDataLen))
		{
			assert(false);
			break;
		}

		if (dwDataLen > MAX_STRING_LENGTH)
		{
			assert(false);
			break;
		}

		if (m_dwBufferLen < (m_dwDataLen + dwDataLen))
		{
			if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// 外部分配的缓存
			{
				assert(false);
				break;
			}
			else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// 内部分配的缓存
			{
				// 要扩充的长度
				suint32 dwLen = m_dwBufferLen * 2;
				if (dwLen < dwDataLen)
					dwLen = dwDataLen;

				m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen + dwLen);
				if (m_pBuffer == NULL)
				{
					assert(false);
					break;
				}
				m_dwBufferLen += dwLen;
			}
		}

		if (m_iSerializeType == EnumSerializeIORead)	// 读取数据
		{
			strValue.append(m_pBuffer + m_dwDataLen, dwDataLen);
		}
		else if (m_iSerializeType == EnumSerializeIOWrite)	// 写入数据
		{
			memcpy(m_pBuffer + m_dwDataLen, strValue.c_str(), dwDataLen);
		}

		m_dwDataLen += dwDataLen;
		bRes = true;
	} while (false);

	assert(bRes);
	return bRes;
}

template<typename T>
bool CBinarySerialize::InnerSerialize(T &Value)
{
	bool bRes = false;

	do 
	{
		//T必须是数值类型或者浮点类型，数值类型，包含bool类型
		static_assert(std::is_arithmetic<T>::value, "T must be an integral type or a floating-point type");
		if (m_pBuffer == NULL || m_dwBufferLen == 0)
		{
			assert(false);
			break;
		}

		if (m_dwBufferLen < (m_dwDataLen + sizeof(T)))
		{
			if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// 外部分配的缓存
			{
				assert(false);
				break;
			}
			else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// 内部分配的缓存
			{
				m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
				if (m_pBuffer == NULL)
				{
					assert(false);
					break;
				}
				m_dwBufferLen += m_dwBufferLen;
			}
		}

		if (m_iSerializeType == EnumSerializeIORead)	// 读取数据
		{
			memcpy(&Value, m_pBuffer + m_dwDataLen, sizeof(T));
		}
		else if (m_iSerializeType == EnumSerializeIOWrite)	// 写入数据
		{
			memcpy(m_pBuffer + m_dwDataLen, &Value, sizeof(T));
		}

		m_dwDataLen += sizeof(T);
		bRes = true;
	} while (false);

	assert(bRes);
	return bRes;
}

// 取得数据
const char* CBinarySerialize::GetData()
{
	return m_pBuffer;
}

// 取得数据长度
suint32 CBinarySerialize::GetDataLen()
{
	return m_dwDataLen;
}

bool CBinarySerialize::BeginSerializeStruct(const char *)
{
	return true;
}

bool CBinarySerialize::EndSerializeStruct(const char *)
{
	return true;
}

bool CBinarySerialize::BeginSerializeArray(suint32 & ulCount, const char *)
{
	//写入/读取数组长度
	return Serialize(ulCount, nullptr);
}

bool CBinarySerialize::EndSerializeArray(const char *)
{
	return true;
}

bool CBinarySerialize::BeginSerializeArrayItem(suint32, const char *)
{
	return true;
}

bool CBinarySerialize::EndSerializeArrayItem(suint32, const char *)
{
	return true;
}

bool CBinarySerialize::AssistorSerialize(char *Value, suint32 ulDataLength)
{
	bool bRes = false;

	do 
	{
		if (m_pBuffer == NULL || m_dwBufferLen == 0)
		{
			assert(false);
			break;
		}

		if (m_dwBufferLen < (m_dwDataLen + ulDataLength))
		{
			if (m_iBufferCreateType == enum_Buffer_Create_Type_OutSide)	// 外部分配的缓存
			{
				assert(false);
				break;
			}
			else if (m_iBufferCreateType == enum_Buffer_Create_Type_Inside)	// 内部分配的缓存
			{
				m_pBuffer = (char*)realloc(m_pBuffer, m_dwBufferLen * 2);
				if (m_pBuffer == NULL)
				{
					assert(false);
					break;
				}
				m_dwBufferLen += m_dwBufferLen;
			}
		}

		if (m_iSerializeType == EnumSerializeIORead)	// 读取数据
		{
			memcpy(Value, m_pBuffer + m_dwDataLen, ulDataLength);
		}
		else if (m_iSerializeType == EnumSerializeIOWrite)	// 写入数据
		{
			memcpy(m_pBuffer + m_dwDataLen, Value, ulDataLength);
		}

		m_dwDataLen += ulDataLength;
		bRes = true;
	} while (false);

	assert(bRes);
	return bRes;
}
