// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：UTF8_GBK_Convert.h
// 创建日期：2014-03-21
// 创建人：罗俊杰
// 文件说明：UTF8和GBK的转换类
// $_FILEHEADER_END ***********************************************************

#ifndef UTF8_GBK_CONVERT_H
#define UTF8_GBK_CONVERT_H

// 转换类型
enum CHARSET_CONVERT_TYPE
{
	CHARSET_CONVERT_TYPE_DEFAULT = 0,		// 默认值
	CHARSET_CONVERT_TYPE_GBK_TO_UTF8 = 1,	// GBK转UTF8
	CHARSET_CONVERT_TYPE_UTF8_TO_GBK = 2,	// UTF8转GBK
};

class CUTF8_GBK_Convert
{
public:
	CUTF8_GBK_Convert();
	~CUTF8_GBK_Convert();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：Open
	// 函数参数：
	// 返 回 值：
	// 函数说明：初始化
	// $_FUNCTION_END *********************************************************
	void Open();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：IsOpen
	// 函数参数：
	// 返 回 值：是否初始化
	// 函数说明：是否初始化
	// $_FUNCTION_END *********************************************************
	bool IsOpen();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：ConvertCode
	// 函数参数：aiCharSetConvertType	[输入]		转换类型
	//			 apInput				[输入]		源字符集的字符串
	//			 alInputSize			[输入]		源字符集的字符串的大小
	//			 apOutput				[输入|输出]	目标字符集的字符串
	//			 alOutputSize			[输入|输出]	目标字符集的字符串的大小
	// 返 回 值：小于0表示失败
	// 函数说明：将某字符集的字符串转换为另一个字符集的字符串
	// $_FUNCTION_END *********************************************************
	int ConvertCode(int aiCharSetConvertType, const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

private:
	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InitGBKToUTF16_2
	// 函数参数：
	// 返 回 值：
	// 函数说明：初始化GBK到UTF8的2字节字符
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16_2();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InitGBKToUTF16_3
	// 函数参数：
	// 返 回 值：
	// 函数说明：初始化GBK到UTF8的3字节字符
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16_3();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InitGBKToUTF16
	// 函数参数：
	// 返 回 值：
	// 函数说明：初始化GBK到UTF16的字符
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：InitUTF16ToGBK
	// 函数参数：
	// 返 回 值：
	// 函数说明：初始化UTF16到GBK的字符
	// $_FUNCTION_END *********************************************************
	void InitUTF16ToGBK();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：GBKToUTF8
	// 函数参数：apInput			[输入]		源字符集的字符串
	//			 alInputSize		[输入]		源字符集的字符串的大小
	//			 apOutput			[输入|输出]	目标字符集的字符串
	//			 alOutputSize		[输入|输出]	目标字符集的字符串的大小
	// 返 回 值：小于0表示失败
	// 函数说明：GBK转UTF8
	// $_FUNCTION_END *********************************************************
	int GBKToUTF8(const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：UTF8ToGBK
	// 函数参数：apInput			[输入]		源字符集的字符串
	//			 alInputSize		[输入]		源字符集的字符串的大小
	//			 apOutput			[输入|输出]	目标字符集的字符串
	//			 alOutputSize		[输入|输出]	目标字符集的字符串的大小
	// 返 回 值：小于0表示失败
	// 函数说明：UTF8转GBK
	// $_FUNCTION_END *********************************************************
	int UTF8ToGBK(const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

private:
	// 是否初始化
	bool					m_bInit;

	// GBK到UTF16的2字节字符
	const unsigned short*	m_pGBKToUTF16_2;

	// GBK到UTF16的2字节字符大小
	unsigned short			m_GBKToUTF16_2_Size;

	// GBK到UTF16的3字节字符
	const unsigned short*	m_pGBKToUTF16_3;

	// GBK到UTF16的3字节字符大小
	unsigned short			m_GBKToUTF16_3_Size;

	// GBK到UTF16的字符
	unsigned short			m_GBKToUTF16[0x8000];

	// UTF16到GBK的字符
	unsigned short			m_UTF16ToGBK[0x10000];
};

#endif