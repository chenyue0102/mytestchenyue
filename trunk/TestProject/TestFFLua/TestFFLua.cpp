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

struct TKSnsClientTLV
{
	DWORD	dwID;			// ����ID
	DWORD	dwType;			// ��������(��eDicGlobalSnsMebMarkT)
	DWORD	dwLen;			// ���Գ���
	std::string	strValue;		// ����ֵ
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
	//! ����lua�ļ�
	//fflua.add_package_path("./");
	fflua.load_file(szLuaFileName);
	std::string str("abc123");
	//���Ե���Lua����
	//fflua.call<int>("LuaTestCallFun", str); 

	//����lua�ڲ�������
	//fflua.call<void>("LuaTestNewObject"); 
	
	//������ָ��
	TKSnsClientTLV Tlv;
	Tlv.strValue = "test class pointer";
	//fflua.call<int>("LuaTestClassPointer", &Tlv);

	//����vecotr
	typedef std::vector<TKSnsClientTLV*>	TKSnsClientTLVArray;
	TKSnsClientTLVArray TlvArray;
	Tlv.SetDword(100, 200);
	TlvArray.push_back(new TKSnsClientTLV(Tlv));
	Tlv.SetString(300, "test300");
	TlvArray.push_back(new TKSnsClientTLV(Tlv));

	fflua.call<void>("LuaTestVector", TlvArray); 
	return 0;
}

