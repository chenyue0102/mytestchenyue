#include "SerializeHelperEx.h"

namespace SerializeHelper
{
template<typename T>
inline suint32 InnerGetAnyVectorTypeSize(CTKPtrList<T> &tArray)
{
	return static_cast<suint32>(tArray.GetCount());
}

template<typename T>
inline bool InnerSerializeAnyVectorTypeItem(ISerialize *pSerialize, CTKPtrList<T> &tArray, suint32 unIndex)
{
	// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		T *pItem = new T();
		Serialize(pSerialize, *pItem, nullptr);
		tArray.AddTail(pItem);
		return true;
	}
	else if (EnumSerializeIOWrite == pSerialize->GetSerializeType())
	{
		T *pItem = tArray.GetAt(unIndex);
		if (nullptr == pItem)
		{
			assert(false);
			return false;
		}
		else
		{
			Serialize(pSerialize, *pItem, nullptr);
			return true;
		}
	}
	else
	{
		assert(false);
		return false;
	}
}

template<typename T>
inline void Serialize(ISerialize *pSerialize, CTKPtrList<T> &tArray, const char *pstrName)
{
	return InnerSerializeAnyVectorType(pSerialize, tArray, pstrName);
}

template<typename T>
inline suint32 InnerGetAnyVectorTypeSize(std::vector<T*> &tArray)
{
	return static_cast<suint32>(tArray.size());
}

template<typename T>
inline bool InnerSerializeAnyVectorTypeItem(ISerialize *pSerialize, std::vector<T*> &tArray, suint32 unIndex)
{
	// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		T *pItem = new T();
		Serialize(pSerialize, *pItem, nullptr);
		tArray.push_back(pItem);
		return true;
	}
	else if (EnumSerializeIOWrite == pSerialize->GetSerializeType())
	{
		T *pItem = tArray.at(unIndex);
		if (nullptr == pItem)
		{
			assert(false);
			return false;
		}
		else
		{
			Serialize(pSerialize, *pItem, nullptr);
			return true;
		}
	}
	else
	{
		assert(false);
		return false;
	}
}

template<typename T>
inline void Serialize(ISerialize *pSerialize, std::vector<T*> &tArray, const char *pstrName)
{
	static_assert(!std::is_pointer<T>::value, "T must not be pointer");
	return InnerSerializeAnyVectorType(pSerialize, tArray, pstrName);
}
}