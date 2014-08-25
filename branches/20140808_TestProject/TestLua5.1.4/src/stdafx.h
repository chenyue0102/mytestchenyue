// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#if _MSC_VER >= 1600
#include "targetver.h"
#endif

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息

// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <BaseTyps.h>
#include <oaidl.h>

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

using namespace luabind;
#ifndef _countof
//求出数组元素个数
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
#endif
// TODO: 在此处引用程序需要的其他头文件
