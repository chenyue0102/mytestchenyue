#include "SerializeHelperEx.h"

namespace SerializeHelper
{
template<typename T>
inline void Serialize(ISerialize *pSerialize, CTKPtrList<T> &tArray, const char *pstrName)
{
	suint32 ulLimitedCount = MAX_ARRAY_LIMITED_COUNT;
	//ֻ֧��һά����
	assert(0 != ulLimitedCount);
	suint32 ulCount = tArray.GetCount();
	if (!pSerialize->BeginSerializeArray(ulCount, pstrName))
	{
		// Json��Xmlû��Ԫ�أ���Ϊ��������Ȼ�󷵻أ��������л����������ݡ�
		// ���������л����׳��쳣�������˴����л�
		return ThrowException(pSerialize);
	}

	//���ܳ�������������Array������int a[4]���������飬���ܳ�����������������vector<int> ���޴�����
	assert(ulCount <= ulLimitedCount);
	for (suint32 ulIndex = 0; 
		ulIndex < ulCount && ulIndex < ulLimitedCount; 
		ulIndex++)
	{
		// BeginSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		// Serialize ���������л��п����׳��쳣���������л��� Json��xml��Ӧ��ʧ��
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

		// EndSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
	pSerialize->EndSerializeArray(pstrName);
}
}