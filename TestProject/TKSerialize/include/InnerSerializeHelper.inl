#include "InnerSerializeHelper.h"

namespace SerializeHelper
{
/************************************************************************/
/* ���������л���������׳��쳣����������������л���                          */
/* Json��xml֧��ĳЩ�ֶγ���󣬼������л�                                   */
/************************************************************************/
inline void ThrowException(ISerialize *pSerialize)
{
	switch (pSerialize->GetSerializeFormat())
	{
	case EnumSerializeFormatBinary:
		throw -1;			//�׳��쳣��ֹͣ���л�
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
/* �����������л��ӿ�ģ�壬�������쳣������ͳһ�˳�                            */
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
/* ����������л�                                                         */
/************************************************************************/
template<typename T, typename _InIt>
inline void InnerSerializeArrayWrite(ISerialize *pSerialize, _InIt _First, suint32 ulValueCount, const char *pstrName)
{
	//ֻ֧��һά����
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	if (!pSerialize->BeginSerializeArray(ulValueCount, pstrName))
	{
		// Json��Xmlû��Ԫ�أ���Ϊ��������Ȼ�󷵻أ��������л����������ݡ�
		// ���������л����׳��쳣�������˴����л�
		return ThrowException(pSerialize);
	}

	for (suint32 ulIndex = 0; ulIndex < ulValueCount; ulIndex++,++_First)
	{
		// BeginSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		// Serialize ���������л��п����׳��쳣���������л��� Json��xml��Ӧ��ʧ��
		T &t = *_First;
		Serialize(pSerialize, t, nullptr);

		// EndSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
	pSerialize->EndSerializeArray(pstrName);
}

template<typename T, typename _InIt>
inline void InnerSerializeArrayRead(ISerialize *pSerialize, _InIt _First, suint32 ulLimitedCount, const char *pstrName)
{
	//ֻ֧��һά����
	static_assert(!std::is_array<T>::value, "T must not Be Array");
	assert(0 != ulLimitedCount);
	suint32 ulCount = 0;
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
		ulIndex++,++_First)
	{
		// BeginSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		if (!pSerialize->BeginSerializeArrayItem(ulIndex, pstrName))
		{
			assert(false);
			break;
		}

		// Serialize ���������л��п����׳��쳣���������л��� Json��xml��Ӧ��ʧ��
		T t;
		Serialize(pSerialize, t, nullptr);

		*_First = std::move(t);

		// EndSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
	pSerialize->EndSerializeArray(pstrName);
}

//�������������ͣ������������л�
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

//�ṩһ��char�����ȫ�������汾,char���鵱���ַ������л�
template<>
inline void InnerSerializeArray<char>(ISerialize *pSerialize, char tArray[], suint32 ulCount, const char *pstrName)
{
	//��char*ת����std::string�������л�
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
		CSerializeString strTemp(tArray);	//Value����'\0'��β
		Serialize(pSerialize, strTemp, pstrName);
	}
}

template<typename VECTOR_TYPE>
inline void InnerSerializeAnyVectorType(ISerialize *pSerialize, VECTOR_TYPE &tArray, const char *pstrName)
{
	suint32 ulLimitedCount = MAX_ARRAY_LIMITED_COUNT;
	//ֻ֧��һά����
	assert(0 != ulLimitedCount);
	suint32 ulCount = InnerGetAnyVectorTypeSize(tArray);
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

		InnerSerializeAnyVectorTypeItem(pSerialize, tArray, ulIndex);

		// EndSerializeArrayItem ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
		pSerialize->EndSerializeArrayItem(ulIndex, pstrName);
	}

	// EndSerializeArray ���������л��̶�����true�� Json��xml��Ӧ��ʧ�ܣ����ﲻ���ж���
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
	// Serialize ���������л��п����׳��쳣���������л��� Json��xml��Ӧ��ʧ��
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

