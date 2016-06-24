#include "JsonSerialize.h"
#include <cassert>

CJsonSerialize::CJsonSerialize()
	: m_iSerializationType(enum_Serialization_Type_Default)
	, m_pRootValue(new Json::Value(Json::objectValue))
	, m_pCurValue(nullptr)
	, m_StackJsonValue()
	, m_bHaveWriteToBuffer(false)
{
	m_pCurValue = m_pRootValue;
}

CJsonSerialize::~CJsonSerialize()
{

}

void CJsonSerialize::SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)
{
	m_iSerializationType = iSerializationType;
	if (!(enum_Serialization_Type_Read == m_iSerializationType || enum_Serialization_Type_Write == m_iSerializationType))
	{
		Log("CJsonSerialize::SetSerializationType iSerializationType=%d Error", static_cast<int>(iSerializationType));
		assert(false);
	}
}

ENUM_SERIALIZATION_TYPE CJsonSerialize::GetSerializationType()
{
	if (!(enum_Serialization_Type_Read == m_iSerializationType || enum_Serialization_Type_Write == m_iSerializationType))
	{
		Log("CJsonSerialize::GetSerializationType m_iSerializationType=%d Error", static_cast<int>(m_iSerializationType));
		assert(false);
	}
	return m_iSerializationType;
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
	if (enum_Serialization_Type_Write != m_iSerializationType)
	{
		Log("CJsonSerialize::GetData m_iSerializationType=%d Error", static_cast<int>(m_iSerializationType));
		assert(false);
	}
	CheckWriteToBuffer();
	return m_strBuffer.c_str();
}

unsigned long CJsonSerialize::GetDataLen()
{
	if (enum_Serialization_Type_Write != m_iSerializationType)
	{
		Log("CJsonSerialize::GetDataLen m_iSerializationType=%d Error", static_cast<int>(m_iSerializationType));
		assert(false);
	}
	CheckWriteToBuffer();
	return static_cast<unsigned long>(m_strBuffer.size());
}

void CJsonSerialize::BeginSerlizeStruct(const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
				Log("CJsonSerialize::BeginSerlizeStruct NewValue Type=%d Error", static_cast<int>(NewValue.type()));
				assert(false);
				throw - 1;
			}
			m_StackJsonValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(NewValue));
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			assert(m_pCurValue->isNull());
			//将当前结构体调整为Object，结束的时候，再置回去
			m_pCurValue.reset(new Json::Value(Json::objectValue));
		}
		else
		{
			m_StackJsonValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(Json::objectValue));
		}
	}
}

void CJsonSerialize::EndSerlizeStruct(const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			assert(m_pCurValue->isObject());
			m_pCurValue = m_StackJsonValue.top();
			m_StackJsonValue.pop();
		}
	}
	else
	{
		if (nullptr == pstrName)
		{

		}
		else
		{
			std::shared_ptr<Json::Value> pOldCurValue = m_StackJsonValue.top();
			m_StackJsonValue.pop();

			(*pOldCurValue)[pstrName] = *m_pCurValue;
			m_pCurValue = pOldCurValue;
		}
	}
}

void CJsonSerialize::BeginSerlizeArray(unsigned long &ulCount, const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		if (nullptr == pstrName)
		{
			if (!m_pCurValue->isArray())
			{
				Log("CJsonSerialize::BeginSerlizeArray isArray Type=%d Error", static_cast<int>(m_pCurValue->type()));
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
				Log("CJsonSerialize::BeginSerlizeArray TempValue Type=%d Error", static_cast<int>(TempValue.type()));
				assert(false);
				throw (-1);
			}
			ulCount = TempValue.size();
			m_StackJsonValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(TempValue));
		}
	}
	else
	{
		if (nullptr == pstrName)
		{
			//这个元素应存入数组
			assert(m_pCurValue->isNull());
			//将当前结构体调整为array，结束的时候，再置回去
			m_pCurValue.reset(new Json::Value(Json::arrayValue));
		}
		else
		{
			m_StackJsonValue.push(m_pCurValue);
			m_pCurValue.reset(new Json::Value(Json::arrayValue));
		}
	}
}

void CJsonSerialize::EndSerlizeArray(const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			assert(m_pCurValue->isArray());
			m_pCurValue = m_StackJsonValue.top();
			m_StackJsonValue.pop();
		}
	}
	else
	{
		if (nullptr == pstrName)
		{

		}
		else
		{
			std::shared_ptr<Json::Value> pOldCurValue = m_StackJsonValue.top();
			m_StackJsonValue.pop();

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

void CJsonSerialize::BeginSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		if (!m_pCurValue->isArray())
		{
			Log("CJsonSerialize::BeginSerlizeArrayItem isArray ulIndex=%u Type=%d Error", ulIndex, static_cast<int>(m_pCurValue->type()));
			assert(false);
			throw (-1);
		}
		if (ulIndex >= m_pCurValue->size())
		{
			Log("CJsonSerialize::BeginSerlizeArrayItem ulIndex >= size ulIndex=%u size=%d Error", ulIndex, static_cast<int>(m_pCurValue->size()));
			assert(false);
			throw (-1);
		}
		Json::Value Item = (*m_pCurValue)[Json::ArrayIndex(ulIndex)];
		assert(!Item.isNull());
		m_StackJsonValue.push(m_pCurValue);
		m_pCurValue.reset(new Json::Value(Item));
	}
	else
	{
		m_StackJsonValue.push(m_pCurValue);
		//未知元素类型
		m_pCurValue.reset(new Json::Value());
	}
}

void CJsonSerialize::EndSerlizeArrayItem(unsigned long ulIndex, const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		m_pCurValue = m_StackJsonValue.top();
		m_StackJsonValue.pop();
		assert(m_pCurValue->isArray());
	}
	else
	{
		std::shared_ptr<Json::Value> pOldCurValue = m_StackJsonValue.top();
		m_StackJsonValue.pop();

		//这个元素应存入数组
		pOldCurValue->append(*m_pCurValue);

		m_pCurValue = pOldCurValue;
	}
}

void CJsonSerialize::Serialization(unsigned char & Value, const char * pstrName)
{
	//Json没有unsigned char 当作unsigned int，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization unsigned char JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(bool & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization bool JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(short & Value, const char * pstrName)
{
	//Json没有short 当作int，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization short JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(unsigned short & Value, const char * pstrName)
{
	//Json没有unsigned short 当作unsigned int，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization unsigned short JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(int& Value, const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(unsigned int & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization unsigned int JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(long & Value, const char * pstrName)
{
	//Json没有long 当作int，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(unsigned long & Value, const char * pstrName)
{
	//Json没有unsigned long 当作unsigned int，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization unsigned long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(long long & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(unsigned long long & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization unsigned long long JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(float & Value, const char * pstrName)
{
	//Json没有float 当作double，
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization float JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(double & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Log("CJsonSerialize::Serialization double JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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

void CJsonSerialize::Serialization(std::string& Value, const char *pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			Value = JsonValue.asString();
		}
		else
		{
			const char *pLogName = (nullptr == pstrName) ? "nullptr" : pstrName;
			Log("CJsonSerialize::Serialization string JsonValue Type=%d name=%s Error", static_cast<int>(JsonValue.type()), pLogName);
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
