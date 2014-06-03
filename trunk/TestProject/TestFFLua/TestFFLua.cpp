// TestFFLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../fflua-master/lua/fflua.h"
#include "../fflua-master/lua/fflua_register.h"
#include "../fflua-master/lua/fflua_type.h"
#include <Windows.h>
#include <string>

using namespace ff;

int	AddFun(int a, int b)
{
	return a+b;
}

struct TKSnsClientTLV
{
	DWORD	dwID;			// 属性ID
	DWORD	dwType;			// 属性类型(见eDicGlobalSnsMebMarkT)
	DWORD	dwLen;			// 属性长度
	std::string	strValue;		// 属性值
	TKSnsClientTLV()
	{
		printf("TKSnsClientTLV\n");
	}
	~TKSnsClientTLV()
	{
		printf("~TKSnsClientTLV\n");
	}
	void TKSnsClientTLV::SetDword(DWORD dwPropertyID, DWORD dwPropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 1;
		dwLen = sizeof(DWORD);
		strValue.append((char*)&dwPropertyValue, dwLen);
	}

	void TKSnsClientTLV::SetString(DWORD dwPropertyID, const char* pPropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 2;
		dwLen = (DWORD)strlen(pPropertyValue) + 1;
		strValue.append(pPropertyValue, dwLen);
	}

};

template<typename T>
class CMyVector : public std::vector<T>
{
public:
	CMyVector()
	{
		printf("CMyVector\n");
	}
	~CMyVector()
	{
		printf("~CMyVector\n");
	}
};

void WriteData(const std::vector<TKSnsClientTLV*> &Array)
{
	printf("WriteData\n");
}

static void lua_reg(lua_State* ls)
{
	fflua_register_t<>(ls)  
		.def(&AddFun, "AddFun");    

	fflua_register_t<>(ls)  
		.def(&WriteData, "WriteData");    

	fflua_register_t<TKSnsClientTLV,ctor()>(ls,"TKSnsClientTLV")
		.def(&TKSnsClientTLV::SetDword, "SetDword")
		//.def(&TKSnsClientTLV::SetString, "SetString")
		.def(&TKSnsClientTLV::dwID,"dwID")
		.def(&TKSnsClientTLV::dwType,"dwType")
		.def(&TKSnsClientTLV::dwLen,"dwLen")
		.def(&TKSnsClientTLV::strValue,"strValue");
}


int _tmain(int argc, _TCHAR* argv[])
{
	fflua_t fflua;

	fflua.reg(lua_reg);

	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestFFLuaFun.lua");
	//! 载入lua文件
	//fflua.add_package_path("./");
	fflua.load_file(szLuaFileName);
	std::string str("abc123");
	//测试调用Lua函数
	//fflua.call<int>("LuaTestCallFun", str); 

	//测试lua内部创建类
	//fflua.call<void>("LuaTestNewObject"); 
	
	//测试类指针
	TKSnsClientTLV Tlv;
	Tlv.strValue = "test class pointer";
	//fflua.call<int>("LuaTestClassPointer", &Tlv);

	//测试vecotr
	typedef std::vector<TKSnsClientTLV*>	TKSnsClientTLVArray;
	TKSnsClientTLVArray TlvArray;
	Tlv.SetDword(100, 200);
	TlvArray.push_back(new TKSnsClientTLV(Tlv));
	Tlv.SetString(300, "test300");
	TlvArray.push_back(new TKSnsClientTLV(Tlv));

	fflua.call<void>("LuaTestVector", TlvArray); 
	return 0;
}

