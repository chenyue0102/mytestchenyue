#include "XmlSerialize.h"
#include <assert.h>
#include <algorithm>
#include "SerializeString.h"
#include "CodeConvert.h"

#define NULL_NAME		"item"			//没有名字节点的默认名字
#define ROOT_NAME		"root"			//root节点名字
#define ATTRIBUTE_NAME	"value"			//属性名字
CXmlSerialize::CXmlSerialize()
	: m_iSerializeType(EnumSerializeIONone)
	, m_XmlDocument()
	, m_pRootValue(nullptr)
	, m_pCurValue(nullptr)
	, m_StackValue()
	, m_strBuffer()
	, m_bHaveWriteToBuffer(false)
	, m_SerializeStringCode(EnumSerializeStringCodeNone)
{
	
}

CXmlSerialize::~CXmlSerialize()
{
}

bool CXmlSerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
	if (EnumSerializeIOWrite == m_iSerializeType)
	{
		assert(nullptr == m_pRootValue);
		TiXmlDeclaration *pXmlDeclaration = new TiXmlDeclaration("1.0", "utf-8", "");
		m_XmlDocument.LinkEndChild(pXmlDeclaration);
		m_pRootValue = new TiXmlElement(ROOT_NAME);
		m_XmlDocument.LinkEndChild(m_pRootValue);
		m_pCurValue = m_pRootValue;
	}
	return true;
}

EnumSerializeIO CXmlSerialize::GetSerializeType()
{
	return m_iSerializeType;
}

EnumSerializeFormat CXmlSerialize::GetSerializeFormat()
{
	return EnumSerializeFormatXml;
}

bool CXmlSerialize::SetSerializeStringCode(EnumSerializeStringCode SerializeStringCode)
{
	m_SerializeStringCode = SerializeStringCode;
	return true;
}

EnumSerializeStringCode CXmlSerialize::GetSerializeStringCode()
{
	return m_SerializeStringCode;
}

bool CXmlSerialize::SetData(const char * pstrText, suint32 ulDataLength)
{
	bool bRes = false;

	do
	{
		std::string strText(pstrText, ulDataLength);
		m_XmlDocument.Parse(strText.c_str(), nullptr, TIXML_ENCODING_UTF8);
		if (m_XmlDocument.Error())
		{
			assert(false);
			break;
		}
		auto pNode = m_XmlDocument.FirstChild();
		if (TiXmlNode::TINYXML_DECLARATION == pNode->Type())
		{
			TiXmlDeclaration *pDeclaration = static_cast<TiXmlDeclaration*>(pNode);
			const char *pstrEncoding = pDeclaration->Encoding();
			if (nullptr != pstrEncoding)
			{
				std::string strEncoding(pstrEncoding);
				std::transform(strEncoding.begin(), strEncoding.end(), strEncoding.begin(), &tolower);
				assert(strEncoding == "utf-8");
			}
		}
		if (nullptr == (m_pRootValue = m_XmlDocument.RootElement()))
		{
			assert(false);
			break;
		}
		m_pCurValue = m_pRootValue;
		bRes = true;
	} while (false);
	
	return bRes;
}

const char * CXmlSerialize::GetData()
{
	CheckWriteToBuffer();
	return m_strBuffer.data();
}

suint32 CXmlSerialize::GetDataLen()
{
	CheckWriteToBuffer();
	return static_cast<suint32>(m_strBuffer.size());
}

bool CXmlSerialize::BeginSerializeStruct(const char * pstrName)
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
				auto pElement = m_pCurValue->FirstChildElement(pstrName);
				if (nullptr == pElement)
				{
					Log("CJsonSerialize::BeginSerializeStruct Element(%s) Not Find Error", pstrName);
					assert(false);
					break;
				}

				m_StackValue.push(m_pCurValue);
				m_pCurValue = pElement;
			}
		}
		else
		{
			if (nullptr == pstrName)
			{
				//此逻辑是BeginSerializeArrayItem的时候，不知道接下来要序列化的东西类型，
				//所以BeginSerializeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
				m_pCurValue->SetValue(NULL_NAME);
			}
			else
			{
				TiXmlElement *pElement = new TiXmlElement(pstrName);
				m_pCurValue->LinkEndChild(pElement);
				m_StackValue.push(m_pCurValue);
				m_pCurValue = pElement;
			}
		}
		bRes = true;
	} while (false);

	assert(bRes);
	return bRes;
}

bool CXmlSerialize::EndSerializeStruct(const char * pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
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
			m_pCurValue = m_StackValue.top();
			m_StackValue.pop();
		}
	}
	return true;
}

