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

void CJsonSerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
	if (!(EnumSerializeIORead == m_iSerializeType || EnumSerializeIOWrite == m_iSerializeType))
	{
		Log("CJsonSerialize::SetSerializeType iSerializeType=%d Error", static_cast<int>(iSerializeType));
		assert(false);
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

void CJsonSerialize::SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)
{
	m_SerializeStringCode = SerializeStringCode;
}

EnumSerializeStringCode CJsonSerialize::GetSerializeStringCode()
{
	return m_SerializeStringCode;
}

bool CJsonSerialize::SetData(const char *pstrText, unsigned long ulDataLength)
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

unsigned long CJsonSerialize::GetDataLen()
{
	if (EnumSerializeIOWrite != m_iSerializeType)
	{
		Log("CJsonSerialize::GetDataLen m_iSerializeType=%d Error", static_cast<int>(m_iSerializeType));
		assert(false);
	}
	CheckWriteToBuffer();
	return static_cast<unsigned long>(m_strBuffer.size());
}

void CJsonSerialize::BeginSerializeStruct(const char *pstrName)
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
				throw - 1;
			}
			m_StackValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(NewValue));
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			assert(m_pCurValue->isNull());
			//将当前结构体调整为Object
			//此逻辑是BeginSerializeArrayItem的时候，不知道接下来要序列化的东西类型，
			//所以BeginSerializeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
			*m_pCurValue = Json::Value(Json::objectValue);
		}
		else
		{
			m_StackValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(Json::objectValue));
		}
	}
}

void CJsonSerialize::EndSerializeStruct(const char *pstrName)
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
}

void CJsonSerialize::BeginSerializeArray(unsigned long &ulCount, const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (nullptr == pstrName)
		{
			if (!m_pCurValue->isArray())
			{
				Log("CJsonSerialize::BeginSerializeArray isArray Type=%d Error", static_cast<int>(m_pCurValue->type()));
				assert(false);
				throw (-1);
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
				throw (-1);
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
			//这个元素应存入数组
			assert(m_pCurValue->isNull());
			//将当前结构体调整为array
			//此逻辑是BeginSerializeArrayItem的时候，不知道接下来要序列化的东西类型，
			//所以BeginSerializeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
			*m_pCurValue = Json::Value(Json::arrayValue);
		}
		else
		{
			m_StackValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(Json::arrayValue));
		}
	}
}

void CJsonSerialize::EndSerializeArray(const char *pstrName)
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
				//这个元素应存入数组
				pOldCurValue->append(*m_pCurValue);
			}
			else
			{
				(*pOldCurValue)[pstrName] = *m_pCurValue;
			}
			m_pCurValue = pOldCurValue;
		}
	}
}

void CJsonSerialize::BeginSerializeArrayItem(unsigned long ulIndex, const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (!m_pCurValue->isArray())
		{
			Log("CJsonSerialize::BeginSerializeArrayItem isArray ulIndex=%u Type=%d Error", ulIndex, static_cast<int>(m_pCurValue->type()));
			assert(false);
			throw (-1);
		}
		if (ulIndex >= m_pCurValue->size())
		{
			Log("CJsonSerialize::BeginSerializeArrayItem ulIndex >= size ulIndex=%u size=%d Error", ulIndex, static_cast<int>(m_pCurValue->size()));
			assert(false);
			throw (-1);
		}
		Json::Value Item = (*m_pCurValue)[Json::ArrayIndex(ulIndex)];
		assert(!Item.isNull());
		m_StackValue.push(m_pCurValue);
		m_pCurValue.reset(new Json::Value(Item));
	}
	else
	{
		m_StackValue.push(m_pCurValue);
		//未知元素类型
		m_pCurValue.reset(new Json::Value());
	}
}

void CJsonSerialize::EndSerializeArrayItem(unsigned long ulIndex, const char *pstrName)
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

		//这个元素应存入数组
		pOldCurValue->append(*m_pCurValue);

		m_pCurValue = pOldCurValue;
	}
}

void CJsonSerialize::Serialize(bool & Value, const char * pstrName)
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
		if (JsonValue.isBool())
		{
			Value = JsonValue.asBool();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize bool JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(char & Value, const char * pstrName)
{
	//Json没有unsigned char 当作unsigned int，
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
		if (JsonValue.isString())
		{
			std::string strValue = JsonValue.asString();
			if (1 == strValue.size())
			{
				Value = strValue[0];
			}
			else
			{
				const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
				Log("CJsonSerialize::Serialize char JsonValue Length != 1 name=%s Error", pLogName);
				assert(false);
			}
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize char JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}

	}
	else
	{
		char szValue[] = { Value, '\0'};
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(szValue));
		}
		else
		{
			(*m_pCurValue)[pstrName] = szValue;
		}
	}
}

