// TestSerialize.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EnumSerialize.h"
#include "InterfaceSerialize.h"
#include "TKSerialize.h"
#include <memory>
#include <sstream>
#include "TestStruct.h"

using namespace SerializeExport;
void Test(EnumSerializeFormat SerializeFormat)
{
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest<TestAllType>(pSerializeWrite.get(), pSerializeRead.get());
	}
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest<TestContainer>(pSerializeWrite.get(), pSerializeRead.get());
	}
}

void Test2(EnumSerializeFormat SerializeFormat)
{
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest2<TestAllType>(pSerializeWrite.get(), pSerializeRead.get());
	}
	{
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
		DoTest2<TestContainer>(pSerializeWrite.get(), pSerializeRead.get());
	}
}

void Test3(EnumSerializeFormat SerializeFormat)
{
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeWrite(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
	std::unique_ptr<ISerialize, decltype(&DestroySerializeInterface)> pSerializeRead(CreateSerializeInterface(SerializeFormat), &DestroySerializeInterface);
	DoTestMiss(pSerializeWrite.get(), pSerializeRead.get());
}
int _tmain(int argc, _TCHAR* argv[])
{
	{
		//序列化函数为结构体成员函数形式
		Test(EnumSerializeFormatJson);
		Test(EnumSerializeFormatXml);
		Test(EnumSerializeFormatBinary);

		//序列化函数为全局函数形式
		Test2(EnumSerializeFormatJson);
		Test2(EnumSerializeFormatXml);
		Test2(EnumSerializeFormatBinary);

		//测试缺少字段
		Test3(EnumSerializeFormatJson);
		Test3(EnumSerializeFormatXml);
	}
	DWORD dwTickCount = GetTickCount();
	int nCount = 10000;
	for (int a = 0; a < 10000; a ++)
	{
		//序列化函数为结构体成员函数形式
		Test(EnumSerializeFormatBinary);
	}
	{
		std::stringstream ss;
		ss << "Binary " << GetTickCount() - dwTickCount << std::endl;
		printf(ss.str().c_str());
	}
	

	dwTickCount = GetTickCount();
	for (int a = 0; a < 10000; a ++)
	{
		//序列化函数为结构体成员函数形式
		Test(EnumSerializeFormatJson);
	}

	{
		std::stringstream ss;
		ss << "Json " << GetTickCount() - dwTickCount << std::endl;
		printf(ss.str().c_str());
	}

	dwTickCount = GetTickCount();
	for (int a = 0; a < 10000; a ++)
	{
		//序列化函数为结构体成员函数形式
		Test(EnumSerializeFormatXml);
	}
	{
		std::stringstream ss;
		ss << "Xml " << GetTickCount() - dwTickCount << std::endl;
		printf(ss.str().c_str());
	}
	return 0;
}

