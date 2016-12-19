// TKSerialize.cpp : 定义 DLL 应用程序的导出函数。
//
#include <assert.h>
#include "BinarySerialize.h"
#include "JsonSerialize.h"
#include "XmlSerialize.h"
#include "TKSerializeExport.h"
#include "TKSerialize.h"


namespace SerializeExport
{
ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat)
{
	ISerialize *pInterface = nullptr;
	switch (SerializeFormat)
	{
	case EnumSerializeFormatBinary:
		pInterface = new CBinarySerialize();
		break;
	case EnumSerializeFormatJson:
		pInterface = new CJsonSerialize();
		break;
	case EnumSerializeFormatXml:
		pInterface = new CXmlSerialize();
		break;
	default:
		assert(false);
		break;
	}
	return pInterface;
}

void DestroySerializeInterface(ISerialize *pInterface)
{
	if (nullptr != pInterface)
	{
		switch (pInterface->GetSerializeFormat())
		{
		case EnumSerializeFormatBinary:
			delete static_cast<CBinarySerialize*>(pInterface);
			break;
		case EnumSerializeFormatJson:
			delete static_cast<CJsonSerialize*>(pInterface);
			break;
		case EnumSerializeFormatXml:
			delete static_cast<CXmlSerialize*>(pInterface);
			break;
		default:
			assert(false);
			break;
		}
	}
	else
	{
		assert(false);
	}
}
}


