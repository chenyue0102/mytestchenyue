#include "stdafx.h"
#include "XmlSerialize.h"
#include <assert.h>

#define NULL_NAME		"item"			//没有名字节点的默认名字
#define ROOT_NAME		"root"			//root节点名字
CXmlSerialize::CXmlSerialize()
	: m_iSerializationType(enum_Serialization_Type_Default)
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

void CXmlSerialize::SetSerializationType(ENUM_SERIALIZATION_TYPE iSerializationType)
{
	m_iSerializationType = iSerializationType;
	if (enum_Serialization_Type_Write == m_iSerializationType)
	{
		assert(nullptr == m_pRootValue);
		TiXmlDeclaration *pXmlDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "");
		m_XmlDocument.LinkEndChild(pXmlDeclaration);
		m_pRootValue = new TiXmlElement(ROOT_NAME);
		m_XmlDocument.LinkEndChild(m_pRootValue);
		m_pCurValue = m_pRootValue;
	}
}

ENUM_SERIALIZATION_TYPE CXmlSerialize::GetSerializationType()
{
	return m_iSerializationType;
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
		if (nullptr != m_XmlDocument.Parse(strText.c_str(), nullptr, TIXML_ENCODING_UTF8))
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

void CXmlSerialize::BeginSerlizeStruct(const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
				Log("CJsonSerialize::BeginSerlizeStruct Element(%s) Not Find Error", pstrName);
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
			//此逻辑是BeginSerlizeArrayItem的时候，不知道接下来要序列化的东西类型，
			//所以BeginSerlizeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
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

void CXmlSerialize::EndSerlizeStruct(const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
			auto pOldCurValue = m_StackValue.top();
			m_StackValue.pop();

			//BeginSerlizeStruct已经LinkEndChild了
			m_pCurValue = pOldCurValue;
		}
	}
}

void CXmlSerialize::BeginSerlizeArray(unsigned long & ulCount, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
				Log("CXmlSerialize::BeginSerlizeArray Element(%s) Not Find Error", pstrName);
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
			//此逻辑是BeginSerlizeArrayItem的时候，不知道接下来要序列化的东西类型，
			//所以BeginSerlizeArrayItem先创建了一个未知元素类型，此时需要将其调整为数组
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

void CXmlSerialize::EndSerlizeArray(const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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

void CXmlSerialize::BeginSerlizeArrayItem(unsigned long ulIndex, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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

void CXmlSerialize::EndSerlizeArrayItem(unsigned long ulIndex, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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

void CXmlSerialize::Serialization(unsigned char & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialization(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialization(bool & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
					Log("CXmlSerialize::Serialization bool Value(%s) Error", pstrValue);
					assert(false);
				}
			}
			else
			{
				Log("CXmlSerialize::Serialization bool GetText Error");
				assert(false);
			}
		}
		else
		{
			Log("CXmlSerialize::Serialization bool pElement == nullptr Error");
			assert(false);
		}
	}
	else
	{
		const char *pstrValue = nullptr;
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

void CXmlSerialize::Serialization(short & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialization(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialization(unsigned short & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialization(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialization(int & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialization(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialization(unsigned int & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialization(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialization(long & Value, const char * pstrName)
{
	long long llValue = Value;
	Serialization(llValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(llValue);
}

void CXmlSerialize::Serialization(unsigned long & Value, const char * pstrName)
{
	unsigned long long ullValue = Value;
	Serialization(ullValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(ullValue);
}

void CXmlSerialize::Serialization(long long & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
		const char *pstrValue = nullptr;
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

void CXmlSerialize::Serialization(unsigned long long & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
		const char *pstrValue = nullptr;
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

void CXmlSerialize::Serialization(float & Value, const char * pstrName)
{
	double dValue = Value;
	Serialization(dValue, pstrName);
	Value = static_cast<std::remove_reference<decltype(Value)>::type>(dValue);
}

void CXmlSerialize::Serialization(double & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
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
				Value = std::stod(pstrValue);
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
		const char *pstrValue = nullptr;
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

void CXmlSerialize::Serialization(std::string & Value, const char * pstrName)
{
	if (enum_Serialization_Type_Read == m_iSerializationType)
	{
		if (nullptr == pstrName)
		{

		}
		else
		{
			auto pElement = m_pCurValue->FirstChildElement(pstrName);
			if (nullptr != pElement)
			{
				auto pstrValue = pElement->GetText();
				if (nullptr != pstrValue)
				{
					Value = pstrValue;
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
	}
	else
	{
		const char *pstrValue = nullptr;
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
