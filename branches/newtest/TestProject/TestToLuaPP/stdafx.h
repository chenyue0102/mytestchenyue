// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
//lua ��
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind ��
#include "tolua++.h"
#include "LuaUtil.h"
#include <string>
#include <Windows.h>
#include <vector>

struct TestTLV
{
	DWORD	dwID;			// ����ID
	DWORD	dwType;			// ��������
	std::string 	strValue;		// ����ֵ

	TestTLV(const TestTLV &other)	//��������
	{
		printf("TestTLV\n");
		dwID = other.dwID;
		dwType = other.dwType;
		strValue = other.strValue;
		InterlockedIncrement(&g_lCount);
	}
	TestTLV()//���캯��
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