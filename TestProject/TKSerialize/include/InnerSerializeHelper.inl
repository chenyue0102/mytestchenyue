#include "InnerSerializeHelper.h"

namespace SerializeHelper
{
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
/* 数组控制序列化                                                         */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayWrite(ISerialize *pSerialize, _InIt _First, suint32 ulValueCount, const char *pstrName)
{
	//只支持一维数组
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	if (!pSerialize->BeginSerializeArray(ulValueCount, pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	for (suint32 ulIndex = 0; ulIndex < ulValueCount; ulIndex++,++_First)
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
inline void InnerSerializeArrayRead(ISerialize *pSerialize, _InIt _First, suint32 ulLimitedCount, const char *pstrName)
{
	//只支持一维数组
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	assert(0 != ulLimitedCount);
	suint32 ulCount = 0;
	if (!pSerialize->BeginSerializeArray(ulCount, pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	//不能超过限制数量，Array可能是int a[4]这样的数组，不能超过数组的最大数量，vector<int> 则无此限制
	assert(ulCount <= ulLimitedCount);
	for (suint32 ulIndex = 0; 
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

//其他的数组类型，按照数组序列化
template<typename T>
inline void InnerSerializeArray(ISerialize *pSerialize, T tArray[], suint32 ulCount, const char *pstrName)
{
	static_assert(!std::is_pointer<T>::value, "T must not be pointer");
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
inline void InnerSerializeArray<char>(ISerialize *pSerialize, char tArray[], suint32 ulCount, const char *pstrName)
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

template<typename VECTOR_TYPE>
inline void InnerSerializeAnyVectorType(ISerialize *pSerialize, VECTOR_TYPE &tArray, const char *pstrName)
{
	suint32 ulLimitedCount = MAX_ARRAY_LIMITED_COUNT;
	//只支持一维数组
	assert(0 != ulLimitedCount);
	suint32 ulCount = InnerGetAnyVectorTypeSize(tArray);
	if (!pSerialize->BeginSerializeArray(ulCount, pstrName))
	{
		// Json，Xml没有元素，认为是正常。然后返回，继续序列化其他的内容。
		// 二进制序列化会抛出异常，结束此次序列化
		return ThrowException(pSerialize);
	}

	//不能超过限制数量，Array可能是int a[4]这样的数组，不能超过数组的最大数量，vector<int> 则无此限制
	assert(ulCount <= ulLimitedCount);
	for (suint32 ulIndex = 0; 
		ulIndex < ulCount && ulIndex < ulLimitedCount; 
		ulIndex++)
	{
		// BeginSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		InnerSerializeAnyVectorTypeItem(pSerialize, tArray, ulIndex);

		// EndSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
	pSerialize->EndSerializeArray(pstrName);
}

template<typename VECTOR_TYPE>
inline suint32 InnerGetAnyVectorTypeSize(VECTOR_TYPE &tArray)
{
	return static_cast<suint32>(tArray.size());
}

template<typename VECTOR_TYPE>
inline void InnerSerializeAnyVectorTypeItem(ISerialize *pSerialize, VECTOR_TYPE &tArray, suint32 unIndex)
{
	// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		VECTOR_TYPE::value_type item = VECTOR_TYPE::value_type();
		Serialize(pSerialize, item, nullptr);
		tArray.push_back(std::move(item));
	}
	else if (EnumSerializeIOWrite == pSerialize->GetSerializeType())
	{
		VECTOR_TYPE::value_type &item = tArray[unIndex];
		Serialize(pSerialize, item, nullptr);
	}
	else
	{
		assert(false);
	}
}
}