void CJsonSerialize::Serialize(unsigned char & Value, const char * pstrName)
{
	//Json没有unsigned char 当作unsigned int，
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
		if (JsonValue.isUInt())
		{
			Value = JsonValue.asUInt();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize unsigned char JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
		
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<unsigned int>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<unsigned int>(Value);
		}
	}
}

void CJsonSerialize::Serialize(short & Value, const char * pstrName)
{
	//Json没有short 当作int，
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
		if (JsonValue.isInt())
		{
			Value = static_cast<short>(JsonValue.asInt());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize short JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<int>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<int>(Value);
		}
	}
}

void CJsonSerialize::Serialize(unsigned short & Value, const char * pstrName)
{
	//Json没有unsigned short 当作unsigned int，
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
		if (JsonValue.isUInt())
		{
			Value = static_cast<unsigned short>(JsonValue.asUInt());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize unsigned short JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<unsigned int>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<unsigned int>(Value);
		}
	}
}

void CJsonSerialize::Serialize(int& Value, const char *pstrName)
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
		if (JsonValue.isInt())
		{
			Value = JsonValue.asInt();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(unsigned int & Value, const char * pstrName)
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
		if (JsonValue.isUInt())
		{
			Value = JsonValue.asUInt();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize unsigned int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(long & Value, const char * pstrName)
{
	//Json没有long 当作int，
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
		if (JsonValue.isInt())
		{
			Value = static_cast<long>(JsonValue.asInt());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<int>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<int>(Value);
		}
	}
}

void CJsonSerialize::Serialize(unsigned long & Value, const char * pstrName)
{
	//Json没有unsigned long 当作unsigned int，
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
		if (JsonValue.isUInt())
		{
			Value = static_cast<unsigned long>(JsonValue.asUInt());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize unsigned long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<unsigned int>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<unsigned int>(Value);
		}
	}
}

void CJsonSerialize::Serialize(long long & Value, const char * pstrName)
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
		if (JsonValue.isInt64())
		{
			Value = JsonValue.asInt64();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(unsigned long long & Value, const char * pstrName)
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
		if (JsonValue.isUInt64())
		{
			Value = JsonValue.asUInt64();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize unsigned long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(float & Value, const char * pstrName)
{
	//Json没有float 当作double，
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
		if (JsonValue.isDouble())
		{
			Value = static_cast<float>(JsonValue.asDouble());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize float JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<double>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<double>(Value);
		}
	}
}

void CJsonSerialize::Serialize(double & Value, const char * pstrName)
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
		if (JsonValue.isDouble())
		{
			Value = JsonValue.asDouble();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize double JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(Value));
		}
		else
		{
			(*m_pCurValue)[pstrName] = Value;
		}
	}
}

void CJsonSerialize::Serialize(long double & Value, const char * pstrName)
{
	//Json没有long double 当作double，
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
		if (JsonValue.isDouble())
		{
			Value = static_cast<long double>(JsonValue.asDouble());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize long double JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
			assert(false);
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(static_cast<double>(Value)));
		}
		else
		{
			(*m_pCurValue)[pstrName] = static_cast<double>(Value);
		}
	}
}

void CJsonSerialize::Serialize(CSerializeString& Value, const char *pstrName)
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
		if (JsonValue.isString())
		{
			std::string strTempValue = ConvertToLocal(JsonValue.asString());

			Value.assign(strTempValue.data(), strTempValue.size());
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialize string JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
		}
	}
	else
	{
		std::string strTempValue(Value.data(), Value.size());
		strTempValue = ConvertToJson(strTempValue);
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			m_pCurValue.reset(new Json::Value(strTempValue));
		}
		else
		{
			(*m_pCurValue)[pstrName] = strTempValue;
		}
	}
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
	case EnumSerializeStringCodeGB2312:
		strResultText = CodeConvert::GB2312ToUtf8(strText);
		break;
	case EnumSerializeStringCodeUtf8:
		strResultText = strText;
		break;
	case EnumSerializeStringCodeBinary:
		strResultText = strText;
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
	case EnumSerializeStringCodeGB2312:
		strResultText = CodeConvert::Utf8ToGB2312(strText);
		break;
	case EnumSerializeStringCodeUtf8:
		strResultText = strText;
		break;
	case EnumSerializeStringCodeBinary:
		strResultText = strText;
		break;
	default:
		strResultText = strText;
		assert(false);
		break;
	}
	return strResultText;
}
