// TestSeri.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "XmlSerialize.h"
#include "JsonSerialize.h"
#include "Serialization.h"
#include "TestStruct.h"
#pragma comment(lib, "lib_json.lib")

template<typename T>
void Test()
{
	{
		T XmlSerializeWrite, XmlSerializeRead;
		DoTest<TestAllType>(&XmlSerializeWrite, &XmlSerializeRead);
	}
	{
		T XmlSerializeWrite, XmlSerializeRead;
		DoTest<TestContainer>(&XmlSerializeWrite, &XmlSerializeRead);
	}
}
template<typename T>
void Test2()
{
	{
		T XmlSerializeWrite, XmlSerializeRead;
		DoTest2<TestAllType>(&XmlSerializeWrite, &XmlSerializeRead);
	}
	{
		T XmlSerializeWrite, XmlSerializeRead;
		DoTest2<TestContainer>(&XmlSerializeWrite, &XmlSerializeRead);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	Test<CXmlSerialize>();
	Test<CJsonSerialize>();
	Test<CSerialization>();

	Test2<CXmlSerialize>();
	Test2<CJsonSerialize>();
	Test2<CSerialization>();
	return 0;
}

