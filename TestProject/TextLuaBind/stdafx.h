// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//lua 库
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind 库
#include "luabind\luabind.hpp"
#include "luabind\tag_function.hpp"
#include "LuaUtil.h"
#include <Windows.h>

// TODO: 在此处引用程序需要的其他头文件
using namespace luabind;