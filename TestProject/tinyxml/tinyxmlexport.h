#ifndef TINYXML_EXPORT_INCLUDE
#define TINYXML_EXPORT_INCLUDE

#ifdef TINYXML_EXPORT
#define TINYXML_EXPORTS __declspec(dllexport)  // ����һ����������������dll�С�
#else
#define TINYXML_EXPORTS __declspec(dllimport)  // ����һ�����뺯��������ʹ��ĳ��dll��exe�С�
#endif

#endif//TINYXML_EXPORT_INCLUDE