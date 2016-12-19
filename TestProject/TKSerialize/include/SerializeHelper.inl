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

void SerializeCharArray(ISerialize *pSerialize, char *Value, unsigned long ulValueBufferSize, const char *pstrName)
{
	//��char*ת����std::string�������л�
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

template<typename T>
void SerializeArray(ISerialize *pSerialize, T Value[], unsigned long ulValueCount, const char *pstrName)
{
	//T ����
	static_assert(!std::is_pointer<T>::value, "Serialize T must be not pointer");
	unsigned long ulCount = ulValueCount;
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialize->BeginSerializeArray(ulCount, pstrName);
	}
	catch (int)
	{
		// Json��Xmlû�нṹ�壬��Ϊ��������
		return;
	}

	assert(ulValueCount == ulCount);
	for (unsigned long ulIndex = 0; ulIndex < ulCount && ulIndex < ulValueCount; ulIndex++)
	{
		pSerialize->BeginSerializeArrayItem(ulIndex, pstrName);
		Serialize(pSerialize, Value[ulIndex], nullptr);
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}
	pSerialize->EndSerializeArray(pstrName);
}

template<typename T>
bool SerializeStruct(ISerialize *pSerialize, T &Value)
{
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	return Value.Serialize(pSerialize);
}

template<typename T>
void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName)
{
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialize->BeginSerializeStruct(pstrName);
	}
	catch (int)
	{
		//û�нṹ�壬��Ϊ������
		return;
	}

	if (!SerializeStruct(pSerialize, Value))
	{
		throw - 1;
	}

	pSerialize->EndSerializeStruct(pstrName);
}

template<typename T>
void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName)
{
	unsigned long ulCount = tArray.size();
	try
	{
		//���Json��û������ṹ�壬�����л��������׳��쳣
		pSerialize->BeginSerializeArray(ulCount, pstrName);
	}
	catch (int)
	{
		// Json��Xmlû�нṹ�壬��Ϊ��������
		return;
	}

	for (unsigned long ulIndex = 0; ulIndex < ulCount; ulIndex++)
	{
		pSerialize->BeginSerializeArrayItem(ulIndex, pstrName);
		if (EnumSerializeIORead == pSerialize->GetSerializeType())
		{
			T t;
			Serialize(pSerialize, t, nullptr);
			tArray.push_back(t);
		}
		else
		{
			Serialize(pSerialize, tArray[ulIndex], nullptr);
		}
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}
	pSerialize->EndSerializeArray(pstrName);
}

}
