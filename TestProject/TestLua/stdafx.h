// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//lua 库
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind 库
#include "luabind\luabind.hpp"
#include "luabind\tag_function.hpp"
#include "LuaUtil.h"

// TODO: 在此处引用程序需要的其他头文件
#include <Windows.h>
struct TestTLV
{
	DWORD	dwID;			// 属性ID
	DWORD	dwType;			// 属性类型
	std::string 	strValue;		// 属性值

	TestTLV(const TestTLV &other)	//拷贝构造
	{
		printf("TestTLV\n");
		dwID = other.dwID;
		dwType = other.dwType;
		strValue = other.strValue;
	}
	TestTLV()//构造函数
	{
		printf("TestTLV\n");
	}
	~TestTLV()
	{
		printf("~TestTLV\n");
	}
	void TestTLV::SetDword(DWORD dwPropertyID, DWORD dwPropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 1;
		strValue.append((char*)&dwPropertyValue, sizeof(DWORD));
	}

	void TestTLV::SetString(DWORD dwPropertyID, const std::string &PropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 2;
		DWORD dwLen = (DWORD)strlen(PropertyValue.c_str()) + 1;
		strValue.append(PropertyValue.c_str(), dwLen);
	}

	void Test()
	{
		printf("TestTlv\n");
	}

	bool operator==(const TestTLV &other)const
	{
		if (dwID == other.dwID
			&& dwType == other.dwType
			&& strValue == other.strValue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};