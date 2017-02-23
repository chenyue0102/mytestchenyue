#pragma once

namespace SerializeExport
{
// ���л�����
enum EnumSerializeIO
{
	EnumSerializeIONone,		// Ĭ��ֵ
	EnumSerializeIORead,		// ��ȡ����
	EnumSerializeIOWrite,		// д������
};

// ���л��ĸ�ʽ
enum EnumSerializeFormat
{
	EnumSerializeFormatNone,
	EnumSerializeFormatBinary,	// ������
	EnumSerializeFormatJson,	// Json��ʽ
	EnumSerializeFormatXml,		// Xml��ʽ
};

//�����л��ַ����ı��룬�����Json���л�дʱ���Ὣ�ַ���ת����utf8��Json����ʱ�򣬻Ὣutf8ת��Ϊָ������
//Binary��Xml��֧��gb2312��utf8
enum EnumSerializeStringCode
{
	EnumSerializeStringCodeNone,		//Ĭ�ϣ���EnumSerializeStringCodeUtf8�߼����
	EnumSerializeStringCodeUtf8,		//utf8
	EnumSerializeStringCodeBinary,		//std::string�д洢���Ƕ��������ݣ���Щ����£���std::string��������ʹ��

	EnumSerializeStringCodeGB2312 = 1000,		//GB2312��
};

// ���л����������£����鳤�����޷���32λ��������ֹ��ͬ�����������鳤���ֶ�ռ�ÿռ䲻һ��
#ifdef WIN32
typedef unsigned long suint32;
#else
#error ��������ƽ̨�޷���32λ����
#endif
}

