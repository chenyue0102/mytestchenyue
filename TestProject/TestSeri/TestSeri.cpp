// TestSeri.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//���л�����Ϊ�ṹ���Ա������ʽ
	Test<CJsonSerialize>();
	Test<CXmlSerialize>();
	Test<CBinarySerialize>();

	//���л�����Ϊȫ�ֺ�����ʽ
	Test2<CJsonSerialize>();
	Test2<CXmlSerialize>();
	Test2<CBinarySerialize>();
	
	//����ȱ���ֶ�
	Test3<CJsonSerialize>();
	Test3<CXmlSerialize>();
	return 0;
}

