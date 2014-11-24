// TestToLuaPP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tolua++.h"
extern int tolua__open (lua_State* tolua_S);
int _tmain(int argc, _TCHAR* argv[])
{
	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestToLua.lua");

	{
 		lua_State* luaVM = NULL;
		luaVM = lua_open();
		luaL_openlibs(luaVM);
		tolua__open(luaVM);
		luaL_dofile(luaVM, szLuaFileName);
	}
	return 0;
}

