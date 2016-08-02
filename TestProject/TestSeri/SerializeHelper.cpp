#include "SerializeHelper.h"
#include <cassert>
#include "SerializeString.h"



namespace SerializeHelper
{
void test()
{

}

void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize * pSerialize, CSerializeString & Value, const char * pstrName)
{
	return pSerialize->Serialize(Value, pstrName);
}

void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName)
{
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		CSerializeString strTemp;
		Serialize(pSerialize, strTemp, pstrName);
		Value.assign(strTemp.data(), strTemp.size());
	}
	else
	{
		CSerializeString strTemp(Value.data(), Value.size());
		Serialize(pSerialize, strTemp, pstrName);
	}
}

void Serialize(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName)
{
	//将char*转换成std::string，再序列化
	assert(ulValueBufferSize > 1);
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		CSerializeString strTemp;
		Serialize(pSerialize, strTemp, pstrName);
		strncpy(Value, strTemp.c_str(), ulValueBufferSize - 1);
	}
	else
	{
		CSerializeString strTemp(Value);
		Serialize(pSerialize, strTemp, pstrName);
	}
}

}
