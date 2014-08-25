/*
	lua 工具
*/


#pragma once


//lua 虚似机
class CLuaVM
{
public:
	CLuaVM(bool supportPackage=true,
		bool supportTable=true,
		bool supportIo=true,
		bool supportOs=true,
		bool supportString=true,
		bool supportMath=true,
		bool supportDebug=true
		) throw(...)
	{
		//创建 lua 实例
		if( !(m_luaVM = /*lua_open()*/luaL_newstate()) ) throw std::exception("lua_open 失败");

		//打开 lua 库
		lua_State* L = m_luaVM;

#if LUA_VERSION_NUM >= 501 
		luaL_openlibs(L);
#else
		lua_pushcfunction(L, luaopen_base);
		lua_pushstring(L, "");
		lua_call(L, 1, 0);
#define CLUAVM_CLUAVM_CODE_SNIP(libNamePara) \
		{ \
			lua_pushcfunction(L, luaopen_##libNamePara); \
			lua_pushstring(L, #libNamePara); \
			lua_call(L, 1, 0); \
		}

		if(supportPackage) CLUAVM_CLUAVM_CODE_SNIP(package);
		if(supportTable) CLUAVM_CLUAVM_CODE_SNIP(table);
		if(supportIo) CLUAVM_CLUAVM_CODE_SNIP(io);
		if(supportOs) CLUAVM_CLUAVM_CODE_SNIP(os);
		if(supportString) CLUAVM_CLUAVM_CODE_SNIP(string);
		if(supportMath) CLUAVM_CLUAVM_CODE_SNIP(math);
		if(supportDebug) CLUAVM_CLUAVM_CODE_SNIP(debug);

#undef CLUAVM_CLUAVM_CODE_SNIP
#endif
		//支持 luabind
		luabind::open(L);
	}
	~CLuaVM()
	{
		if( m_luaVM ) lua_close(m_luaVM);
	}
	operator lua_State*()
	{
		return m_luaVM;
	}

private:
	lua_State* m_luaVM;
};
