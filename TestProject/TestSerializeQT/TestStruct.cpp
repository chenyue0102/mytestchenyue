#include "TestStruct.h"
#include "SerializeHelper.h"

bool SerializeStruct(ISerialize &pSerialize, TestAllType &Value)
{
	try
	{
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
		{
			//将当前字符编码切换到Gb2312，此段退出的时候，会将编码置回去
			SERIALIZE_SWITCH_CODE(EnumSerializeStringCodeGB2312);
			SERIALIZE_VALUE(strGB2312);
		}

		{
			//将当前字符编码切换到二进制，此段退出的时候，会将编码置回去
			SERIALIZE_SWITCH_CODE(EnumSerializeStringCodeBinary);
			SERIALIZE_VALUE(strBinary);
		}

		SERIALIZE_VALUE(szText);
		SERIALIZE_VALUE(Keys);
#ifdef QT_CORE_LIB
		SERIALIZE_VALUE(strQString);
#endif
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
	//UTF-8与UCS2互转 //如果char16_t编译不过，替换成short ，有些字符转换不成功，如四个龙
	std::wstring_convert<std:: codecvt_utf8<char16_t >, char16_t> utf8_ucs2_cvt;
	char16_t *ucs2 = (char16_t*)L"utf8文本";
	auto  strtemputf8 = utf8_ucs2_cvt.to_bytes(ucs2);
	strUtf8.assign(strtemputf8.data(), strtemputf8.size());

	strGB2312 = "hello,world,你好，世界,~!@#$%^&*()_+|}{\": ? > < , . / ; '`[]-=\\";

	unsigned char szInitBinary[] = { 0x00, 0x01, 0x02, 0x03, 0xff, 0xff};
	strBinary.append(reinterpret_cast<const char*>(szInitBinary), _countof(szInitBinary));
	strBinary.append("你好");
	unsigned char szInitBinary2[] = { 0xff, 0xff, 0xff, 0xfe };
	strBinary.append(reinterpret_cast<const char*>(szInitBinary2), _countof(szInitBinary2));


	strcpy(szText, "hello, world,szText");
	int nBegin = 2000;
	for each(auto &OneKey in Keys)
	{
		OneKey = nBegin++;
	}
#ifdef QT_CORE_LIB
	strQString = QStringLiteral("你好，QT!");
#endif
}

BOOL TestAllType::Serialize(ISerialize &pSerialize)
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
		&& strGB2312 == other.strGB2312
		&& strBinary == other.strBinary
		&& 0 == strcmp(szText, other.szText)
		&& CompareArray(Keys, other.Keys, _countof(Keys))
#ifdef QT_CORE_LIB
		&& strQString == other.strQString
#endif
		);
}

void TestStruct::init()
{
	id = 11;
	strValue = "TestStruct, hello, world";
}

BOOL TestStruct::Serialize(ISerialize & pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize &pSerialize, TestStruct &Value)
{
	try
	{
		SERIALIZE_VALUE(id);
		SERIALIZE_VALUE(strValue);
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
	vt.push_back(1);
	vt.push_back(2);
	vt.push_back(3);
	
	std::vector<std::string> tempvs;
	tempvs.push_back("abc");
	tempvs.push_back("123");
	vvs.push_back(tempvs);

	tempvs.clear();
	vvs.push_back(tempvs);

	tempvs.clear();
	tempvs.push_back("def");
	tempvs.push_back("456");
	tempvs.push_back("789");
	vvs.push_back(tempvs);

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

	vtArray[0].push_back(111);
	vtArray[0].push_back(222);
	vtArray[0].push_back(333);

	vtArray[2].push_back(44);
	vtArray[2].push_back(55);
	vtArray[2].push_back(66);
}

BOOL TestArray::Serialize(ISerialize &pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize & pSerialize, TestArray & Value)
{
	try
	{
		SERIALIZE_VALUE(idarray);
		SERIALIZE_VALUE(ts);
		SERIALIZE_VALUE(vt);
		SERIALIZE_VALUE(vvs);
		SERIALIZE_VALUE(vts);
		SERIALIZE_VALUE(vvts);
		SERIALIZE_VALUE(tsArray);
		SERIALIZE_VALUE(vtArray);
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

BOOL TestContainer::Serialize(ISerialize & pSerialize)
{
	return SerializeStruct(pSerialize, *this);
}

bool SerializeStruct(ISerialize & pSerialize, TestContainer & Value)
{
	try
	{
		SERIALIZE_VALUE(idcontainer);
		SERIALIZE_VALUE(ts);
		SERIALIZE_VALUE(ta);
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
	
	std::string *ptrlist1 = new std::string("aaaaaaa");
	vtKey.AddTail(ptrlist1);
	std::string *ptrlist2= new std::string("bbbbbbbb");
	vtKey.AddTail(ptrlist2);
	std::string *ptrlist3 = new std::string("cccccc");
	vtKey.AddTail(ptrlist3);

	std::string *pstr1 = new std::string("11111");
	vtMiss.push_back(pstr1);
	std::string *pstr2 = new std::string("22222");
	vtMiss.push_back(pstr2);
	//strMiss = "hello,world,miss";
	strValue = "hello,world,value";
}

BOOL TestMiss::Serialize(ISerialize & pSerialize)
{
	try
	{
		SERIALIZE_STRUCT_VALUE(nID);
		SERIALIZE_STRUCT_VALUE(vtKey);
		//SERIALIZE_STRUCT_VALUE(vtMiss);
		SERIALIZE_STRUCT_VALUE(strValue);
	}
	catch (...)
	{
		return FALSE;
	}
	return TRUE;
}

bool SerializeStruct(ISerialize & pSerialize, TestMiss & Value)
{
	try
	{
		SERIALIZE_VALUE(nID);
		SERIALIZE_VALUE(vtKey);
		SERIALIZE_VALUE(vtMiss);
		SERIALIZE_VALUE(strValue);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void DoTestMiss(ISerialize & pSerializeWrite, ISerialize & pSerializeRead)
{
	//二进制不支持缺少字段
	TestMiss MissWrite;
	MissWrite.init();
	pSerializeWrite.SetSerializeType(EnumSerializeIOWrite);
	MissWrite.Serialize(pSerializeWrite);

	std::string strBuffer(pSerializeWrite.GetData(), pSerializeWrite.GetDataLen());
	std::wstring strWText;
	if (pSerializeWrite.GetSerializeFormat() != EnumSerializeFormatBinary)
	{
		strWText = UTF8ToWChar(strBuffer);
	}

	TestMiss MissRead;
	pSerializeRead.SetSerializeType(EnumSerializeIORead);
	pSerializeRead.SetData(strBuffer.data(), strBuffer.size());
	SerializeStruct(pSerializeRead, MissRead);

	assert(MissWrite == MissRead);
}