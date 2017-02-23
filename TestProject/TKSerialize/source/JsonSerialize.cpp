#include "JsonSerialize.h"
#include <cassert>
#include "SerializeString.h"
#include "CodeConvert.h"


CJsonSerialize::CJsonSerialize()
	: m_iSerializeType(EnumSerializeIONone)
	, m_pRootValue(new Json::Value(Json::objectValue))
	, m_pCurValue(nullptr)
	, m_StackValue()
	, m_bHaveWriteToBuffer(false)
	, m_SerializeStringCode(EnumSerializeStringCodeNone)
{
	m_pCurValue = m_pRootValue;
}

CJsonSerialize::~CJsonSerialize()
{

}

bool CJsonSerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
	if (!(EnumSerializeIORead == m_iSerializeType || EnumSerializeIOWrite == m_iSerializeType))
	{
		Log("CJsonSerialize::SetSerializeType iSerializeType=%d Error", static_cast<int>(iSerializeType));
		assert(false);
		return false;
	}
	else
	{
		return true;
	}
}

EnumSerializeIO CJsonSerialize::GetSerializeType()
{
	if (!(EnumSerializeIORead == m_iSerializeType || EnumSerializeIOWrite == m_iSerializeType))
	{
		Log("CJsonSerialize::GetSerializeType m_iSerializeType=%d Error", static_cast<int>(m_iSerializeType));
		assert(false);
	}
	return m_iSerializeType;
}

EnumSerializeFormat CJsonSerialize::GetSerializeFormat()
{
	return EnumSerializeFormatJson;
}

bool CJsonSerialize::SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)
{
	m_SerializeStringCode = SerializeStringCode;
	return true;
}

EnumSerializeStringCode CJsonSerialize::GetSerializeStringCode()
{
	return m_SerializeStringCode;
}

bool CJsonSerialize::SetData(const char *pstrText, suint32 ulDataLength)
{
	std::string strText;
	strText.append(pstrText, ulDataLength);
	Json::Reader r;
	bool bRes = r.parse(strText, *m_pRootValue);
	if (!bRes)
	{
		Log("CJsonSerialize::SetData JsonText=%s Error", strText.c_str());
		assert(false);
	}
	
	return bRes;
}

const char* CJsonSerialize::GetData()
{
	if (EnumSerializeIOWrite != m_iSerializeType)
	{
		Log("CJsonSerialize::GetData m_iSerializeType=%d Error", static_cast<int>(m_iSerializeType));
		assert(false);
	}
	CheckWriteToBuffer();
	return m_strBuffer.c_str();
}

suint32 CJsonSerialize::GetDataLen()
{
	if (EnumSerializeIOWrite != m_iSerializeType)
	{
		Log("CJsonSerialize::GetDataLen m_iSerializeType=%d Error", static_cast<int>(m_iSerializeType));
		assert(false);
	}
	CheckWriteToBuffer();
	return static_cast<suint32>(m_strBuffer.size());
}

bool CJsonSerialize::BeginSerializeStruct(const char *pstrName)
{
	bool bRes = false;

	do 
	{
		if (EnumSerializeIORead == m_iSerializeType)
		{
			if (nullptr == pstrName)
			{
				//do nothing
			}
			else
			{
				Json::Value NewValue = (*m_pCurValue)[pstrName];
				if (!NewValue.isObject())
				{
					Log("CJsonSerialize::BeginSerializeStruct NewValue Type=%d Error", static_cast<int>(NewValue.type()));
					assert(false);
					break;
				}
				m_StackValue.push(m_pCurValue);
				m_pCurValue.reset(new Json::Value(NewValue));
			}
		}
		else
		{
			if (nullptr == pstrName)
			{
				//���Ԫ��Ӧ��������
				assert(m_pCurValue->isNull());
				//����ǰ�ṹ�����ΪObject
				//���߼���BeginSerializeArrayItem��ʱ�򣬲�֪��������Ҫ���л��Ķ������ͣ�
				//����BeginSerializeArrayItem�ȴ�����һ��δ֪Ԫ�����ͣ���ʱ��Ҫ�������Ϊ����
				*m_pCurValue = Json::Value(Json::objectValue);
			}
			else
			{
				m_StackValue.push(m_pCurValue);
				m_pCurValue.reset(new Json::Value(Json::objectValue));
			}
		}
		bRes = true;
	} while (false);
	
	assert(bRes);
	return bRes;
}

