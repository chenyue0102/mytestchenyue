// TestLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LuaUtil.h"
#include "boost/lexical_cast.hpp"
#include <Windows.h>
#include <string>

using namespace luabind;
void outputstring(const char *pstrText)
{
	printf(pstrText);
}

class CTest
{
public: 
	CTest():m_nValue(0){;}
	void TestOutput(const char *pstr)
	{
		printf(pstr);
		printf("%d", m_nValue);
	}
	int	m_nValue;
};

extern "C" int luabind_outputstring(lua_State *l)
{
	luabind::module(l)
		[
			luabind::def("outputstring", &outputstring)
		];
	return 0;
}

int getstring(int strValue)
{
	strValue = 99999;
	//strValue = "getstring";
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestLuaFun.lua");

	CLuaVM luaVM;
	
	if( 0 != luaL_dofile(luaVM, szLuaFileName))
	{
		return 1;
	}

	int nfirst = 1, nsecond = 2;
	int nResult = luabind::call_function<int>(luaVM, "testadd", nfirst, nsecond);
	std::string str = luabind::call_function<std::string>(luaVM, "teststring");

	luabind::object obj = luabind::call_function<luabind::object>(luaVM, "testable");
	std::string strValue;
	int nKey = 0;
	for(luabind::iterator i(obj); i != luabind::iterator(); ++i)
	{
		strValue = boost::lexical_cast<std::string>(*i);
		nKey = boost::lexical_cast<int>(i.key());
	}
	luabind_outputstring(luaVM);
	const char *pstrText = "kingmax";
	luabind::call_function<int>(luaVM, "testoutput", pstrText);

	luabind::module(luaVM)
		[
			luabind::def("getstring", &getstring)
		];

	//std::string strValue2;
	std::string strValue2;
	//luabind::call_function<int>(luaVM, "testquote", strValue2);

	CTest t1, t2;
	t1.m_nValue = 100;
	t2.m_nValue = 200;
	module(luaVM)
		[
			class_<CTest>("CTest")
			.def(constructor<>())
			.def("ClassTestOutput", &CTest::TestOutput)
		];
	luabind::call_function<int>(luaVM, "LuaTestOutput");
	/*luabind::module(luaVM)
		[
			luabind::def("ClassTestOutput", &CTest::TestOutput)
		];
	luabind::call_function<int>(luaVM, "LuaTestOutput", &t1, strValue2.c_str());*/
	return 0;
}

