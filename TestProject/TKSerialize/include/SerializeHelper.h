// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：SerializeHelper.h
// 创建日期：2016-04-08
// 创建人：陈月
// 文件说明：序列化帮助类，可以使得序列化基本类型，结构体类型，vector数组方式一样
// $_FILEHEADER_END ***********************************************************
#pragma once
#include <vector>
#include <string>
#include "EnumSerialize.h"

#define MAX_ARRAY_LIMITED_COUNT		2147483647		//序列化Array的时候，需要一个容器最大数量，这个值表示最大数量


namespace SerializeExport
{
	class CSerializeString;
	struct ISerialize;
}
#ifdef QT_CORE_LIB
class QString;
#endif
using namespace  SerializeExport;
/************************************************************************/
/* 序列化宏 Serialize                                                */
/************************************************************************/
//序列化宏定义
#define SERIALIZE_STRUCT_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, value, #value); 

/************************************************************************/
/* 使用全局序列化函数时的宏 SerializeStruct                                */
/************************************************************************/
//序列化宏定义，使用外部的序列化函数时的帮助函数
#define SERIALIZE_VALUE(value) \
                SerializeHelper::Serialize(pSerialize, Value.value, #value); 



/************************************************************************/
/* 序列化的一些帮助函数，使得使用序列化的时候，简化统一方式，                   */
/* pSerialize指针这里不会判空，外部判断                                     */
/************************************************************************/
namespace SerializeHelper
{

/************************************************************************/
/* 基本类型序列化函数                                                      */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, bool& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，这个表示字符
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned char& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned short& Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned int &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, unsigned long long &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, float &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, long double &Value, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, CSerializeString& Value, const char *pstrName);



/************************************************************************/
/* 扩展类型序列化函数，InnerSerializeWithException成功后再赋值              */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数，字符串编码默认为GB2312。更改编码使用SetStringCode
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, std::string& Value, const char *pstrName);

#ifdef QT_CORE_LIB
// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化变量
// $_FUNCTION_END *********************************************************
inline void Serialize(ISerialize &pSerialize, QString& Value, const char *pstrName);
#endif


/************************************************************************/
/* 数组控制序列化                                                         */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化vector数组变量
// $_FUNCTION_END *********************************************************
template<typename T>
inline void Serialize(ISerialize &pSerialize, std::vector<T> &tArray, const char *pstrName);

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					tArray				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化int nParam[8],char szNickName[16]这样的成员数组变量
// $_FUNCTION_END *********************************************************
template<typename T, size_t _Size> 
inline void Serialize(ISerialize &pSerialize, T (&tArray)[_Size], const char *pstrName);


/************************************************************************/
/* 结构体控制序列化，非浸入式序列化函数，类似如下                              */
/* struct Test                                                          */
/* {                                                                    */
/*    int a;                                                            */
/* };                                                                   */
/* //结构体序列化函数名称必须为SerializeStruct，如果使用SERIALIZE_VALUE宏     */
/* //参数名称必须为Value                                                  */
/* bool SerializeStruct(ISerialize &pSerialize, Test &Value)            */
/* {                                                                    */
/*     try                                                              */
/*     {                                                                */
/*         SERIALIZE_VALUE(a);                                          */
/*     }                                                                */
/*     catch (...)                                                      */
/*     {                                                                */
/*         return false;                                                */
/*     }                                                                */
/*     return true;                                                     */
/* }                                                                    */
/************************************************************************/

// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
//					pstrName			[输入]		参数的名字,nullptr表示此参数没有名字
// 返 回 值：
// 函数说明：序列化结构体变量
// $_FUNCTION_END *********************************************************
template<typename T>
inline void Serialize(ISerialize &pSerialize, T &Value, const char *pstrName);


/************************************************************************/
/* 兼容类成员函数形式序列化，类似如下：                                       */
/* struct Test                                                          */
/* {                                                                    */
/*		int a;                                                          */
/*      //成员函数序列化名称必须为Serialize，如果使用SERIALIZE_STRUCT_VALUE宏 */
/*		bool Serialize(ISerialize &pSerialize)                          */
/*      {                                                               */
/*          try                                                         */
/*          {                                                           */
/*              SERIALIZE_STRUCT_VALUE(a);                              */
/*          }                                                           */
/*          catch (...)                                                 */
/*          {                                                           */
/*              return false;                                           */
/*          }                                                           */
/*          return true;                                                */
/*      }                                                               */
/* };                                                                   */
/************************************************************************/


// $_FUNCTION_BEGIN *******************************************************
// 函数名称：Serialize
// 函数参数：
//					pSerialize			[输入]		序列化接口
//					Value				[输入/输出]	需要序列化的参数
// 返 回 值：
// 函数说明：序列化结构体变量，只为兼容成员函数形式序列化，其他情况下，此函数没有用处
// $_FUNCTION_END *********************************************************
template<typename T>
inline bool SerializeStruct(ISerialize &pSerialize, T &Value);
};

#include "SerializeHelper.inl"