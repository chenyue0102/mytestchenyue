#pragma once
#include <vector>
#include <string>
#include "ISerialize.h"

void SerializeImp(bool &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(char &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(unsigned char &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(int &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(unsigned int &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(long &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(unsigned long &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(long long &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(unsigned long long &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(float &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(double &Value, ISerialize *pSerialize)
{
	if (nullptr == pSerialize ||
		!pSerialize->Serialize(Value))
	{
		throw -1;
	}
}

void SerializeImp(std::string &strValue, ISerialize *pSerialize)
{
	if (nullptr == pSerialize)
	{
		throw -1;
	}
	unsigned long ulSize = strValue.size();
	if (!pSerialize->Serialize(ulSize))
	{
		throw -1;
	}
	if (0 != ulSize)
	{
		if (!pSerialize->Serialize(&*strValue.begin(), ulSize))
		{
			throw -1;
		}
	}
}

template<typename T>
void SerializeImp(std::vector<T> &tArray, ISerialize *pSerialize)
{
	if (nullptr == pSerialize)
	{
		throw -1;
	}
	unsigned long ulSize = tArray.size();
	if (!pSerialize->Serialize(ulSize))
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

template<typename T>
void SerializeImp(T &t, ISerialize *pSerialize)
{
	if (!t.Serialize(pSerialize))
	{
		throw -1;
	}
}