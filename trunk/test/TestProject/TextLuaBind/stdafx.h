// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//lua ��
extern "C" 
{
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//LuaBind ��
#include "luabind\luabind.hpp"
#include "luabind\tag_function.hpp"
#include "LuaUtil.h"
#include <Windows.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
using namespace luabind;