#include "SerializeHelper.h"
#include <cassert>
#if _MSC_VER >= 1700//MS VC++ 11.0
#include <atomic>
#endif
#include "UTF8_GBK_Convert.h"


//SerializeHelper使用存储数据的内部类
class CSerializeHelperData
{
public:
	CSerializeHelperData()
		: m_CodeConvert()
	{
		m_CodeConvert.Open();
	}
public:
	static CSerializeHelperData& GetInstance()
	{
		static CSerializeHelperData HelperData;
		return HelperData;
	}
	CUTF8_GBK_Convert& GetCodeConvert()
	{
		return m_CodeConvert;
	}
	SerializeHelper::EnumStringCode GetStringCode()const
	{
		return m_StringCode;
	}
	void SetStringCode(SerializeHelper::EnumStringCode StringCode)
	{
		m_StringCode = StringCode;
	}
private:
	CUTF8_GBK_Convert m_CodeConvert;
#if _MSC_VER >= 1700//MS VC++ 11.0
	std::atomic<SerializeHelper::EnumStringCode> m_StringCode;
#else
	SerializeHelper::EnumStringCode m_StringCode;
#endif
};

namespace SerializeHelper
{
void test()
{

}

void SetStringCode(EnumStringCode StringCode)
{
	auto &HelpData = CSerializeHelperData::GetInstance();
	HelpData.SetStringCode(StringCode);
}

void Serialize(ISerialize *pSerialization, bool& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, char& Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, unsigned char& Value, const char *pstrName)
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

void Serialize(ISerialize *pSerialization, long double &Value, const char *pstrName)
{
	return pSerialization->Serialization(Value, pstrName);
}

void Serialize(ISerialize *pSerialization, std::string& Value, const char *pstrName)
{
	switch (pSerialization->GetSerializeFormat())
	{
	case EnumSerializeFormatBinary:
		return pSerialization->Serialization(Value, pstrName);
		break;
	case EnumSerializeFormatJson:
	case EnumSerializeFormatXml:
		{
			CSerializeHelperData &HelpData = CSerializeHelperData::GetInstance();
			EnumStringCode StringCode = HelpData.GetStringCode();
			if (EnumStringCodeNone == StringCode
				|| EnumStringCodeGB2312 == StringCode)
			{
				CUTF8_GBK_Convert &CodeConvert = HelpData.GetCodeConvert();
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
						if (CodeConvert.ConvertCode(CHARSET_CONVERT_TYPE_UTF8_TO_GBK, strUTF8.c_str(), strUTF8.size(),
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
						if (CodeConvert.ConvertCode(CHARSET_CONVERT_TYPE_GBK_TO_UTF8,
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
			else if (EnumStringCodeUtf8 == StringCode)
			{
				return pSerialization->Serialization(Value, pstrName);
			}
			else
			{
				assert(false);
				return pSerialization->Serialization(Value, pstrName);
			}
		}
		break;
	default:
		assert(false);
		return pSerialization->Serialization(Value, pstrName);
		break;
	}
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
