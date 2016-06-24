// TestSeri.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ISerialize.h"
#include "SerializeHelper.h"
#include "JsonSerialize.h"
#include "Serialization.h"
#include <type_traits>
#include <cassert>
#include "UTF8_GBK_Convert.h"
#pragma comment(lib, "lib_json.lib")

void TestFunc();
using namespace SerializeHelper;
struct Tlv
{
	int ID;
	std::string strValue;

	Tlv()
	{
		ID = 0;
	}
	void init()
	{
		ID = 9999;
		strValue = "hello world";
	}
	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			Serialize(pSerialize, ID, "ID");
			Serialize(pSerialize, strValue, "strValue");
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};

bool SerializeStruct(ISerialize *pSerialize, Tlv &Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(ID);
		SERIALIZE_STRUCT_VALUE(strValue);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}

struct UserInfo
{
	int UserID;
	std::string strValue;
	Tlv t;
	std::vector<Tlv> TlvArray;
	std::vector<int> ArrayInt;
	std::vector<std::vector<int>> ArrayArrayInt;

	UserInfo()
	{
		
	}
	void init()
	{
		UserID = 123456;
		unsigned char szTemp[] = { 'a',0x00,'b',0xFF };
		strValue.append((char*)szTemp, _countof(szTemp));
		t.init();

		Tlv t1;
		TlvArray.push_back(t1);

		t1.ID = 8888;
		t1.strValue = "king king";
		TlvArray.push_back(t1);

		ArrayInt.push_back(1);
		ArrayInt.push_back(2);
		ArrayInt.push_back(3);

		for (int a = 1; a < 5; a++)
		{
			std::vector<int> vt;
			for (int b = 1; b < a; b++)
			{
				vt.push_back(b);
			}
			ArrayArrayInt.push_back(vt);
		}
	}

	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			SERIALIZE_VALUE(UserID);
			SERIALIZE_VALUE(strValue);
			SERIALIZE_VALUE(t);
			SERIALIZE_VALUE(TlvArray);
			SERIALIZE_VALUE(ArrayInt);
			SERIALIZE_VALUE(ArrayArrayInt);
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};

bool SerializeStruct(ISerialize *pSerialize, UserInfo &Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(UserID);
		SERIALIZE_STRUCT_VALUE(strValue);
		SERIALIZE_STRUCT_VALUE(t);
		SERIALIZE_STRUCT_VALUE(TlvArray);
		SERIALIZE_STRUCT_VALUE(ArrayInt);
		SERIALIZE_STRUCT_VALUE(ArrayArrayInt);
	}
	catch (...)
	{
		assert(false);
		return false;
	}
	return true;
}


void TestFunc()
{
	UserInfo t;
	CJsonSerialize js;
	js.SetSerializationType(enum_Serialization_Type_Write);
	t.init();
	SerializeStruct(&js, t);
	std::string str(js.GetData(), js.GetDataLen());
	printf(str.c_str());

	UserInfo t2;
	CJsonSerialize jsRead;
	jsRead.SetData(str.data(), str.size());
	jsRead.SetSerializationType(enum_Serialization_Type_Read);
	SerializeStruct(&jsRead, t2);
}

struct TestRead
{
	int readid;
	std::string readvalue;

	Tlv t;
	std::vector<int> vt;
	std::vector<std::vector<int>> vvt;

	std::vector<Tlv> tArray;

	std::vector<std::vector<Tlv>> tArrayArray;
	std::vector<std::vector<Tlv>> tArrayArrayEmpty;
	char szKey[128];

	TestRead()
	{
		memset(szKey, 0, sizeof(szKey));
	}
	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			SERIALIZE_VALUE(readid);
			SERIALIZE_VALUE(readvalue);
			SERIALIZE_VALUE(vt);
			SERIALIZE_VALUE(vvt);
			SERIALIZE_VALUE(t);
			SERIALIZE_VALUE(tArrayArray);
			SERIALIZE_VALUE(tArrayArrayEmpty);
			SERIALIZE_VALUE(tArray);
			SERIALIZE_CHAR(szKey);
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};

