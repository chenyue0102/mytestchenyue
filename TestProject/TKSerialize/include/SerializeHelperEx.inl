#include "SerializeHelperEx.h"

namespace SerializeHelper
{
template<typename T>
inline void Serialize(ISerialize *pSerialize, CTKPtrList<T> &tArray, const char *pstrName)
{
	suint32 ulLimitedCount = MAX_ARRAY_LIMITED_COUNT;
	//只支持一维数组
	assert(0 != ulLimitedCount);
	suint32 ulCount = tArray.GetCount();
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

		// Serialize 二进制序列化有可能抛出异常，结束序列化， Json与xml不应该失败
		if (EnumSerializeIORead == pSerialize->GetSerializeType())
		{
			T *pItem = new T();
			Serialize(pSerialize, *pItem, nullptr);
			tArray.AddTail(pItem);
		}
		else if (EnumSerializeIOWrite == pSerialize->GetSerializeType())
		{
			T *pItem = tArray.GetAt(ulIndex);
			if (nullptr == pItem)
			{
				pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
				assert(false);
				break;
			}
			Serialize(pSerialize, *pItem, nullptr);
		}
		else
		{
			pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
			assert(false);
			break;
		}

		// EndSerializeArrayItem 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray 二进制序列化固定返回true， Json与xml不应该失败，这里不做判断了
	pSerialize->EndSerializeArray(pstrName);
}
}