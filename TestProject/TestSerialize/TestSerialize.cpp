// TestSerialize.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ISerialize.h"
#include "SerializeImp.h"
#include "Serialize.h"
#include <atlcomcli.h>

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


int _tmain(int argc, _TCHAR* argv[])
{
	Test t;
	t.Keys.push_back(1);
	t.Keys.push_back(2);
	t.strValue = "abc123";
	t.inner.strText = "1";
	CComPtr<ISerialize> pSerialize(new CSerialize);
	pSerialize->SetSerializeType(EnumSerializeTypeWrite);
	t.Serialize(pSerialize);

	Test t2;
	CComPtr<ISerialize> pSerializeRead(new CSerialize);
	pSerializeRead->SetSerializeType(EnumSerializeTypeRead);
	pSerializeRead->SetSerializeReadBuffer(pSerialize->GetWriteBuffer(), pSerialize->GetWriteBufferLength());
	t2.Serialize(pSerializeRead);
	return 0;
}