static char *g_test1 = R"({"szKey":"mykey myworld","tArrayArrayEmpty":[],"tArrayArray":[[{"ID":1,"strValue":"111"},{"ID":2,"strValue":"222"}],[{"ID":333,"strValue":"333"}],[]],"tArray":[{"ID":333,"strValue":"test king"},{"ID":444,"strValue":"raw string"}],"vt":[1,2,3,4,5],"vvt":[[],[1],[1,2],[1,2,3]],"readid":123456,"readvalue":"hello world","t":{"ID":5555,"strValue":"king max"}})";

struct DoTest
{
	DoTest()
	{
		{
			TestRead r;
			CJsonSerialize js;
			js.SetSerializationType(enum_Serialization_Type_Read);
			js.SetData(g_test1, strlen(g_test1));
			r.Serialization(&js);

			CJsonSerialize jsw;
			jsw.SetSerializationType(enum_Serialization_Type_Write);
			r.Serialization(&jsw);

			std::string str(jsw.GetData(), jsw.GetDataLen());

			CJsonSerialize jsr;
			jsr.SetSerializationType(enum_Serialization_Type_Read);
			jsr.SetData(str.data(), str.size());

			TestRead comp1;
			comp1.Serialization(&jsr);

			CSerialization s1;
			s1.SetSerializationType(enum_Serialization_Type_Write);
			comp1.Serialization(&s1);

			TestRead comp2;
			CSerialization s2;
			s2.SetData(s1.GetData(), s1.GetDataLen());
			s2.SetSerializationType(enum_Serialization_Type_Read);
			comp2.Serialization(&s2);
		}
		Tlv t;
		CJsonSerialize js;
		js.SetSerializationType(enum_Serialization_Type_Write);
		//t.Serialization(&js);
		UserInfo u;
		u.Serialization(&js);

		Json::FastWriter w;
		//std::string strValue = w.write(*js.m_pRootValue);


	}
};

struct TestType
{
	bool b;
	unsigned char uc;
	short		s;
	unsigned short us;
	int i;
	unsigned ui;
	long l;
	unsigned ul;
	long long ll;
	unsigned long long ull;
	float f;
	double d;
	std::string str;
	char szKey[128];

	//std::vector<int*> pt;
	TestType()
	{
		memset(szKey, 0, sizeof(szKey));
	}
	void init()
	{
		b = true;
		uc = 128;
		s = 30000;
		us = 65000;
		i = -12345678;
		ui = 87654321;
		l = -8888888;
		ul = 8888888;
		ll = -1234567890123456789LL;
		ull = 9876543210987654321ULL;
		f = 98765.43f;
		d = 123456789.123;
		str = "test type，中文";
		strcpy(szKey, "mykey my world,字符");
	}
	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			Serialize(pSerialize, b, "b");
			Serialize(pSerialize, uc, "uc");
			Serialize(pSerialize, s, "s");
			Serialize(pSerialize, us, "us");
			Serialize(pSerialize, i, "i");
			Serialize(pSerialize, ui, "ui");
			Serialize(pSerialize, l, "l");
			Serialize(pSerialize, ul, "ul");
			Serialize(pSerialize, ll, "ll");
			Serialize(pSerialize, ull, "ull");
			Serialize(pSerialize, f, "f");
			Serialize(pSerialize, d, "d");
			Serialize(pSerialize, str, "str");
			//Serialize(pSerialize, pt, "pt");
			Serialize(pSerialize, szKey, _countof(szKey), "szKey");
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};
class a {};
struct b {};

struct TestEmpty
{
	int ID;
	std::string strValue;
	Tlv tlv;
	std::vector<int> v;
	std::vector<std::vector<Tlv>> vv;