bool CJsonSerialize::EndSerializeStruct(const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			assert(m_pCurValue->isObject());
			m_pCurValue = m_StackValue.top();
			m_StackValue.pop();
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			std::shared_ptr<Json::Value> pOldCurValue = m_StackValue.top();
			m_StackValue.pop();

			(*pOldCurValue)[pstrName] = *m_pCurValue;
			m_pCurValue = pOldCurValue;
		}
	}
	return true;
}

bool CJsonSerialize::BeginSerializeArray(suint32 &ulCount, const char *pstrName)
{
	bool bRes = false;

	do 
	{
		if (EnumSerializeIORead == m_iSerializeType)
		{
			if (nullptr == pstrName)
			{
				if (!m_pCurValue->isArray())
				{
					Log("CJsonSerialize::BeginSerializeArray isArray Type=%d Error", static_cast<int>(m_pCurValue->type()));
					assert(false);
					break;
				}

				ulCount = m_pCurValue->size();
			}
			else
			{
				Json::Value TempValue = (*m_pCurValue)[pstrName];
				if (!TempValue.isArray())
				{
					Log("CJsonSerialize::BeginSerializeArray TempValue Type=%d Error", static_cast<int>(TempValue.type()));
					assert(false);
					break;
				}
				ulCount = TempValue.size();
				m_StackValue.push(m_pCurValue);
				m_pCurValue.reset(new Json::Value(TempValue));
			}
		}
		else
		{
			if (nullptr == pstrName)
			{
				//���Ԫ��Ӧ��������
				assert(m_pCurValue->isNull());
				//����ǰ�ṹ�����Ϊarray
				//���߼���BeginSerializeArrayItem��ʱ�򣬲�֪��������Ҫ���л��Ķ������ͣ�
				//����BeginSerializeArrayItem�ȴ�����һ��δ֪Ԫ�����ͣ���ʱ��Ҫ�������Ϊ����
				*m_pCurValue = Json::Value(Json::arrayValue);
			}
			else
			{
				m_StackValue.push(m_pCurValue);
				m_pCurValue.reset(new Json::Value(Json::arrayValue));
			}
		}
		bRes = true;
	} while (false);
	
	assert(bRes);
	return bRes;
}

bool CJsonSerialize::EndSerializeArray(const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			assert(m_pCurValue->isArray());
			m_pCurValue = m_StackValue.top();
			m_StackValue.pop();
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			std::shared_ptr<Json::Value> pOldCurValue = m_StackValue.top();
			m_StackValue.pop();

			if (nullptr == pstrName)
			{
				//���Ԫ��Ӧ��������
				pOldCurValue->append(*m_pCurValue);
			}
			else
			{
				(*pOldCurValue)[pstrName] = *m_pCurValue;
			}
			m_pCurValue = pOldCurValue;
		}
	}
	return true;
}

bool CJsonSerialize::BeginSerializeArrayItem(suint32 ulIndex, const char *pstrName)
{
	bool bRes = false;

	do 
	{
		if (EnumSerializeIORead == m_iSerializeType)
		{
			if (!m_pCurValue->isArray())
			{
				Log("CJsonSerialize::BeginSerializeArrayItem isArray ulIndex=%u Type=%d Error", ulIndex, static_cast<int>(m_pCurValue->type()));
				assert(false);
				break;
			}
			if (ulIndex >= m_pCurValue->size())
			{
				Log("CJsonSerialize::BeginSerializeArrayItem ulIndex >= size ulIndex=%u size=%d Error", ulIndex, static_cast<int>(m_pCurValue->size()));
				assert(false);
				break;
			}
			Json::Value Item = (*m_pCurValue)[Json::ArrayIndex(ulIndex)];
			assert(!Item.isNull());
			m_StackValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(Item));
		}
		else
		{
			m_StackValue.push(m_pCurValue);
			//δ֪Ԫ������
			m_pCurValue.reset(new Json::Value());
		}
		bRes = true;
	} while (false);
	
	assert(bRes);
	return bRes;
}

