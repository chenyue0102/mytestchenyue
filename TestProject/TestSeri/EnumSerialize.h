#pragma once

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
	EnumSerializeFormatBinary,	// �����ƣ�
	EnumSerializeFormatJson,	// Json��ʽ�����л�std::string��ʱ��Json��ʽֻ����utf8�ַ���
	EnumSerializeFormatXml,		// Xml��ʽ�����л�std::string��ʱ��ֻ����utf8�ַ���
};

//�����л��ַ����ı��룬�����Json���л�дʱ���Ὣ�ַ���ת����utf8��Json����ʱ�򣬻Ὣutf8ת��Ϊָ������
//Binary��Xml��֧��gb2312��utf8
enum EnumSerializeStringCode
{
	EnumSerializeStringCodeNone,		//Ĭ�ϣ���EnumSerializeStringCodeGB2312�߼����
	EnumSerializeStringCodeGB2312,		//GB2312��
	EnumSerializeStringCodeUtf8,		//utf8
	EnumSerializeStringCodeBinary,		//std::string�д洢���Ƕ��������ݣ���Щ����£���std::string��������ʹ��
};