	BOOL Serialization(ISerialize *pSerialize)
	{
		try
		{
			SERIALIZE_VALUE(tlv);
			SERIALIZE_VALUE(ID);
			SERIALIZE_VALUE(strValue);
			SERIALIZE_VALUE(vv);
			SERIALIZE_VALUE(v);
		}
		catch (...)
		{
			return FALSE;
		}
		return TRUE;
	}
};

char *g_ptext = R"({"ID":1,"vv":[]})";

struct TestDelete
{
	TestDelete()
	{

	}
	~TestDelete()
	{
		printf("");
	}
};

struct TestDelete2
{
	TestDelete2()
	{

	}
	virtual ~TestDelete2()
	{
		printf("");
	}
	void deletethis()
	{
		delete this;
	}
};

struct TestKK
	: public TestDelete
	, public TestDelete2
{
	TestKK()
	{

	}
	virtual ~TestKK()
	{
		printf("");
	}
};

struct Test
{
	Test()
	{

	}
	Test(const std::string &s)
	{
		printf("");
	}
	void init(int a)
	{

	}
};

template<typename T, typename C, void (T::*compFun)(C) = nullptr>
class CTestTemplate
	: public T
{
public:
	using T::T;

	void DoTest(int a)
	{
		(m_p->*compFun)(a);
		/*if (nullptr != compFun)
		{
			compFun(a);
		}*/
	}
	T *m_p;
};

class CA
{
public:
	CA(int)
	{
		printf("");
	}
	CA(double)
	{
		printf("");
	}
};

template<typename T>
class CB
	: public T
{
public:
	template<typename T1>
	CB(T1 &&v)
		: T(v)
	{
		printf("");
	}
public:
	//typename T c;
	//using T::T;
	//using sometype::sometype;
};

int _tmain(int argc, _TCHAR* argv[])
{
	CUTF8_GBK_Convert c;
	c.Open();
	SerializeHelper::SetConverStringCode(c);


	TestFunc();
	CB<CA> cccb(1), cb2(1.1);
	//Test tttx;
	CTestTemplate<Test, int
			//, &Test::init
	> f("a");
	f.DoTest(1);

	TestDelete2 *pkk = new TestKK;
	delete pkk;
	
	if (0)
	{
		TestEmpty t;
		CJsonSerialize js;
		js.SetData(g_ptext, strlen(g_ptext));
		js.SetSerializationType(enum_Serialization_Type_Read);
		t.Serialization(&js);

	}
	
	static_assert(std::is_class<b>::value, "error");
	
	
	//DoTest d;
	{
		TestType t;
		t.init();
		CJsonSerialize js;
		js.SetSerializationType(enum_Serialization_Type_Write);
		t.Serialization(&js);
		std::string str(js.GetData(), js.GetDataLen());
		char pu8[] = u8"你好啊";

		TestType t2;
		CJsonSerialize jsread;
		jsread.SetData(str.data(), str.size());
		jsread.SetSerializationType(enum_Serialization_Type_Read);
		t2.Serialization(&jsread);

		CSerialization s;
		s.SetSerializationType(enum_Serialization_Type_Write);
		t2.Serialization(&s);

		std::string strBuffer(s.GetData(), s.GetDataLen());

		TestType t3;
		CSerialization s2;// (strBuffer.data(), strBuffer.size())
		s2.SetSerializationType(enum_Serialization_Type_Read);
		s2.SetData(strBuffer.data(), strBuffer.size());
		t3.Serialization(&s2);
	}
	CJsonSerialize js;
	js.SetSerializationType(enum_Serialization_Type_Write);
	Tlv t;
	t.init();
	t.Serialization(&js);
	std::string str(js.GetData(), js.GetDataLen());

	{
		CJsonSerialize js2;
		js2.SetData(str.data(), str.size());
		js2.SetSerializationType(enum_Serialization_Type_Read);
		Tlv t2;
		t2.Serialization(&js2);
	}
	CSerialization s;
	return 0;
}

