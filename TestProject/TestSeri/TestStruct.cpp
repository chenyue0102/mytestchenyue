#include "StdAfx.h"
#include "TestStruct.h"
#include "SerializeHelper.h"



template<typename T>
bool operator==(const std::vector<T> &left, const std::vector<T> &right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	for (size_t a = 0; a < left.size(); a++)
	{
		if (!(left[a] == right[a]))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool CompareArray(const T leftArray[], const T rightArray[], size_t stCount)
{
	for (size_t nIndex = 0; nIndex < stCount; ++nIndex)
	{
		if (!(leftArray[nIndex] == rightArray[nIndex]))
		{
			return false;
		}
	}
	return true;
}

bool SerializeStruct(ISerialize *pSerialize, TestAllType &Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(b);
		SERIALIZE_STRUCT_VALUE(c);
		SERIALIZE_STRUCT_VALUE(uc);
		SERIALIZE_STRUCT_VALUE(s);
		SERIALIZE_STRUCT_VALUE(us);
		SERIALIZE_STRUCT_VALUE(i);
		SERIALIZE_STRUCT_VALUE(ui);
		SERIALIZE_STRUCT_VALUE(l);
		SERIALIZE_STRUCT_VALUE(ul);
		SERIALIZE_STRUCT_VALUE(ll);
		SERIALIZE_STRUCT_VALUE(ull);
		SERIALIZE_STRUCT_VALUE(f);
		SERIALIZE_STRUCT_VALUE(d);
		SERIALIZE_STRUCT_VALUE(ld);
		SERIALIZE_STRUCT_VALUE(ss);
		SerializeHelper::Serialize(pSerialize, Value.strBinary, "strBinary", SerializeHelper::EnumStringCodeBinary);
		SERIALIZE_STRUCT_CHAR(szText);
		SERIALIZE_STRUCT_ARRAY(Keys);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void TestAllType::init()
{
	b = true;
	c = 'a';
	uc = 1;
	s = -2;
	us = 2;
	i = -3;
	ui = 3;
	l = -4;
	ul = 4;
	ll = -5;
	ull = 5;
	f = 123.456f;
	d = 456.789;
	ld = 789.123;
	ss = R"(hello,world,你好，世界,~!@#$%^&*()_+|}{": ? > < , . / ; '`[]-=\)";
	char szInitBinary[] = { 0x00, 0x01, 0x02, 0x03};
	strBinary.append(szInitBinary, _countof(szInitBinary));
	strcpy(szText, "hello, world,szText");
	int nBegin = 2000;
	for (auto &OneKey : Keys)
	{
		OneKey = nBegin++;
	}
	
}

BOOL TestAllType::Serialize(ISerialize *pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool TestAllType::operator==(const TestAllType &other)const
{
	return (b == other.b
		&& c == other.c
		&& uc == other.uc
		&& s == other.s
		&& us == other.us
		&& i == other.i
		&& ui == other.ui
		&& l == other.l
		&& ul == other.ul
		&& ll == other.ll
		&& ull == other.ull
		&& fabs(f - other.f) < FLT_MIN
		&& fabs(d - other.d) < FLT_MIN
		&& fabs(ld - other.ld) < FLT_MIN
		&& ss == other.ss
		&& strBinary == other.strBinary
		&& 0 == strcmp(szText, other.szText)
		&& CompareArray(Keys, other.Keys, _countof(Keys))
		);
}

void TestStruct::init()
{
	id = 11;
	strValue = R"(TestStruct，hello, world)";
}

BOOL TestStruct::Serialize(ISerialize * pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize *pSerialize, TestStruct &Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(id);
		SERIALIZE_STRUCT_VALUE(strValue);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TestStruct::operator==(const TestStruct & other) const
{
	return (id == other.id
		&& strValue == other.strValue);
}

void TestArray::init()
{
	idarray = 22;
	ts.init();
	vt = { 1,2,3 };
	vvs = { {"abc", "123"},{},{"def", "456", "789"} };
	TestStruct ts1;
	vts.push_back(ts1);
	ts1.id = 55;
	ts1.strValue = "vts";
	vts.push_back(ts1);

	ts1.id = 66;
	ts1.strValue = "vvts66";
	std::vector<TestStruct> vtsTemp;
	vtsTemp.push_back(ts1);
	ts1.id = 77;
	ts1.strValue = "vvts77";
	vtsTemp.push_back(ts1);

	vvts.push_back(vtsTemp);
	vvts.push_back(std::vector<TestStruct>());

	tsArray[1].id = 6565;
	tsArray[1].strValue = "tsArray1,6565";

	tsArray[2].id = 7878;
	tsArray[2].strValue = "tsArray2,7878";

	vtArray[0] = { 111,222,333 };
	vtArray[2] = { 44,55,66 };
}

BOOL TestArray::Serialize(ISerialize *pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize * pSerialize, TestArray & Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(idarray);
		SERIALIZE_STRUCT_VALUE(ts);
		SERIALIZE_STRUCT_VALUE(vt);
		SERIALIZE_STRUCT_VALUE(vvs);
		SERIALIZE_STRUCT_VALUE(vts);
		SERIALIZE_STRUCT_VALUE(vvts);
		SERIALIZE_STRUCT_ARRAY(tsArray);
		SERIALIZE_STRUCT_ARRAY(vtArray);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TestArray::operator==(const TestArray & other) const
{
	return (idarray == other.idarray
		&& ts == other.ts
		&& vt == other.vt
		&& vvs == other.vvs
		&& vts == other.vts
		&& vvts == other.vvts
		&& CompareArray(tsArray, other.tsArray, _countof(tsArray))
		&& CompareArray(vtArray, other.vtArray, _countof(vtArray))
		);
}

void TestContainer::init()
{
	idcontainer = 7788;
	ts.init();
	ta.init();
}

BOOL TestContainer::Serialize(ISerialize * pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize * pSerialize, TestContainer & Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(idcontainer);
		SERIALIZE_STRUCT_VALUE(ts);
		SERIALIZE_STRUCT_VALUE(ta);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TestContainer::operator==(const TestContainer & other) const
{
	return (idcontainer == other.idcontainer
		&& ts == other.ts
		&& ta == other.ta);
}

void TestMiss::init()
{
	nID = 987321;
	strKey = "hello,world,key";
	strMiss = "hello,world,miss";
	strValue = "hello,world,value";
}

BOOL TestMiss::Serialize(ISerialize * pSerialize)
{
	try
	{
		SERIALIZE_VALUE(nID);
		SERIALIZE_VALUE(strKey);
		//SERIALIZE_VALUE(strMiss);
		SERIALIZE_VALUE(strValue);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

bool SerializeStruct(ISerialize * pSerialize, TestMiss & Value)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(nID);
		SERIALIZE_STRUCT_VALUE(strKey);
		SERIALIZE_STRUCT_VALUE(strMiss);
		SERIALIZE_STRUCT_VALUE(strValue);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void DoTestMiss(ISerialize * pSerializeWrite, ISerialize * pSerializeRead)
{
	//二进制不支持缺少字段
	assert(pSerializeWrite->GetSerializeFormat() != EnumSerializeFormatBinary);
	TestMiss MissWrite;
	MissWrite.init();
	pSerializeWrite->SetSerializeType(EnumSerializeIOWrite);
	MissWrite.Serialize(pSerializeWrite);

	std::string strBuffer(pSerializeWrite->GetData(), pSerializeWrite->GetDataLen());
	std::wstring strWText;
	if (pSerializeWrite->GetSerializeFormat() != EnumSerializeFormatBinary)
	{
		strWText = UTF8ToWChar(strBuffer);
	}

	TestMiss MissRead;
	pSerializeRead->SetSerializeType(EnumSerializeIORead);
	pSerializeRead->SetData(strBuffer.data(), strBuffer.size());
	SerializeStruct(pSerializeRead, MissRead);
}