bool CXmlSerialize::BeginSerializeArray(suint32 & ulCount, const char * pstrName)
{
	bool bRes = false;

	do 
	{
		if (EnumSerializeIORead == m_iSerializeType)
		{
			if (nullptr == pstrName)
			{
				ulCount = GetChildCount(m_pCurValue);
			}
			else
			{
				auto pElement = m_pCurValue->FirstChildElement(pstrName);
				if (nullptr == pElement)
				{
					Log("CXmlSerialize::BeginSerializeArray Element(%s) Not Find Error", pstrName);
					assert(false);
					break;
				}

				ulCount = GetChildCount(pElement);
				m_StackValue.push(m_pCurValue);
				m_pCurValue = pElement;
			}
		}
		else
		{
			if (nullptr == pstrName)
			{
				//这个元素应存入数组
				//将当前结构体调整为array
				//此逻辑是BeginSerializeArrayItem的时候，不知道接下来要序列化的东西类型，
				//所以BeginSerializeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
				m_pCurValue->SetValue(NULL_NAME);
			}
			else
			{
				TiXmlElement *pElement = new TiXmlElement(pstrName);
				m_pCurValue->LinkEndChild(pElement);
				m_StackValue.push(m_pCurValue);
				m_pCurValue = pElement;
			}
		}
		bRes = true;
	} while (false);

	assert(bRes);
	return bRes;
}

bool CXmlSerialize::EndSerializeArray(const char * pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		if (nullptr == pstrName)
		{
			//do nothing
		}
		else
		{
			m_pCurValue = m_StackValue.top();
			m_StackValue.pop();
		}
	}
	else
	{
		if (nullptr == pstrName)
		{

		}
		else
		{
			m_pCurValue = m_StackValue.top();
			m_StackValue.pop();
		}
	}
	return true;
}

bool CXmlSerialize::BeginSerializeArrayItem(suint32 ulIndex, const char * pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		TiXmlHandle XmlHandle(m_pCurValue);
		TiXmlHandle ChildXmlHandle = XmlHandle.Child(ulIndex);
		auto pElement = ChildXmlHandle.ToElement();
		if (nullptr == pElement)
		{
			assert(false);
			return false;
		}
		m_StackValue.push(m_pCurValue);
		m_pCurValue = pElement;
	}
	else
	{
		TiXmlElement *pElement = new TiXmlElement(NULL_NAME);
		m_pCurValue->LinkEndChild(pElement);
		m_StackValue.push(m_pCurValue);
		m_pCurValue = pElement;
	}
	return true;
}

