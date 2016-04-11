#include "stdafx.h"
#include "SerializeHelper.h"
#include <cassert>


#ifdef CONVER_STRING_CODE
//需要将输出的字符串从GB2312转换成UTF-8格式，输入的时候，将UTF-8转换成GB2312
#include "UTF8_GBK_Convert.h"
static CUTF8_GBK_Convert *g_CUTF8_GBK_Convert = nullptr;
#endif

namespace SerializeHelper
{
void test()
{

}

#ifdef CONVER_STRING_CODE
void SetConverStringCode(CUTF8_GBK_Convert &Conver)
{
	g_CUTF8_GBK_Convert = &Conver;
}
#endif

void Serialize(ISerialize *pSerialization, unsigned char& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, bool& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, short& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, unsigned short& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, int &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, unsigned int &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, long &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, unsigned long &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, long long &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, unsigned long long &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, float &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, double &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, std::string& Value, const char *pstrName)
{
#ifdef CONVER_STRING_CODE
	if (nullptr != g_CUTF8_GBK_Convert && g_CUTF8_GBK_Convert->IsOpen())
	{
		if (enum_Serialization_Type_Read == pSerialization->GetSerializationType())
		{
			//将Json中的字符串从UTF8转换成GB2312
			std::string strUTF8;
			pSerialization->Serialization(strUTF8, pstrName);
			if (!strUTF8.empty())
			{
				std::string strGB2312;
				strGB2312.resize(strUTF8.size() * 2, '\0');	//2倍大小认为够了
				unsigned long ulGB2312 = strGB2312.size();
				if (g_CUTF8_GBK_Convert->ConvertCode(CHARSET_CONVERT_TYPE_UTF8_TO_GBK, strUTF8.c_str(), strUTF8.size(),
					&*strGB2312.begin(), ulGB2312) < 0)
				{
					assert(false);
				}
				else
				{
					Value.append(strGB2312.data(), ulGB2312);
				}
			}
		}
		else
		{
			//写入Json之前，将GB2312转换成UTF8
			std::string strUTF8;
			if (!Value.empty())
			{
				std::string strTemp;
				strTemp.resize(Value.size() * 2, '\0');
				unsigned long ulUTF8 = strTemp.size();
				if (g_CUTF8_GBK_Convert->ConvertCode(CHARSET_CONVERT_TYPE_GBK_TO_UTF8,
					Value.c_str(), Value.size(), &*strTemp.begin(), ulUTF8) < 0)
				{
					assert(false);
				}
				else
				{
					strUTF8.append(strTemp.data(), ulUTF8);
				}
			}
			pSerialization->Serialization(strUTF8, pstrName);
		}
	}
	else
	{
		assert(false);
	}
#else
	return pSerialization->Serialization(Value, pstrName);
#endif
}

void Serialize(ISerialize *pSerialization, char *Value, unsigned long ulValueBufferSize, const char *pstrName)
{
	//将char*转换成std::string，再序列化
	assert(ulValueBufferSize > 1);
	if (enum_Serialization_Type_Read == pSerialization->GetSerializationType())
	{
		std::string strTemp;
		Serialize(pSerialization, strTemp, pstrName);
		strncpy(Value, strTemp.c_str(), ulValueBufferSize - 1);
	}
	else
	{
		std::string strTemp(Value);
		Serialize(pSerialization, strTemp, pstrName);
	}
}

}
