#ifndef TINYXML_EXPORT_INCLUDE
#define TINYXML_EXPORT_INCLUDE

#ifdef TINYXML_EXPORT
#define TINYXML_EXPORTS __declspec(dllexport)  // 声明一个导出函数，用于dll中。
#else
#define TINYXML_EXPORTS __declspec(dllimport)  // 声明一个导入函数，用于使用某个dll的exe中。
#endif

#endif//TINYXML_EXPORT_INCLUDE