bool CJsonSerialize::EndSerializeArrayItem(suint32 ulIndex, const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		m_pCurValue = m_StackValue.top();
		m_StackValue.pop();
		assert(m_pCurValue->isArray());
	}
	else
	{
		std::shared_ptr<Json::Value> pOldCurValue = m_StackValue.top();
		m_StackValue.pop();

		//���Ԫ��Ӧ��������
		pOldCurValue->append(*m_pCurValue);

		m_pCurValue = pOldCurValue;
	}
	return true;
}
/************************************************************************/
/* ���л��ֶκ���                                                         */
/************************************************************************/
bool CJsonSerialize::Serialize(bool & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(char & Value, const char * pstrName)
{
	//Jsonû��char ����int
	int iValue = Value;
	bool bRes = InnerSerialize(iValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(iValue);
	return bRes;
}

bool CJsonSerialize::Serialize(unsigned char & Value, const char * pstrName)
{
	//Jsonû��unsigned char ����unsigned int
	unsigned int uiValue = Value;
	bool bRes = InnerSerialize(uiValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(uiValue);
	return bRes;
}

bool CJsonSerialize::Serialize(short & Value, const char * pstrName)
{
	//Jsonû��short ����int��
	int iValue = Value;
	bool bRes = InnerSerialize(iValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(iValue);
	return bRes;
}

bool CJsonSerialize::Serialize(unsigned short & Value, const char * pstrName)
{
	//Jsonû��unsigned short ����unsigned int��
	unsigned int uiValue = Value;
	bool bRes = InnerSerialize(uiValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(uiValue);
	return bRes;
}

bool CJsonSerialize::Serialize(int& Value, const char *pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(unsigned int & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(long & Value, const char * pstrName)
{
	//Jsonû��long ����int��
	int iValue = Value;
	bool bRes = InnerSerialize(iValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(iValue);
	return bRes;
}

bool CJsonSerialize::Serialize(unsigned long & Value, const char * pstrName)
{
	//Jsonû��unsigned long ����unsigned int��
	unsigned int uiValue = Value;
	bool bRes = InnerSerialize(uiValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(uiValue);
	return bRes;
}

bool CJsonSerialize::Serialize(long long & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(unsigned long long & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(float & Value, const char * pstrName)
{
	//Jsonû��float ����double��
	double dValue = Value;
	bool bRes = InnerSerialize(dValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(dValue);
	return bRes;
}

bool CJsonSerialize::Serialize(double & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CJsonSerialize::Serialize(long double & Value, const char * pstrName)
{
	//Jsonû��long double ����double��
	double dValue = Value;
	bool bRes = InnerSerialize(dValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(dValue);
	return bRes;
}

bool CJsonSerialize::Serialize(CSerializeString& Value, const char *pstrName)
{
	return InnerSerialize(Value, pstrName);
}

void CJsonSerialize::CheckWriteToBuffer()
{
	if (!m_bHaveWriteToBuffer)
	{
		m_bHaveWriteToBuffer = true;
		Json::FastWriter w;
		m_strBuffer = w.write(*m_pRootValue);
	}
}

void CJsonSerialize::Log(const char * apFormat, ...)
{

}

std::string CJsonSerialize::ConvertToJson(const std::string &strText)
{
	std::string strResultText;
	switch (m_SerializeStringCode)
	{
	case EnumSerializeStringCodeNone:
	case EnumSerializeStringCodeUtf8:
		assert(CodeConvert::IsUtf8(strText));
		strResultText = strText;
		break;
	case EnumSerializeStringCodeBinary:
		strResultText = CodeConvert::Base64Encode(strText);
		break;
	case EnumSerializeStringCodeGB2312:
		strResultText = CodeConvert::GB2312ToUtf8(strText);
		break;
	default:
		strResultText = strText;
		assert(false);
		break;
	}
	return strResultText;
}

std::string CJsonSerialize::ConvertToLocal(const std::string & strText)
{
	std::string strResultText;
	switch (m_SerializeStringCode)
	{
	case EnumSerializeStringCodeNone:
	case EnumSerializeStringCodeUtf8:
		assert(CodeConvert::IsUtf8(strText));
		strResultText = strText;
		break;
	case EnumSerializeStringCodeBinary:
		strResultText = CodeConvert::Base64Decode(strText);
		break;
	case EnumSerializeStringCodeGB2312:
		strResultText = CodeConvert::Utf8ToGB2312(strText);
		break;
	default:
		strResultText = strText;
		assert(false);
		break;
	}
	return strResultText;
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, CSerializeString &Value, const char *pstrName)
{
	if (JsonValue.isString())
	{
		std::string strTempValue = ConvertToLocal(JsonValue.asString());

		Value.assign(strTempValue.data(), strTempValue.size());
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType string JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, bool &Value, const char *pstrName)
{
	if (JsonValue.isBool())
	{
		Value = JsonValue.asBool();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType bool JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, int &Value, const char *pstrName)
{
	if (JsonValue.isInt())
	{
		Value = JsonValue.asInt();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, unsigned int &Value, const char *pstrName)
{
	if (JsonValue.isUInt())
	{
		Value = JsonValue.asUInt();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType unsigned int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, long long &Value, const char *pstrName)
{
	if (JsonValue.isInt64())
	{
		Value = JsonValue.asInt64();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, unsigned long long &Value, const char *pstrName)
{
	if (JsonValue.isUInt64())
	{
		Value = JsonValue.asUInt64();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType unsigned long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

bool CJsonSerialize::ConverToType(Json::Value &JsonValue, double &Value, const char *pstrName)
{
	if (JsonValue.isDouble())
	{
		Value = JsonValue.asDouble();
		return true;
	}
	else
	{
		const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
		Log("CJsonSerialize::ConverToType double JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		assert(false);
		return false;
	}
}

Json::Value CJsonSerialize::ConverToJsonValue(CSerializeString &Value)
{
	std::string strTempValue(Value.data(), Value.size());
	strTempValue = ConvertToJson(strTempValue);
	return Json::Value(strTempValue);
}

Json::Value CJsonSerialize::ConverToJsonValue(bool &Value)
{
	return Json::Value(Value);
}

Json::Value CJsonSerialize::ConverToJsonValue(int &Value)
{
	return Json::Value(Value);
}

Json::Value CJsonSerialize::ConverToJsonValue(unsigned int &Value)
{
	return Json::Value(Value);
}

Json::Value CJsonSerialize::ConverToJsonValue(long long &Value)
{
	return Json::Value(Value);
}

Json::Value CJsonSerialize::ConverToJsonValue(unsigned long long &Value)
{
	return Json::Value(Value);
}

Json::Value CJsonSerialize::ConverToJsonValue(double &Value)
{
	return Json::Value(Value);
}

template<typename T>
bool CJsonSerialize::InnerSerialize(T &Value, const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		Json::Value JsonValue;
		if (nullptr == pstrName)
		{
			JsonValue = *m_pCurValue;
		}
		else
		{
			JsonValue = (*m_pCurValue)[pstrName];
		}
		return ConverToType(JsonValue, Value, pstrName);
	}
	else
	{
		if (nullptr == pstrName)
		{
			//���Ԫ��Ӧ��������
			m_pCurValue.reset(new Json::Value(ConverToJsonValue(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = ConverToJsonValue(Value);
		}
		return true;
	}
}

