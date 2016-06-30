// TestSeri.cpp : �������̨Ӧ�ó������ڵ㡣
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
int _tmain(int argc, _TCHAR* argv[])
{
	Test<CXmlSerialize>();
	Test<CJsonSerialize>();
	Test<CSerialization>();
	return 0;
}

