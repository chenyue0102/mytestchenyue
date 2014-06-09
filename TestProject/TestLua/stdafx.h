// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//lua ��
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind ��
#include "luabind\luabind.hpp"
#include "luabind\tag_function.hpp"
#include "LuaUtil.h"

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <Windows.h>
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
	}
	TestTLV()//���캯��
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