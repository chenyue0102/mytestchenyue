#include "SerializeHelper.h"
#include <cassert>
#include <iterator>
#ifdef QT_DLL
#include <QString>
#endif
#include "SerializeString.h"
#include "InterfaceSerialize.h"


namespace SerializeHelper
{
inline void test()
{

}

/************************************************************************/
/* 二进制序列化，出错后抛出异常，不在允许继续序列化，                          */
/* Json与xml支持某些字段出错后，继续序列化                                   */
/************************************************************************/
inline void ThrowException(ISerialize *pSerialize)
{
	switch (pSerialize->GetSerializeFormat())
	{
	case EnumSerializeFormatBinary:
		throw -1;			//抛出异常，停止序列化
		break;
	case EnumSerializeFormatJson:
	case EnumSerializeFormatXml:
		break;
	default:
		assert(false);
		break;
	}
}
/************************************************************************/
/* 真正调用序列化接口模板，增加了异常，方便统一退出                            */
/************************************************************************/
template<typename T>
inline bool InnerSerializeWithException(ISerialize *pSerialize, T& Value, const char *pstrName)
{
	static_assert(std::is_arithmetic<T>::value || std::is_same<T, CSerializeString>::value , 
		"T must be an integral type or a floating-point type or CSerializeString");
	bool bRes = false;
	if (nullptr != pSerialize)
	{
		bRes = pSerialize->Serialize(Value, pstrName);
	}
	else
	{
		assert(false);
	}
	if (!bRes)
	{
		ThrowException(pSerialize);
	}
	return bRes;
}

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


/************************************************************************/
/* 数组控制序列化                                                         */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayWrite(ISerialize *pSerialize, _InIt _First, unsigned long ulValueCount, const char *pstrName)
{
	//只支持一维数组
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	if (!pSerialize->BeginSerializeArray(ulValueCount, pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	for (unsigned long ulIndex = 0; ulIndex < ulValueCount; ulIndex++,++_First)
	{
		// BeginSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
		T &t = *_First;
		Serialize(pSerialize, t, nullptr);

		// EndSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
	pSerialize->EndSerializeArray(pstrName);
}

template<typename T, typename _InIt>
inline void InnerSerializeArrayRead(ISerialize *pSerialize, _InIt _First, unsigned long ulLimitedCount, const char *pstrName)
{
	//只支持一维数组
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	assert(0 != ulLimitedCount);
	unsigned long ulCount = 0;
	if (!pSerialize->BeginSerializeArray(ulCount, pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	//不能超过限制数量，Array可能是int a[4]这样的数组，不能超过数组的最大数量，vector<int> 则无此限制
	assert(ulCount <= ulLimitedCount);
	for (unsigned long ulIndex = 0; 
		ulIndex < ulCount && ulIndex < ulLimitedCount; 
		ulIndex++,++_First)
	{
		// BeginSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
		T t;
		Serialize(pSerialize, t, nullptr);

		*_First = std::move(t);

		// EndSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
	pSerialize->EndSerializeArray(pstrName);
}


template<typename T>
inline void Serialize(ISerialize *pSerialize, std::vector<T> &tArray, const char *pstrName)
{
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

//其他的数组类型，按照数组序列化
template<typename T>
inline void InnerSerializeArray(ISerialize *pSerialize, T tArray[], unsigned long ulCount, const char *pstrName)
{
	switch (pSerialize->GetSerializeType())
	{
	case EnumSerializeIORead:
		{
			InnerSerializeArrayRead<T, T*>(pSerialize, tArray, ulCount, pstrName);
		}
		break;
	case EnumSerializeIOWrite:
		{
			InnerSerializeArrayWrite<T, T*>(pSerialize, tArray, ulCount, pstrName);
		}
		break;
	default:
		assert(false);
		break;
	}
}

//提供一个char数组的全特例化版本,char数组当成字符串序列化
template<>
inline void InnerSerializeArray<char>(ISerialize *pSerialize, char tArray[], unsigned long ulCount, const char *pstrName)
{
	//将char*转换成std::string，再序列化
	assert(ulCount > 1);
	assert(strlen(tArray) < ulCount);
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		CSerializeString strTemp;
		Serialize(pSerialize, strTemp, pstrName);
		assert(ulCount > strTemp.size());
		strncpy(tArray, strTemp.c_str(), ulCount - 1);
	}
	else
	{
		CSerializeString strTemp(tArray);	//Value必须'\0'结尾
		Serialize(pSerialize, strTemp, pstrName);
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