bool CXmlSerialize::EndSerializeArrayItem(suint32 ulIndex, const char * pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		m_pCurValue = m_StackValue.top();
		m_StackValue.pop();
	}
	else
	{
		m_pCurValue = m_StackValue.top();
		m_StackValue.pop();
	}
	return true;
}
/************************************************************************/
/* 序列化字段函数                                                         */
/************************************************************************/
bool CXmlSerialize::Serialize(bool & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CXmlSerialize::Serialize(char & Value, const char * pstrName)
{
	long long llValue = Value;
	bool bRes = InnerSerialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
	return bRes;
}

bool CXmlSerialize::Serialize(unsigned char & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	bool bRes = InnerSerialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
	return bRes;
}

bool CXmlSerialize::Serialize(short & Value, const char * pstrName)
{
	long long llValue = Value;
	bool bRes = InnerSerialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
	return bRes;
}

bool CXmlSerialize::Serialize(unsigned short & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	bool bRes = InnerSerialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
	return bRes;
}

bool CXmlSerialize::Serialize(int & Value, const char * pstrName)
{
	long long llValue = Value;
	bool bRes = InnerSerialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
	return bRes;
}

bool CXmlSerialize::Serialize(unsigned int & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	bool bRes = InnerSerialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
	return bRes;
}

bool CXmlSerialize::Serialize(long & Value, const char * pstrName)
{
	long long llValue = Value;
	bool bRes = InnerSerialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
	return bRes;
}

bool CXmlSerialize::Serialize(unsigned long & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	bool bRes = InnerSerialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
	return bRes;
}

bool CXmlSerialize::Serialize(long long & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CXmlSerialize::Serialize(unsigned long long & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CXmlSerialize::Serialize(float & Value, const char * pstrName)
{
	long double ldValue = Value;
	bool bRes = InnerSerialize(ldValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ldValue);
	return bRes;
}

bool CXmlSerialize::Serialize(double & Value, const char * pstrName)
{
	long double ldValue = Value;
	bool bRes = InnerSerialize(ldValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ldValue);
	return bRes;
}

bool CXmlSerialize::Serialize(long double& Value, const char *pstrName)
{
	return InnerSerialize(Value, pstrName);
}

bool CXmlSerialize::Serialize(CSerializeString & Value, const char * pstrName)
{
	return InnerSerialize(Value, pstrName);
}

void CXmlSerialize::Log(const char * apFormat, ...)
{

}

int CXmlSerialize::GetChildCount(TiXmlElement * pElement)
{
	int nCount = 0;
	if (nullptr != pElement)
	{
		for (auto pChildElement = pElement->FirstChildElement();
			pChildElement != nullptr; pChildElement = pChildElement->NextSiblingElement(), nCount++);
	}
	else
	{
		assert(false);
	}
	return nCount;
}

void CXmlSerialize::CheckWriteToBuffer()
{
	if (!m_bHaveWriteToBuffer)
	{
		m_bHaveWriteToBuffer = true;
		TiXmlPrinter XmlPrinter;
		m_XmlDocument.Accept(&XmlPrinter);
		m_strBuffer = XmlPrinter.CStr();
	}
}

std::string CXmlSerialize::ConverToXml(const std::string &strText)
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

std::string CXmlSerialize::ConvertToLocal(const std::string &strText)
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

bool CXmlSerialize::ConverToType(const char *pstrValue, CSerializeString &Value)
{
	std::string strTempValue(ConvertToLocal(pstrValue));
	Value.assign(strTempValue.data(), strTempValue.size());
	return true;
}

bool CXmlSerialize::ConverToType(const char *pstrValue, bool &Value)
{
	if (0 == strcmp(pstrValue, "true"))
	{
		Value = true;
		return true;
	}
	else if (0 == strcmp(pstrValue, "false"))
	{
		Value = false;
		return true;
	}
	else
	{
		Log("CXmlSerialize::ConverToType bool Value(%s) Error", pstrValue);
		assert(false);
		return false;
	}
}

bool CXmlSerialize::ConverToType(const char *pstrValue, long long &Value)
{
	try
	{
		Value = std::stoll(pstrValue);
	}
	catch (...)
	{
		Log("CXmlSerialize::ConverToType long long %s Error", pstrValue);
		return false;
	}
	return true;
}

bool CXmlSerialize::ConverToType(const char *pstrValue, unsigned long long &Value)
{
	try
	{
		Value = std::stoull(pstrValue);
	}
	catch (...)
	{
		Log("CXmlSerialize::ConverToType unsigned long long %s Error", pstrValue);
		return false;
	}
	return true;
}

bool CXmlSerialize::ConverToType(const char *pstrValue, long double &Value)
{
	try
	{
		Value = std::stold(pstrValue);
	}
	catch (...)
	{
		Log("CXmlSerialize::ConverToType long double %s Error", pstrValue);
		return false;
	}
	return true;
}

std::string CXmlSerialize::ConverToString(CSerializeString &Value)
{
	std::string strTempValue(Value.data(), Value.size());
	strTempValue = ConverToXml(strTempValue);
	//xml序列化不支持中间截断
	assert(strTempValue.size() == strlen(strTempValue.c_str()));
	return strTempValue;
}

std::string CXmlSerialize::ConverToString(bool &Value)
{
	return (Value ? std::string("true") : std::string("false"));
}

std::string CXmlSerialize::ConverToString(long long &Value)
{
	return std::to_string(Value);
}

std::string CXmlSerialize::ConverToString(unsigned long long &Value)
{
	return std::to_string(Value);
}

std::string CXmlSerialize::ConverToString(long double &Value)
{
	return std::to_string(Value);
}

template<typename T>
bool CXmlSerialize::InnerSerialize(T &Value, const char *pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		TiXmlElement *pElement = nullptr;
		if (nullptr == pstrName)
		{
			pElement = m_pCurValue;
		}
		else
		{
			pElement = m_pCurValue->FirstChildElement(pstrName);
		}
		if (nullptr != pElement)
		{
			auto pstrValue = pElement->Attribute(ATTRIBUTE_NAME);
			if (nullptr != pstrValue)
			{
				return ConverToType(pstrValue, Value);
			}
		}
		return false;
	}
	else
	{
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->SetAttribute(ATTRIBUTE_NAME, ConverToString(Value).c_str());
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->SetAttribute(ATTRIBUTE_NAME, ConverToString(Value).c_str());
			m_pCurValue->LinkEndChild(pElement);
		}
		return true;
	}
}