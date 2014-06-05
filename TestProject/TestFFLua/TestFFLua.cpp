// TestFFLua.cpp : �������̨Ӧ�ó������ڵ㡣
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

struct TestTLV
{
	DWORD	dwID;			// ����ID
	DWORD	dwType;
	DWORD	dwLen;			// ���Գ���
	std::string	strValue;		// ����ֵ
	TestTLV()
	{
		printf("TestTLV\n");
	}
	~TestTLV()
	{
		printf("~TestTLV\n");
	}
	void TestTLV::SetDword(DWORD dwPropertyID, DWORD dwPropertyValue)
	{
		strValue.clear();
		dwID = dwPropertyID;
		dwType = 1;
		dwLen = sizeof(DWORD);
		strValue.append((char*)&dwPropertyValue, dwLen);
	}

	void TestTLV::SetString(DWORD dwPropertyID, const char* pPropertyValue)
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

BOOL WriteData(const std::vector<TestTLV*> &Array)
{
	printf("WriteData\n");
	return TRUE;
}

static void lua_reg(lua_State* ls)
{
	fflua_register_t<>(ls)  
		.def(&AddFun, "AddFun");    

	fflua_register_t<>(ls)  
		.def(&WriteData, "WriteData");    

	fflua_register_t<TestTLV,ctor()>(ls,"TestTLV")
		.def(&TestTLV::SetDword, "SetDword")
		//.def(&TestTLV::SetString, "SetString")
		.def(&TestTLV::dwID,"dwID")
		.def(&TestTLV::dwType,"dwType")
		.def(&TestTLV::dwLen,"dwLen")
		.def(&TestTLV::strValue,"strValue");
}


int _tmain(int argc, _TCHAR* argv[])
{
	fflua_t fflua;

	fflua.reg(lua_reg);

	char szCurrentDir[MAX_PATH] = {0}, szLuaFileName[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szCurrentDir, MAX_PATH);
	*strrchr(szCurrentDir,'\\') = '\0';
	_snprintf(szLuaFileName, MAX_PATH, "%s%s", szCurrentDir, "\\TestFFLuaFun.lua");
	//! ����lua�ļ�
	//fflua.add_package_path("./");
	fflua.load_file(szLuaFileName);
	std::string str("abc123");
	//���Ե���Lua����
	//fflua.call<int>("LuaTestCallFun", str); 

	//����lua�ڲ�������
	//fflua.call<void>("LuaTestNewObject"); 
	
	//������ָ��
	TestTLV Tlv;
	Tlv.strValue = "test class pointer";
	//fflua.call<int>("LuaTestClassPointer", &Tlv);

	//����vecotr
	typedef std::vector<TestTLV*>	TestTLVArray;
	TestTLVArray TlvArray;
	Tlv.SetDword(100, 200);
	TlvArray.push_back(new TestTLV(Tlv));
	Tlv.SetString(300, "test300");
	TlvArray.push_back(new TestTLV(Tlv));

	fflua.call<void>("LuaTestVector", TlvArray); 
	return 0;
}

