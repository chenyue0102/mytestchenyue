#include "StdAfx.h"
#include "TestSharePointer.h"
#include "luabind/operator.hpp"
#include <luabind/return_reference_to_policy.hpp>

CTestSharePointerVector g_TestSharePointerVector;

using namespace luabind;
void TestSharePointer(lua_State *luaVM)
{
	//luabind::call_function<void>(luaVM, "LuaTestSharedPointer");

	//luabind::call_function<void>(luaVM, "LuaTestChildClass");
	//luabind::call_function<void>(luaVM, "LuaTestChildClass2");
	
	luabind::call_function<void>(luaVM, "LuaTestInitAnotherClass");
	
	for (int nIndex = 0; nIndex < 1000; nIndex++)
	{
		//int nCount = lua_gc(luaVM, LUA_GCCOUNT, 200);
		//int nByte = lua_gc(luaVM, LUA_GCCOUNTB, 200);
		//printf("gcCont=%d %d\n", nCount, nByte);
		luabind::call_function<void>(luaVM, "LuaEnumAnotherClass2");
	}
	printf("LuaEnumAnotherClassbegin======================\n");
	for (int nIndex = 0; nIndex < 10; nIndex++)
	{
		//int nCount = lua_gc(luaVM, LUA_GCCOUNT, 200);
		//int nByte = lua_gc(luaVM, LUA_GCCOUNTB, 200);
		//printf("gcCont=%d %d\n", nCount, nByte);
		luabind::call_function<void>(luaVM, "LuaEnumAnotherClass");
	}
	luabind::call_function<void>(luaVM, "LuaEmptyFun");
	int nSize = g_TestSharePointerVector.size();
	printf("g_TestSharePointerVector size=%d", nSize);
	g_TestSharePointerVector.clear();
}

void RegisterTestSharePointer(lua_State *luaVM)
{
	luabind::module(luaVM)
		[
			class_<CTestSharePointer, CTestSharePointer_wrapper, boost::shared_ptr<CTestSharePointer>>("CTestSharePointer")
			.def(constructor<>())
			.def("Test", &CTestSharePointer::Test, &CTestSharePointer_wrapper::default_Test)
			.def_readwrite("m_nValue", &CTestSharePointer::m_nValue)
		];

	luabind::module(luaVM)
		[
			class_<CTestSharePointerVector::const_iterator >("CTestSharePointerVector_const_iterator")
			.def(constructor<>())
			.def(self == other<CTestSharePointerVector::const_iterator>())		//变量在lua中可以执行比较操作
			.def("increment", (CTestSharePointerVector::const_iterator&(CTestSharePointerVector::const_iterator::*)())&(CTestSharePointerVector::const_iterator::operator++))
			.def("GetValue", &(CTestSharePointerVector::const_iterator::operator *), return_reference_to(_1))
		];

	luabind::module(luaVM)
		[
			class_<CTestSharePointerVector::iterator, CTestSharePointerVector::const_iterator>("CTestSharePointerVector_iterator")
			.def(constructor<>())
			.def(self == other<CTestSharePointerVector::iterator>())		//变量在lua中可以执行比较操作
			.def("increment", (CTestSharePointerVector::iterator&(CTestSharePointerVector::iterator::*)())&(CTestSharePointerVector::iterator::operator++))
			.def("GetValue", &(CTestSharePointerVector::iterator::operator *), return_reference_to(_1))
		];

	luabind::module(luaVM)
		[
			class_<CTestSharePointerVector >("CTestSharePointerVector")
			.def(constructor<>())
			.def("push_back", &CTestSharePointerVector::push_back)
			.def("Begin", (CTestSharePointerVector::iterator(CTestSharePointerVector::*)())&CTestSharePointerVector::begin)
			.def("End", (CTestSharePointerVector::iterator(CTestSharePointerVector::*)())&CTestSharePointerVector::end)
		];

	luabind::globals(luaVM)["g_TestSharePointerVector"] = &g_TestSharePointerVector;
}

CTestSharePointer::CTestSharePointer(void)
	: m_nValue(0)
{
	printf("CTestSharePointer\n");
}

CTestSharePointer::CTestSharePointer(const CTestSharePointer &other)
{
	m_nValue = other.m_nValue;
	printf("Copy CTestSharePointer\n");
}


CTestSharePointer::~CTestSharePointer(void)
{
	printf("~CTestSharePointer\n");
}

void CTestSharePointer::Test()
{
	printf("CTestSharePointer::Test\n");
}

void CTestSharePointerVector::push_back( const boost::shared_ptr<CTestSharePointer> &_Val )
{
	return __super::push_back(_Val);
}

CTestSharePointerVector::iterator CTestSharePointerVector::erase( const_iterator _Where )
{
	return __super::erase(_Where);
}

CTestSharePointerVector::iterator CTestSharePointerVector::insert( const_iterator _Where, const boost::shared_ptr<CTestSharePointer>& _Val )
{
	return __super::insert(_Where, _Val);
}

CTestSharePointer_wrapper::CTestSharePointer_wrapper()
	: CTestSharePointer()
{

}

void CTestSharePointer_wrapper::Test()
{
	call<void>("Test"); 
}

void CTestSharePointer_wrapper::default_Test( CTestSharePointer* ptr )
{
	return ptr->CTestSharePointer::Test();
}
