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
	//���л�����Ϊ�ṹ���Ա������ʽ
	Test<CXmlSerialize>();
	Test<CJsonSerialize>();
	Test<CSerialization>();

	//���л�����Ϊȫ�ֺ�����ʽ
	Test2<CXmlSerialize>();
	Test2<CJsonSerialize>();
	Test2<CSerialization>();
	
	//����ȱ���ֶ�
	Test3<CXmlSerialize>();
	Test3<CJsonSerialize>();
	return 0;
}

