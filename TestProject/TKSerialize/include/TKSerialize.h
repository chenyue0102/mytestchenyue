#pragma once
#include "TKSerializeExport.h"
#include "EnumSerialize.h"
#include "InterfaceSerialize.h"

namespace SerializeExport
{
// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�CreateSerializeInterface
// ����������
//					SerializeFormat	[����]		���л���ʽ
// �� �� ֵ�����л��ӿ�
// ����˵������ȡĳ�����л��ӿ�
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API ISerialize* CreateSerializeInterface(EnumSerializeFormat SerializeFormat);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�DestroySerializeInterface
// ����������
//					pInterface		[����]		���л��ӿ�
// �� �� ֵ��true or false
// ����˵�����ͷ����л��ӿ�
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API bool DestroySerializeInterface(ISerialize *pInterface);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�SetDefaultStringCode
// ����������
//					DefaultStringCode	[����]	Ĭ���ַ�������
// �� �� ֵ��true or false
// ����˵��������Ĭ��std::string char[]�У��洢���ַ��������ʽ
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API bool SetDefaultStringCode(EnumSerializeStringCode DefaultStringCode);

// $_FUNCTION_BEGIN *******************************************************
// �������ƣ�GetDefaultStringCode
// ����������
// �� �� ֵ���ַ�������
// ����˵������ȡĬ��std::string char[]�У��洢���ַ��������ʽ
// $_FUNCTION_END *********************************************************
TKSERIALIZE_API EnumSerializeStringCode GetDefaultStringCode();
}
