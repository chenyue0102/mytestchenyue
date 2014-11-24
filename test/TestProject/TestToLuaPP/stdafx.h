// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
//lua 库
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind 库
#include "tolua++.h"
#include "LuaUtil.h"
#include <string>
#include <Windows.h>
#include <vector>

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
		InterlockedIncrement(&g_lCount);
	}
	TestTLV()//构造函数
	{
		printf("TestTLV\n");
		InterlockedIncrement(&g_lCount);
	}
	~TestTLV()
	{
		printf("~TestTLV\n");
		InterlockedDecrement(&g_lCount);
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
	TestTLV& operator++()
	{
		return *this;
	}
	static volatile long g_lCount;
};

template<typename T>
class CMyVector : public std::vector<T>
{
public:
	CMyVector()
	{
		printf("CMyVector\n");
	}
	virtual ~CMyVector()
	{
		printf("~CMyVector\n");
	}
	void Test()
	{
		printf("size=%u\n", size());
	}
	void push_back(const T &value)
	{
		const T *p = &value;
		return __super::push_back(value);
	}
	iterator erase(const_iterator _Where)
	{
		return __super::erase(_Where);
	}
	iterator insert(const_iterator _Where, const T& _Val)
	{
		return __super::insert(_Where, _Val);
	}
	typedef void (CMyVector::*PushBackFunType)(const T &Value);
};