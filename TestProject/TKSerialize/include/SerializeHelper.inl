#include "SerializeHelper.h"
#include <cassert>
#include <iterator>
#ifdef QT_CORE_LIB
#include <QString>
#endif
#include "SerializeString.h"
#include "InterfaceSerialize.h"
#include "InnerSerializeHelper.h"


namespace SerializeHelper
{

/************************************************************************/
/* 基本类型序列化函数                                                      */
/************************************************************************/
inline void Serialize(ISerialize *pSerialize, bool& Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, char& Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, unsigned char& Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, short& Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, unsigned short& Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, int &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, unsigned int &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, long &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, unsigned long &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, long long &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, unsigned long long &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, float &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, double &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize *pSerialize, long double &Value, const char *pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

inline void Serialize(ISerialize * pSerialize, CSerializeString & Value, const char * pstrName)
{
	InnerSerializeWithException(pSerialize, Value, pstrName);
}

/************************************************************************/
/* 扩展类型序列化函数，InnerSerializeWithException成功后再赋值              */
/************************************************************************/
inline void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName)
{
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		//序列化成功，才给参数赋值
		CSerializeString strTemp;
		if (InnerSerializeWithException(pSerialize, strTemp, pstrName))
		{
			Value.assign(strTemp.data(), strTemp.size());
		}
	}
	else
	{
		CSerializeString strTemp(Value.data(), Value.size());
		InnerSerializeWithException(pSerialize, strTemp, pstrName);
	}
}

#ifdef QT_CORE_LIB
inline void Serialize(ISerialize *pSerialize, QString& Value, const char *pstrName)
{
	//OldStringCode不考虑异常的情况。因为二进制抛出异常就是停止序列化，不恢复旧编码没关系
	//Json与xml不会抛出异常，所以会恢复旧编码
	EnumSerializeStringCode OldStringCode = pSerialize->GetSerializeStringCode();
	pSerialize->SetSerializeStringCode(EnumSerializeStringCodeUtf8);
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		//序列化成功，才给参数赋值
		CSerializeString strTemp;
		if (InnerSerializeWithException(pSerialize, strTemp, pstrName))
		{
			Value = QString::fromUtf8(strTemp.c_str());
		}
	}
	else
	{
		CSerializeString strTemp(Value.toUtf8().data());
		InnerSerializeWithException(pSerialize, strTemp, pstrName);
	}
	pSerialize->SetSerializeStringCode(OldStringCode);
}
#endif

template<typename T>
inline void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName)
{
	static_assert(!std::is_pointer<T>::value, "T must not be pointer");
	switch (pSerialize->GetSerializeType())
	{
	case EnumSerializeIORead:
		{
			assert(0 == tArray.size());
			//MAX_ARRAY_LIMITED_COUNT表示读取的时候，tArray没有容量限制
			std::insert_iterator<std::vector<T>> insertItor(tArray, tArray.end());//末尾插入迭代器
			InnerSerializeArrayRead<T, std::insert_iterator<std::vector<T>>>(pSerialize, insertItor, 
				MAX_ARRAY_LIMITED_COUNT, pstrName);
		}
		break;
	case EnumSerializeIOWrite:
		{
			InnerSerializeArrayWrite<T, std::vector<T>::iterator>(pSerialize, tArray.begin(), tArray.size(), pstrName);
		}
		break;
	default:
		assert(false);
		break;
	}
}

template<typename T, size_t _Size> 
inline void Serialize(ISerialize *pSerialize, T (&tArray)[_Size], const char *pstrName)
{
	//char数组的size必须大于1，必须包含空格结尾
	static_assert(!(std::is_same<T, char>::value && _Size <= 1),
		"char Array Size Must > 1");
	InnerSerializeArray(pSerialize, tArray, _Size, pstrName);
}

/************************************************************************/
/* 结构体控制序列化，非浸入式序列化函数，类似如下                              */
/* struct Test                                                          */
/* {                                                                    */
/*    int a;                                                            */
/* };                                                                   */
/* //结构体序列化函数名称必须为SerializeStruct，如果使用SERIALIZE_VALUE宏     */
/* //参数名称必须为Value                                                  */
/* bool SerializeStruct(ISerialize *pSerialize, Test &Value)            */
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
template<typename T>
inline void Serialize(ISerialize *pSerialize, T &Value, const char *pstrName)
{
	//T类型必须是结构体或者类
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	
	if (!pSerialize->BeginSerializeStruct(pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	//调用这个结构体的序列化函数，使用者提供的序列化函数名称固定为SerializeStruct
	bool bRes = SerializeStruct(pSerialize, Value);

	//因为BeginSerializeStruct成功了，所以先调用EndSerializeStruct，然后再检测标记位，抛出异常
	pSerialize->EndSerializeStruct(pstrName);

	if (!bRes)
	{
		ThrowException(pSerialize);
	}
}

/************************************************************************/
/* 兼容类成员函数形式序列化，类似如下：                                       */
/* struct Test                                                          */
/* {                                                                    */
/*		int a;                                                          */
/*      //成员函数序列化名称必须为Serialize，如果使用SERIALIZE_STRUCT_VALUE宏 */
/*		bool Serialize(ISerialize *pSerialize)                          */
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
template<typename T>
inline bool SerializeStruct(ISerialize *pSerialize, T &Value)
{
	//T类型必须是结构体或者类
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	//调用类成员函数
	return Value.Serialize(pSerialize);
}
}
