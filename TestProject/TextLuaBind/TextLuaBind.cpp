// TextLuaBind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestNewCount.h"

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
		
		extern void TestCTestNewCount(lua_State *luaVM);
		TestCTestNewCount(luaVM);
	}
 	CTestNewCount::TestCount();
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
