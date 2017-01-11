#pragma once
#include <string>
#include <vector>
#include <codecvt>
#include <assert.h>
#include <Windows.h>
#include "InterfaceSerialize.h"
#include "SerializeHelper.h"

namespace SerializeExport
{
	struct ISerialize;
}
using namespace SerializeExport;



inline std::wstring UTF8ToWChar(const std::string &strUtf8)
{
	std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
	std::wstring strw = utf8_wstr_cvt.from_bytes(strUtf8);
	return strw;
}

template<typename T>
void DoTest(ISerialize * pSerializeWrite, ISerialize * pSerializeRead)
{
	T AllTypeWrite;
	AllTypeWrite.init();
	pSerializeWrite->SetSerializeType(EnumSerializeIOWrite);
	AllTypeWrite.Serialize(pSerializeWrite);

	std::string strBuffer(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());
#ifdef _DEBUG
	std::wstring strWText;
	if (pSerializeWrite->GetSerializeFormat() == EnumSerializeFormatJson
		|| pSerializeWrite->GetSerializeFormat() == EnumSerializeFormatXml)
	{
		strWText = UTF8ToWChar(strBuffer);
	}
#endif

	pSerializeRead->SetSerializeType(EnumSerializeIORead);
	pSerializeRead->SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	AllTypeRead.Serialize(pSerializeRead);

	assert(AllTypeWrite == AllTypeRead);
}

template<typename T>
void DoTest2(ISerialize * pSerializeWrite, ISerialize * pSerializeRead)
{
	T AllTypeWrite;
	AllTypeWrite.init();
	pSerializeWrite->SetSerializeType(EnumSerializeIOWrite);
	if (!SerializeStruct(pSerializeWrite, AllTypeWrite))
	{
		assert(false);
	}

	std::string strBuffer(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());
#ifdef _DEBUG
	std::wstring strWText;
	if (pSerializeWrite->GetSerializeFormat() == EnumSerializeFormatJson)
	{
		strWText = UTF8ToWChar(strBuffer);
	}
#endif

	pSerializeRead->SetSerializeType(EnumSerializeIORead);
	pSerializeRead->SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	if (!SerializeStruct(pSerializeRead, AllTypeRead))
	{
		assert(false);
	}

	assert(AllTypeWrite == AllTypeRead);
}

void DoTestMiss(ISerialize * pSerializeWrite, ISerialize * pSerializeRead);
enum EnumTest
{
	EnumTestNone,
};
struct TestAllType
{
	bool b;
	char c;
	unsigned char uc;
	short s;
	unsigned short us;
	int i;
	unsigned int ui;
	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;
	float f;
	double d;
	long double ld;
	std::string strUtf8;
	std::string strGB2312;
	std::string strBinary;		//存储二进制数据
	char	szText[32];
	int		Keys[4];
	std::vector<int> vt;
	std::vector<int> vtt[3];
	//byte ppp[6];

	TestAllType()
	{
		b = false;
		c = '\0';
		uc = 0;
		s = 0;
		us = 0;
		i = 0;
		ui = 0;
		l = 0;
		l = 0;
		ll = 0;
		ull = 0;
		f = 0.0f;
		d = 0.0;
		ld = 0.0;
		//ss;
		//strBinary;		//存储二进制数据
		memset(szText, 0, sizeof(szText));
		memset(Keys, 0, sizeof(Keys));
	}
	void init();
	BOOL Serialize(ISerialize *pSerialize);
	bool operator==(const TestAllType &other)const;
};

inline bool SerializeStruct(ISerialize *pSerialize, TestAllType &Value)
{
	try
	{
		//SERIALIZE_VALUE(ppp);
		SERIALIZE_VALUE(b);
		SERIALIZE_VALUE(c);
		SERIALIZE_VALUE(uc);
		SERIALIZE_VALUE(s);
		SERIALIZE_VALUE(us);
		SERIALIZE_VALUE(i);
		SERIALIZE_VALUE(ui);
		SERIALIZE_VALUE(l);
		SERIALIZE_VALUE(ul);
		SERIALIZE_VALUE(ll);
		SERIALIZE_VALUE(ull);
		SERIALIZE_VALUE(f);
		SERIALIZE_VALUE(d);
		SERIALIZE_VALUE(ld);
		SERIALIZE_VALUE(strUtf8);

		//序列化二进制数据
		auto OldStringCode = pSerialize->GetSerializeStringCode();

		pSerialize->SetSerializeStringCode(EnumSerializeStringCodeGB2312);
		SERIALIZE_VALUE(strGB2312);
		pSerialize->SetSerializeStringCode(EnumSerializeStringCodeBinary);
		SERIALIZE_VALUE(strBinary);

		pSerialize->SetSerializeStringCode(OldStringCode);

		SERIALIZE_VALUE(szText);
		SERIALIZE_VALUE(Keys);
		SERIALIZE_VALUE(vt);
		SERIALIZE_VALUE(vtt);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

struct TestStruct
{
	int id;
	std::string strValue;

	TestStruct()
	{
		id = 0;
	}
	void init();
	BOOL Serialize(ISerialize *pSerialize);
	bool operator==(const TestStruct &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestStruct &Value);

struct TestArray
{
	int idarray;
	TestStruct ts;
	std::vector<int> vt;
	std::vector<std::vector<std::string>> vvs;
	std::vector<TestStruct> vts;
	std::vector<std::vector<TestStruct>> vvts;
	TestStruct tsArray[3];
	std::vector<int> vtArray[3];

	TestArray()
	{
		idarray = 0;
	}
	void init();
	BOOL Serialize(ISerialize *pSerialize);
	bool operator==(const TestArray &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestArray &Value);

struct TestContainer
{
	int idcontainer;
	TestStruct ts;
	TestArray ta;

	TestContainer()
	{
		idcontainer = 0;
	}
	void init();
	BOOL Serialize(ISerialize *pSerialize);
	bool operator==(const TestContainer &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestContainer &Value);

struct TestMiss
{
	int nID;
	std::string strKey;
	TestContainer tc;
	std::vector<int> vi;
	std::string strValue;

	TestMiss()
	{
		nID = 0;
	}
	void init();
	BOOL Serialize(ISerialize *pSerialize);
};

bool SerializeStruct(ISerialize *pSerialize, TestMiss &Value);