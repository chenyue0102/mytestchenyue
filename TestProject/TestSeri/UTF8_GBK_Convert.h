// $_FILEHEADER_BEGIN *********************************************************
// �ļ����ƣ�UTF8_GBK_Convert.h
// �������ڣ�2014-03-21
// �����ˣ��޿���
// �ļ�˵����UTF8��GBK��ת����
// $_FILEHEADER_END ***********************************************************

#ifndef UTF8_GBK_CONVERT_H
#define UTF8_GBK_CONVERT_H

// ת������
enum CHARSET_CONVERT_TYPE
{
	CHARSET_CONVERT_TYPE_DEFAULT = 0,		// Ĭ��ֵ
	CHARSET_CONVERT_TYPE_GBK_TO_UTF8 = 1,	// GBKתUTF8
	CHARSET_CONVERT_TYPE_UTF8_TO_GBK = 2,	// UTF8תGBK
};

class CUTF8_GBK_Convert
{
public:
	CUTF8_GBK_Convert();
	~CUTF8_GBK_Convert();

public:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�Open
	// ����������
	// �� �� ֵ��
	// ����˵������ʼ��
	// $_FUNCTION_END *********************************************************
	void Open();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�IsOpen
	// ����������
	// �� �� ֵ���Ƿ��ʼ��
	// ����˵�����Ƿ��ʼ��
	// $_FUNCTION_END *********************************************************
	bool IsOpen();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�ConvertCode
	// ����������aiCharSetConvertType	[����]		ת������
	//			 apInput				[����]		Դ�ַ������ַ���
	//			 alInputSize			[����]		Դ�ַ������ַ����Ĵ�С
	//			 apOutput				[����|���]	Ŀ���ַ������ַ���
	//			 alOutputSize			[����|���]	Ŀ���ַ������ַ����Ĵ�С
	// �� �� ֵ��С��0��ʾʧ��
	// ����˵������ĳ�ַ������ַ���ת��Ϊ��һ���ַ������ַ���
	// $_FUNCTION_END *********************************************************
	int ConvertCode(int aiCharSetConvertType, const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

private:
	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InitGBKToUTF16_2
	// ����������
	// �� �� ֵ��
	// ����˵������ʼ��GBK��UTF8��2�ֽ��ַ�
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16_2();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InitGBKToUTF16_3
	// ����������
	// �� �� ֵ��
	// ����˵������ʼ��GBK��UTF8��3�ֽ��ַ�
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16_3();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InitGBKToUTF16
	// ����������
	// �� �� ֵ��
	// ����˵������ʼ��GBK��UTF16���ַ�
	// $_FUNCTION_END *********************************************************
	void InitGBKToUTF16();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�InitUTF16ToGBK
	// ����������
	// �� �� ֵ��
	// ����˵������ʼ��UTF16��GBK���ַ�
	// $_FUNCTION_END *********************************************************
	void InitUTF16ToGBK();

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�GBKToUTF8
	// ����������apInput			[����]		Դ�ַ������ַ���
	//			 alInputSize		[����]		Դ�ַ������ַ����Ĵ�С
	//			 apOutput			[����|���]	Ŀ���ַ������ַ���
	//			 alOutputSize		[����|���]	Ŀ���ַ������ַ����Ĵ�С
	// �� �� ֵ��С��0��ʾʧ��
	// ����˵����GBKתUTF8
	// $_FUNCTION_END *********************************************************
	int GBKToUTF8(const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�UTF8ToGBK
	// ����������apInput			[����]		Դ�ַ������ַ���
	//			 alInputSize		[����]		Դ�ַ������ַ����Ĵ�С
	//			 apOutput			[����|���]	Ŀ���ַ������ַ���
	//			 alOutputSize		[����|���]	Ŀ���ַ������ַ����Ĵ�С
	// �� �� ֵ��С��0��ʾʧ��
	// ����˵����UTF8תGBK
	// $_FUNCTION_END *********************************************************
	int UTF8ToGBK(const char* apInput, unsigned long alInputSize, char* apOutput, unsigned long& alOutputSize);

private:
	// �Ƿ��ʼ��
	bool					m_bInit;

	// GBK��UTF16��2�ֽ��ַ�
	const unsigned short*	m_pGBKToUTF16_2;

	// GBK��UTF16��2�ֽ��ַ���С
	unsigned short			m_GBKToUTF16_2_Size;

	// GBK��UTF16��3�ֽ��ַ�
	const unsigned short*	m_pGBKToUTF16_3;

	// GBK��UTF16��3�ֽ��ַ���С
	unsigned short			m_GBKToUTF16_3_Size;

	// GBK��UTF16���ַ�
	unsigned short			m_GBKToUTF16[0x8000];

	// UTF16��GBK���ַ�
	unsigned short			m_UTF16ToGBK[0x10000];
};

#endif