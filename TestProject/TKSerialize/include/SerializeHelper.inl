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
/* �����������л�����                                                      */
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
/* ��չ�������л�������InnerSerializeWithException�ɹ����ٸ�ֵ              */
/************************************************************************/
inline void Serialize(ISerialize *pSerialize, std::string& Value, const char *pstrName)
{
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		//���л��ɹ����Ÿ�������ֵ
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
	//OldStringCode�������쳣���������Ϊ�������׳��쳣����ֹͣ���л������ָ��ɱ���û��ϵ
	//Json��xml�����׳��쳣�����Ի�ָ��ɱ���
	EnumSerializeStringCode OldStringCode = pSerialize->GetSerializeStringCode();
	pSerialize->SetSerializeStringCode(EnumSerializeStringCodeUtf8);
	if (EnumSerializeIORead == pSerialize->GetSerializeType())
	{
		//���л��ɹ����Ÿ�������ֵ
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
			//MAX_ARRAY_LIMITED_COUNT��ʾ��ȡ��ʱ��tArrayû����������
			std::insert_iterator<std::vector<T>> insertItor(tArray, tArray.end());//ĩβ���������
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
	//char�����size�������1����������ո��β
	static_assert(!(std::is_same<T, char>::value && _Size <= 1),
		"char Array Size Must > 1");
	InnerSerializeArray(pSerialize, tArray, _Size, pstrName);
}

/************************************************************************/
/* �ṹ��������л����ǽ���ʽ���л���������������                              */
/* struct Test                                                          */
/* {                                                                    */
/*    int a;                                                            */
/* };                                                                   */
/* //�ṹ�����л��������Ʊ���ΪSerializeStruct�����ʹ��SERIALIZE_VALUE��     */
/* //�������Ʊ���ΪValue                                                  */
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
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	
	if (!pSerialize->BeginSerializeStruct(pstrName))
	{
		// Json��Xmlû��Ԫ�أ���Ϊ��������Ȼ�󷵻أ��������л����������ݡ�
		// ���������л����׳��쳣�������˴����л�
		return ThrowException(pSerialize);
	}

	//��������ṹ������л�������ʹ�����ṩ�����л��������ƹ̶�ΪSerializeStruct
	bool bRes = SerializeStruct(pSerialize, Value);

	//��ΪBeginSerializeStruct�ɹ��ˣ������ȵ���EndSerializeStruct��Ȼ���ټ����λ���׳��쳣
	pSerialize->EndSerializeStruct(pstrName);

	if (!bRes)
	{
		ThrowException(pSerialize);
	}
}

/************************************************************************/
/* �������Ա������ʽ���л����������£�                                       */
/* struct Test                                                          */
/* {                                                                    */
/*		int a;                                                          */
/*      //��Ա�������л����Ʊ���ΪSerialize�����ʹ��SERIALIZE_STRUCT_VALUE�� */
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
	//T���ͱ����ǽṹ�������
	static_assert(std::is_class<T>::value, "Serialize T must be struct or class");
	//�������Ա����
	return Value.Serialize(pSerialize);
}
}
