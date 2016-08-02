// TestSeri.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "XmlSerialize.h"
#include "JsonSerialize.h"
#include "BinarySerialize.h"
#include "TestStruct.h"

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

template<typename T>
void Test3()
{
	T XmlSerializeWrite, XmlSerializeRead;
	DoTestMiss(&XmlSerializeWrite, &XmlSerializeRead);
}
int _tmain(int argc, _TCHAR* argv[])
{
	//序列化函数为结构体成员函数形式
	Test<CJsonSerialize>();
	Test<CXmlSerialize>();
	Test<CBinarySerialize>();

	//序列化函数为全局函数形式
	Test2<CJsonSerialize>();
	Test2<CXmlSerialize>();
	Test2<CBinarySerialize>();
	
	//测试缺少字段
	Test3<CJsonSerialize>();
	Test3<CXmlSerialize>();
	return 0;
}

