// TextLuaBind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestNewCount.h"
#include "luabind/class_info.hpp"

void LuaErrorCallbackFun(lua_State* e);
void TestOverloadedFun(int nValue);
void TestOverloadedFun(const std::string &strText);

void RegisterAll(lua_State *luaVM)
{
	extern void RegisterCTestNewCount(lua_State *luaVM);
	RegisterCTestNewCount(luaVM);
}
int _tmain(int argc, _TCHAR* argv[])
{
	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestLuaBind.lua");

	{
		CLuaVM luaVM;

		luabind::set_error_callback(&LuaErrorCallbackFun);
		RegisterAll(luaVM);
		module(luaVM)
			[
				class_<class_info>("class_info_data")
				.def_readonly("name", &class_info::name)
				.def_readonly("methods", &class_info::methods)
				.def_readonly("attributes", &class_info::attributes),

				def("class_info", &get_class_info),
				def("class_names", &get_class_names)
			];
		if( 0 != luaL_dofile(luaVM, szLuaFileName))
		{
			return 1;
		}

		//测试hello world
		//luabind::call_function<void>(luaVM, "LuaHelloWorld");

		//测试重载函数
		module(luaVM)
		[
			namespace_("OverloadedFun")
			[
				def("TestOverloadedFun", (void(*)(int))&TestOverloadedFun)
			]
		];
		module(luaVM, "OverloadedFun")
		[
			def("TestOverloadedFun", (void(*)(const std::string &))&TestOverloadedFun)
		];
		//luabind::call_function<void>(luaVM, "LuaTestOverloadedFun");
		lua_gc(luaVM, LUA_GCCOLLECT, 0);		//发起一次完整的垃圾收集循环
		int nCount = lua_gettop(luaVM);

		extern void TestCTestNewCount(lua_State *luaVM);
		TestCTestNewCount(luaVM);
		extern void DestroyGlobalCTestNewCount();
		DestroyGlobalCTestNewCount();

		lua_gc(luaVM, LUA_GCCOLLECT, 0);		//发起一次完整的垃圾收集循环
		int nNewCount = lua_gettop(luaVM);
		printf("gcCont=%d new= %d \n", nCount, nNewCount);
		CTestNewCount::TestCount();
	}
	
	return 0;
}

void LuaErrorCallbackFun(lua_State* e)
{
	const char *pstrError = lua_tostring(e, -1);
	printf(pstrError);
}

void TestOverloadedFun(int nValue)
{
	printf("TestOverloadedFun int %d\n", nValue);
}

void TestOverloadedFun(const std::string &strText)
{
	printf("TestOverloadedFun str %s\n", strText.c_str());
}
