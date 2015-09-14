// TestSerialize.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ISerialize.h"
#include "SerializeImp.h"

struct TestInner
{
	std::string strText;

	bool Serialize(ISerialize *pSerialize)
	{
		try
		{
			SerializeImp(strText, pSerialize);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
};

struct Test
{
	bool bValue;
	std::vector<unsigned long> Keys;
	std::string strValue;
	TestInner inner;

	bool Serialize(ISerialize *pSerialize)
	{
		try
		{
			SerializeImp(bValue, pSerialize);
			SerializeImp(Keys, pSerialize);
			SerializeImp(strValue, pSerialize);
			SerializeImp(inner, pSerialize);
		}
		catch(...)
		{
			return false;
		}
		return true;
	}
};

class CSerialize
	: public ISerialize
{
public:
	virtual EnumSerializeType GetSerializeType()
	{
		return EnumSerializeTypeWrite;
	}

	virtual bool Serialize(bool Value)
	{
		return true;
	}

	virtual bool Serialize(unsigned long Value)
	{
		return true;
	}

	virtual bool Serialize(std::string &Value)
	{
		return true;
	}

	virtual bool Serialize(char *pstr, unsigned long ulBufferLen)
	{
		return true;
	}
public:
	EnumSerializeType m_SerializeType;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string strkk;
	Test t;
	t.Keys.push_back(1);
	t.Keys.push_back(2);
	//t.strValue = "abc123";
	t.inner.strText = "1";
	CSerialize aSerialize;
	t.Serialize(&aSerialize);
	return 0;
}

