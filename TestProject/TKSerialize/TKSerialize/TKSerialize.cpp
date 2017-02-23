// TKSerialize.cpp : 定义 DLL 应用程序的导出函数。
//
#include <assert.h>
#include "TKSerializeExport.h"
#include "TKSerializeExportDefine.h"
#include "TKSerializeApp.h"


namespace SerializeExport
{
TKSERIALIZE_API ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat)
{
	return theApp.CreateSerializeInterface(SerializeFormat);
}

TKSERIALIZE_API bool DestroySerializeInterface(ISerialize *pInterface)
{
	return theApp.DestroySerializeInterface(pInterface);
}

TKSERIALIZE_API bool SetDefaultStringCode(EnumSerializeStringCode DefaultStringCode)
{
	return theApp.SetDefaultStringCode(DefaultStringCode);
}

TKSERIALIZE_API EnumSerializeStringCode GetDefaultStringCode()
{
	return theApp.GetDefaultStringCode();
}
}


