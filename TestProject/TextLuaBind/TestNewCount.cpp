#include "StdAfx.h"
#include "TestNewCount.h"
#include <assert.h>
#include <luabind/adopt_policy.hpp>		
#include <luabind/copy_policy.hpp>

volatile long CTestNewCount::m_nCount = 0;

CTestNewCount* GetNewObject()	//测试所有权转让给Lua
{
	return new CTestNewCount;
}

CTestNewCount& GetSingleObject()		//所有权不转移
{
	//多线程不安全
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

		def("GetNewObject", &GetNewObject, adopt(result)),		//adopt表示所有权转义给Lua，Result表示是返回值转让给Lua
		def("GetSingleObject", &GetSingleObject, copy(result))		//所有权不转移，lua通过拷贝构造函数，生成一个拷贝
	];
}

void TestCTestNewCount(lua_State *luaVM)
{
	//测试C++New的对象，转义给Lua
	//luabind::call_function<void>(luaVM, "LuaTestGetObject");

	//测试拷贝获取
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
