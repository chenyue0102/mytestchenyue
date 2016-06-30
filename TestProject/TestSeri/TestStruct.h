#pragma once
#include <string>
#include <vector>
#include <codecvt>
#include <assert.h>
#include <Windows.h>
#include "ISerialize.h"

struct ISerialize;
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
	pSerializeWrite->SetSerializationType(enum_Serialization_Type_Write);
	AllTypeWrite.Serialization(pSerializeWrite);

	std::string strBuffer(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());
	std::wstring strWText;
	if (pSerializeWrite->GetSerializeFormat() != EnumSerializeFormatBinary)
	{
		strWText = UTF8ToWChar(strBuffer);
	}

	pSerializeRead->SetSerializationType(enum_Serialization_Type_Read);
	pSerializeRead->SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	AllTypeRead.Serialization(pSerializeRead);

	assert(AllTypeWrite == AllTypeRead);
}

template<typename T>
void DoTest2(ISerialize * pSerializeWrite, ISerialize * pSerializeRead)
{
	T AllTypeWrite;
	AllTypeWrite.init();
	pSerializeWrite->SetSerializationType(enum_Serialization_Type_Write);
	if (!SerializeStruct(pSerializeWrite, AllTypeWrite))
	{
		assert(false);
	}

	std::string strBuffer(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());
	std::wstring strWText;
	if (pSerializeWrite->GetSerializeFormat() != EnumSerializeFormatBinary)
	{
		strWText = UTF8ToWChar(strBuffer);
	}

	pSerializeRead->SetSerializationType(enum_Serialization_Type_Read);
	pSerializeRead->SetData(strBuffer.data(), strBuffer.size());
	T AllTypeRead;
	if (!SerializeStruct(pSerializeRead, AllTypeRead))
	{
		assert(false);
	}

	assert(AllTypeWrite == AllTypeRead);
}

void DoTestMiss(ISerialize * pSerializeWrite, ISerialize * pSerializeRead);

struct TestAllType
{
	bool b = false;
	char c = '\0';
	unsigned char uc = 0;
	short s = 0;
	unsigned short us = 0;
	int i = 0;
	unsigned int ui = 0;
	long l = 0;
	unsigned long ul = 0;
	long long ll = 0;
	unsigned long long ull = 0;
	float f = 0.0f;
	double d = 0.0;
	long double ld = 0.0;
	std::string ss;

	void init();
	BOOL Serialization(ISerialize *pSerialize);
	bool operator==(const TestAllType &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestAllType &Value);

struct TestStruct
{
	int id = 0;
	std::string strValue;

	void init();
	BOOL Serialization(ISerialize *pSerialize);
	bool operator==(const TestStruct &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestStruct &Value);

struct TestArray
{
	int idarray = 0;
	TestStruct ts;
	std::vector<int> vt;
	std::vector<std::vector<std::string>> vvs;
	std::vector<TestStruct> vts;
	std::vector<std::vector<TestStruct>> vvts;

	void init();
	BOOL Serialization(ISerialize *pSerialize);
	bool operator==(const TestArray &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestArray &Value);

struct TestContainer
{
	int idcontainer = 0;
	TestStruct ts;
	TestArray ta;

	void init();
	BOOL Serialization(ISerialize *pSerialize);
	bool operator==(const TestContainer &other)const;
};

bool SerializeStruct(ISerialize *pSerialize, TestContainer &Value);

struct TestMiss
{
	int nID = 0;
	std::string strKey;
	std::string strMiss;
	std::string strValue;

	void init();
	BOOL Serialization(ISerialize *pSerialize);
};

bool SerializeStruct(ISerialize *pSerialize, TestMiss &Value);