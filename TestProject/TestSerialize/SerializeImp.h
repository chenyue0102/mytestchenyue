#pragma once
#include <vector>
#include <string>
#include "ISerialize.h"

void SerializeImp(ISerialize *pSerialize, bool &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, char &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, unsigned char &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, int &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, unsigned int &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, long &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, unsigned long &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, long long &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, unsigned long long &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, float &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

void SerializeImp(ISerialize *pSerialize, double &Value, const char *psrName)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value, psrName))
	{
		throw -1;
	}
}

template<typename T>
void SerializeImp(ISerialize *pSerialize, T &t, const char *psrName)
{
	ISerializeObject *p = nullptr;
	if (!p->SerializeObject(psrName))
	{
		throw -1;
	}

	if (!t.Serialize(pSerialize))
	{
		throw -1;
	}
}


void SerializeImp(ISerialize *pSerialize, std::string &Value, const char *psrName)
{
	if (nullptr == pSerialize)
	{
		throw -1;
	}
	unsigned long ulSize = Value.size();

	ISerializeObject *p = nullptr;
	if (!p->SerializeMultiObject(psrName, ulSize))
	{
		throw -1;
	}
	if (EnumSerializeTypeRead == pSerialize->GetSerializeType())
	{
		Value.resize(ulSize);
		pSerialize->Serialize(&*Value.begin(), ulSize, psrName);
		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
		{
			T t = T();
			SerializeImp(t, pSerialize);
			tArray.push_back(t);
		}
	}
	else if (EnumSerializeTypeWrite == pSerialize->GetSerializeType())
	{
		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
		{
			SerializeImp(tArray[ulIndex], pSerialize);
		}
	}
	else
	{
		throw -1;
	}
}

template<typename T>
void SerializeImp(ISerialize *pSerialize, std::vector<T> &tArray, const char *psrName)
{
	if (nullptr == pSerialize)
	{
		throw -1;
	}
	unsigned long ulSize = tArray.size();

	ISerializeObject *p = nullptr;
	if (!p->SerializeMultiObject(psrName, ulSize))
	{
		throw -1;
	}

	if (EnumSerializeTypeRead == pSerialize->GetSerializeType())
	{
		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
		{
			T t = T();
			SerializeImp(t, pSerialize);
			tArray.push_back(t);
		}
	}
	else if (EnumSerializeTypeWrite == pSerialize->GetSerializeType())
	{
		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
		{
			SerializeImp(tArray[ulIndex], pSerialize);
		}
	}
	else
	{
		throw -1;
	}
}


//void SerializeImp(std::string &strValue, ISerialize *pSerialize)
//{
//	if (nullptr == pSerialize)
//	{
//		throw -1;
//	}
//	unsigned long ulSize = strValue.size();
//	if (!pSerialize->Serialize(ulSize))
//	{
//		throw -1;
//	}
//	if (0 != ulSize)
//	{
//		if (EnumSerializeTypeRead == pSerialize->GetSerializeType())
//		{
//			strValue.resize(ulSize);
//		}
//		if (!pSerialize->Serialize(&*strValue.begin(), ulSize))
//		{
//			throw -1;
//		}
//	}
//}
//
//template<typename T>
//void SerializeImp(std::vector<T> &tArray, ISerialize *pSerialize)
//{
//	if (nullptr == pSerialize)
//	{
//		throw -1;
//	}
//	unsigned long ulSize = tArray.size();
//	if (!pSerialize->Serialize(ulSize))
//	{
//		throw -1;
//	}
//	if (EnumSerializeTypeRead == pSerialize->GetSerializeType())
//	{
//		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
//		{
//			T t = T();
//			SerializeImp(t, pSerialize);
//			tArray.push_back(t);
//		}
//	}
//	else if (EnumSerializeTypeWrite == pSerialize->GetSerializeType())
//	{
//		for (unsigned long ulIndex = 0; ulIndex < ulSize; ulIndex++)
//		{
//			SerializeImp(tArray[ulIndex], pSerialize);
//		}
//	}
//	else
//	{
//		throw -1;
//	}
//}

