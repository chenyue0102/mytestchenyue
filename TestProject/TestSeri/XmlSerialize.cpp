#include "XmlSerialize.h"
#include <assert.h>

#define NULL_NAME		"item"			//没有名字节点的默认名字
#define ROOT_NAME		"root"			//root节点名字
CXmlSerialize::CXmlSerialize()
	: m_iSerializeType(EnumSerializeIONone)
	, m_XmlDocument()
	, m_pRootValue(nullptr)
	, m_pCurValue(nullptr)
	, m_StackValue()
	, m_strBuffer()
	, m_bHaveWriteToBuffer(false)
{
	
}

CXmlSerialize::~CXmlSerialize()
{
}

void CXmlSerialize::SetSerializeType(EnumSerializeIO iSerializeType)
{
	m_iSerializeType = iSerializeType;
	if (EnumSerializeIOWrite == m_iSerializeType)
	{
		assert(nullptr == m_pRootValue);
		TiXmlDeclaration *pXmlDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "");
		m_XmlDocument.LinkEndChild(pXmlDeclaration);
		m_pRootValue = new TiXmlElement(ROOT_NAME);
		m_XmlDocument.LinkEndChild(m_pRootValue);
		m_pCurValue = m_pRootValue;
	}
}

EnumSerializeIO CXmlSerialize::GetSerializeType()
{
	return m_iSerializeType;
}

EnumSerializeFormat CXmlSerialize::GetSerializeFormat()
{
	return EnumSerializeFormatXml;
}

bool CXmlSerialize::SetData(const char * pstrText, unsigned long ulDataLength)
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

unsigned long CXmlSerialize::GetDataLen()
{
	CheckWriteToBuffer();
	return static_cast<unsigned long>(m_strBuffer.size());
}

void CXmlSerialize::BeginSerializeStruct(const char * pstrName)
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
				throw - 1;
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
}

void CXmlSerialize::EndSerializeStruct(const char * pstrName)
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
}

void CXmlSerialize::BeginSerializeArray(unsigned long & ulCount, const char * pstrName)
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
				throw (-1);
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
}

void CXmlSerialize::EndSerializeArray(const char * pstrName)
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
}

void CXmlSerialize::BeginSerializeArrayItem(unsigned long ulIndex, const char * pstrName)
{
	if (EnumSerializeIORead == m_iSerializeType)
	{
		TiXmlHandle XmlHandle(m_pCurValue);
		TiXmlHandle ChildXmlHandle = XmlHandle.Child(ulIndex);
		auto pElement = ChildXmlHandle.ToElement();
		if (nullptr == pElement)
		{
			assert(false);
			throw - 1;
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
}

void CXmlSerialize::EndSerializeArrayItem(unsigned long ulIndex, const char * pstrName)
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
}
/************************************************************************/
/* 序列化字段函数                                                         */
/************************************************************************/
void CXmlSerialize::Serialize(bool & Value, const char * pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue)
			{
				if (0 == strcmp(pstrValue, "true"))
				{
					Value = true;
				}
				else if (0 == strcmp(pstrValue, "false"))
				{
					Value = false;
				}
				else
				{
					Log("CXmlSerialize::Serialize bool Value(%s) Error", pstrValue);
					assert(false);
				}
			}
			else
			{
				Log("CXmlSerialize::Serialize bool GetText Error");
				assert(false);
			}
		}
		else
		{
			Log("CXmlSerialize::Serialize bool pElement == nullptr Error");
			assert(false);
		}
	}
	else
	{
		TiXmlText *pXmlText = new TiXmlText(Value ? "true" : "false");
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
}

void CXmlSerialize::Serialize(char & Value, const char * pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue
				&& 1 == strlen(pstrValue))
			{
				Value = pstrValue[0];
			}
			else
			{
				Log("CXmlSerialize::Serialize char GetText Error");
				assert(false);
			}
		}
		else
		{
			Log("CXmlSerialize::Serialize char pElement == nullptr Error");
			assert(false);
		}
	}
	else
	{
		char szText[] = {Value, '\0'};
		TiXmlText *pXmlText = new TiXmlText(szText);
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
}

void CXmlSerialize::Serialize(unsigned char & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialize(short & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialize(unsigned short & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialize(int & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialize(unsigned int & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialize(long & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialize(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialize(unsigned long & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialize(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialize(long long & Value, const char * pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue)
			{
				Value = std::stoll(pstrValue);
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		TiXmlText *pXmlText = new TiXmlText(std::to_string(Value).c_str());
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
}

void CXmlSerialize::Serialize(unsigned long long & Value, const char * pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue)
			{
				Value = std::stoull(pstrValue);
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		TiXmlText *pXmlText = new TiXmlText(std::to_string(Value).c_str());
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
}

void CXmlSerialize::Serialize(float & Value, const char * pstrName)
{
	long double ldValue = Value;
	Serialize(ldValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ldValue);
}

void CXmlSerialize::Serialize(double & Value, const char * pstrName)
{
	long double ldValue = Value;
	Serialize(ldValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ldValue);
}

void CXmlSerialize::Serialize(long double& Value, const char *pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue)
			{
				Value = std::stold(pstrValue);
			}
			else
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		TiXmlText *pXmlText = new TiXmlText(std::to_string(Value).c_str());
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
}

void CXmlSerialize::Serialize(std::string & Value, const char * pstrName)
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
			auto pstrValue = pElement->GetText();
			if (nullptr != pstrValue)
			{
				Value = pstrValue;
			}
			else
			{
				//字符串为空
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		//xml序列化不支持中间截断
		assert(Value.size() == strlen(Value.c_str()));
		TiXmlText *pXmlText = new TiXmlText(Value.c_str());
		if (nullptr == pstrName)
		{
			m_pCurValue->SetValue(NULL_NAME);
			m_pCurValue->LinkEndChild(pXmlText);
		}
		else
		{
			TiXmlElement *pElement = new TiXmlElement(pstrName);
			pElement->LinkEndChild(pXmlText);
			m_pCurValue->LinkEndChild(pElement);
		}
	}
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
