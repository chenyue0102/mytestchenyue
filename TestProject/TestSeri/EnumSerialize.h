#pragma once

// 序列化类型
enum EnumSerializeIO
{
	EnumSerializeIONone,		// 默认值
	EnumSerializeIORead,		// 读取数据
	EnumSerializeIOWrite,		// 写入数据
};

// 序列化的格式
enum EnumSerializeFormat
{
	EnumSerializeFormatNone,
	EnumSerializeFormatBinary,	// 二进制，
	EnumSerializeFormatJson,	// Json格式，序列化std::string的时候，Json格式只接受utf8字符串
	EnumSerializeFormatXml,		// Xml格式，序列化std::string的时候，只接受utf8字符串
};

//待序列化字符串的编码，如果是Json序列化写时，会将字符串转换成utf8。Json读的时候，会将utf8转换为指定编码
//Binary与Xml，支持gb2312与utf8
enum EnumSerializeStringCode
{
	EnumSerializeStringCodeNone,		//默认，与EnumSerializeStringCodeGB2312逻辑相等
	EnumSerializeStringCodeGB2312,		//GB2312，
	EnumSerializeStringCodeUtf8,		//utf8
	EnumSerializeStringCodeBinary,		//std::string中存储的是二进制数据，有些情况下，把std::string当缓冲区使用
};
