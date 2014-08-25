#pragma once
#include "stdafx.h"
#include <map>
#include <luabind/adopt_policy.hpp>

typedef std::map<DWORD, TestTLV> TestTLVMap;

using namespace luabind;
inline void TestStl(lua_State *luaVM)
{
	luabind::module(luaVM)
	[
		class_<std::pair<const DWORD, TestTLV> >("PairDwordTestTlv")
		.def(constructor<>())
		.def(constructor<const DWORD&, const TestTLV&>())
		.def_readonly("first", &std::pair<const DWORD, TestTLV>::first)
		.def_readwrite("second", &std::pair<const DWORD, TestTLV>::second)
	];
	luabind::module(luaVM)
	[
		class_<TestTLVMap::const_iterator>("mapconst_iterator")
		.def(constructor<>())
		.def(self == other<TestTLVMap::const_iterator>())		//变量在lua中可以执行比较操作
		.def("increment", (TestTLVMap::const_iterator&
						(TestTLVMap::const_iterator::*)())
						&(TestTLVMap::const_iterator::operator++))
		.def("GetValue", &(TestTLVMap::const_iterator::operator *))
	];

	luabind::module(luaVM)
	[
			class_<TestTLVMap::iterator, TestTLVMap::const_iterator>("mapiterator")	//继承于const迭代器，
			.def(constructor<>())
			.def(self == other<TestTLVMap::iterator>())		//变量在lua中可以执行比较操作
			.def("increment", (TestTLVMap::iterator&
			(TestTLVMap::iterator::*)())
			&(TestTLVMap::iterator::operator++))
			.def("GetValue", &(TestTLVMap::iterator::operator *))
	];

	luabind::module(luaVM)
	[
		class_<TestTLVMap::_Pairib>("Pairib")
		.def(constructor<>())
	];

	luabind::module(luaVM)
	[
		class_<TestTLVMap>("TestTLVMap")
		.def(constructor<>())
		.def("Begin", (TestTLVMap::iterator(TestTLVMap::*)())&TestTLVMap::begin)
		.def("End", (TestTLVMap::iterator(TestTLVMap::*)())&TestTLVMap::end)
		.def("Erase", (TestTLVMap::iterator(TestTLVMap::*)(TestTLVMap::const_iterator))&TestTLVMap::erase)
		.def("Insert", (TestTLVMap::_Pairib(TestTLVMap::*)(const std::pair<const DWORD, TestTLV>& _Val))&TestTLVMap::insert)
		.def("Find", (TestTLVMap::iterator (TestTLVMap::*)(const DWORD&))&TestTLVMap::find)
	];

	TestTLVMap map;
	for (int a = 1; a < 10; a++)
	{
		TestTLV t1;
		t1.SetDword(a,a);
		map.insert(std::make_pair(a,t1));
	}
	
	luabind::call_function<void>(luaVM, "LuaTestMap", &map);
	int nSize = map.size();
}