#include "StdAfx.h"
#include "TestNewCount.h"
#include <assert.h>
#include <luabind/adopt_policy.hpp>		
#include <luabind/copy_policy.hpp>

volatile long CTestNewCount::m_nCount = 0;

CTestNewCount* GetNewObject()	//��������Ȩת�ø�Lua
{
	return new CTestNewCount;
}

CTestNewCount& GetSingleObject()		//����Ȩ��ת��
{
	//���̲߳���ȫ
	static CTestNewCount *p = NULL;
	if (NULL == p)
	{
		p = new CTestNewCount;
	}

	return *p;
}

void RegisterCTestNewCount(lua_State *luaVM)
{
	luabind::module(luaVM, "namespacetest")
	[
		class_<CTestNewCount >("CTestNewCount")
		.def(constructor<>())
		.def("TestCount", &CTestNewCount::TestCount)
		.def("Test", &CTestNewCount::Test),

		def("GetNewObject", &GetNewObject, adopt(result)),		//adopt��ʾ����Ȩת���Lua��Result��ʾ�Ƿ���ֵת�ø�Lua
		def("GetSingleObject", &GetSingleObject, copy(result))		//����Ȩ��ת�ƣ�luaͨ���������캯��������һ������
	];
}

void TestCTestNewCount(lua_State *luaVM)
{
	//����C++New�Ķ���ת���Lua
	//luabind::call_function<void>(luaVM, "LuaTestGetObject");

	//���Կ�����ȡ
	//luabind::call_function<void>(luaVM, "LuaTestCopyObject");
}

CTestNewCount::CTestNewCount(void)
	: m_pstrTestBuffer(NULL)
{
	InterlockedIncrement(&m_nCount);
	m_pstrTestBuffer = new char[1024 * 1024];
}

CTestNewCount::CTestNewCount(const CTestNewCount &other)
	: m_pstrTestBuffer(NULL)
{
	m_pstrTestBuffer = new char[1024 * 1024];
	InterlockedIncrement(&m_nCount);
}

CTestNewCount::~CTestNewCount(void)
{
	InterlockedDecrement(&m_nCount);
	if (NULL != m_pstrTestBuffer)
	{
		delete []m_pstrTestBuffer;
		m_pstrTestBuffer = NULL;
	}
}

void CTestNewCount::TestCount()
{
	assert(0 == m_nCount);
}

void CTestNewCount::Test()
{
	printf("CTestNewCount::Test()\n");
}
