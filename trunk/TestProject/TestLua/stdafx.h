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
#include "lua\lua.h"
#include "lua\lualib.h"
#include "lua\lauxlib.h"
}
//LuaBind 库
#include "luabind\luabind.hpp"
#include "luabind\tag_function.hpp"
#include "LuaUtil.h"

// TODO: 在此处引用程序需要的其他头文件
