#include "StdAfx.h"
#include "XmlTranslate.h"
#include <boost/format.hpp>
#include "Markup.h"
#include "ConfigNode.h"


CXmlTranslate::CXmlTranslate(void)
	: m_dwDepth(0)
{
	m_strXmlDepthText.resize(MAX_XML_DEPTH);
}


CXmlTranslate::~CXmlTranslate(void)
{
}

BOOL	CXmlTranslate::ToXml(char *pBuffer, DWORD dwLen, std::string &strXml)
{
	m_dwDepth = 0;
	m_strXmlDepthText[m_dwDepth] = "<?xml version=\"1.0\" encoding=\"gb2312\" standalone=\"yes\" ?>\r\n";
	m_strXmlDepthText[m_dwDepth] += "<root>\r\n";

	CSerialization Seri(pBuffer, dwLen);
	Seri.SetSerializationType(enum_Serialization_Type_Read);
	ParseOneField(Seri);
	m_strXmlDepthText[m_dwDepth] += m_strXmlDepthText[m_dwDepth + 1];
	m_strXmlDepthText[m_dwDepth] += "</root>";

	strXml = m_strXmlDepthText[0];
	return TRUE;
}

BOOL	CXmlTranslate::ParseOneField(CSerialization &GlobalSeri)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth], strTempText;
	strCurDepthText.clear();

	char *pCurFieldBegin = GlobalSeri.GetData() + GlobalSeri.GetDataLen();
	DWORD dwCurDataOffset = GlobalSeri.GetDataLen();
	XmlSerializationHead Head;
	Head.Serialization(GlobalSeri);

	DWORD dwInfoOffset = sizeof(Head) + Head.dwDataLen;
	DWORD dwInfoLen = GlobalSeri.GetBufferLen() - dwCurDataOffset - sizeof(Head) - Head.dwDataLen;
	XmlSerializationInfoArray InfoArray;


	ParseFieldInfo(pCurFieldBegin + dwInfoOffset, dwInfoLen, InfoArray);

	std::string strFormatNormalText("<%1% type=\"%2%\">%3%</%1%>\r\n");
	for (XmlSerializationInfoArray::iterator itorInfo = InfoArray.begin(); itorInfo != InfoArray.end(); ++itorInfo)
	{
		XmlSerializationInfo &Info = *itorInfo;
		char *pField = pCurFieldBegin + Info.dwOffset;
		CSerialization TempSeri(pField, Info.dwLen);
		TempSeri.SetSerializationType(enum_Serialization_Type_Read);


		strTempText.clear();
		AppendTabString(strTempText);
		switch (Info.dwType)
		{
		case XmlFieldTypeBool:
			{
				assert(sizeof(bool) == Info.dwLen);
				bool bValue = true;
				TempSeri.Serialization(bValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType 
					% (bValue ? "1" : "0")).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeChar:
			{
				assert(sizeof(char) == Info.dwLen);
				char c = 0;
				TempSeri.Serialization(c);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% static_cast<int>(c)).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeShort:
			{
				assert(sizeof(short) == Info.dwLen);
				short s = 0;
				TempSeri.Serialization(s);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% s).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeInt:
			{
				assert(sizeof(int) == Info.dwLen);
				int nValue = 0;
				TempSeri.Serialization(nValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% nValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeLong:
			{
				assert(sizeof(long) == Info.dwLen);
				long nValue = 0;
				TempSeri.Serialization(nValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% nValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeFloat:
			{
				assert(sizeof(float) == Info.dwLen);
				float fValue = 0.0;
				TempSeri.Serialization(fValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% fValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeDouble:
			{
				assert(sizeof(double) == Info.dwLen);
				double dValue = 0.0;
				TempSeri.Serialization(dValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% dValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeString:
			{
				std::string str;
				TempSeri.Serialization(str);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% str).str();
				strCurDepthText += strTempText;
				//增加关键字转换
			}
			break;
		case XmlFieldTypeUChar:
			{
				assert(sizeof(unsigned char) == Info.dwLen);
				unsigned char uc = 0;
				TempSeri.Serialization(uc);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% static_cast<unsigned int>(uc)).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeUShort:
			{
				assert(sizeof(unsigned short) == Info.dwLen);
				unsigned short us = 0;
				TempSeri.Serialization(us);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% us).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeUInt:
			{
				assert(sizeof(unsigned int) == Info.dwLen);
				unsigned int uiValue = 0;
				TempSeri.Serialization(uiValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% uiValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeULong:
			{
				assert(sizeof(unsigned long) == Info.dwLen);
				unsigned long ulValue = 0;
				TempSeri.Serialization(ulValue);
				
				strTempText += (boost::format(strFormatNormalText) % Info.strName.c_str() % Info.dwType
					% ulValue).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeStruct:
			{
				strTempText += (boost::format("<%1% type=\"%2%\">\r\n") % Info.strName.c_str() % Info.dwType).str();
				ParseOneField(TempSeri);
				strTempText += m_strXmlDepthText[m_dwDepth + 1];
				AppendTabString(strTempText);
				strTempText += (boost::format("</%1%>\r\n") % Info.strName.c_str()).str();
				strCurDepthText += strTempText;
			}
			break;
		case XmlFieldTypeVector:
			{
				if (Info.dwChildType < XmlFieldTypeStruct)	//是基本数据的数组
				{
					strTempText += (boost::format("<%1% type=\"%2%\" childtype=\"%3%\">\r\n") % Info.strName.c_str() % Info.dwType
						% Info.dwChildType).str();

					DWORD dwVectorSize = 0;
					TempSeri.Serialization(dwVectorSize);

					for (DWORD dwVecotrIndex = 0; dwVecotrIndex < dwVectorSize; dwVecotrIndex++)
					{
						ParseBaseValue(TempSeri, Info.dwChildType);
						strTempText += m_strXmlDepthText[m_dwDepth + 1];
					}
									
					AppendTabString(strTempText);
					strTempText += (boost::format("</%1%>\r\n") % Info.strName.c_str()).str();
					strCurDepthText += strTempText;
				}
				else if (XmlFieldTypeStruct == Info.dwChildType)
				{
					strTempText += (boost::format("<%1% type=\"%2%\" childtype=\"%3%\">\r\n") % Info.strName.c_str()
						% Info.dwType % Info.dwChildType).str();

					DWORD dwVectorSize = 0;
					TempSeri.Serialization(dwVectorSize);

					for (DWORD dwVecotrIndex = 0; dwVecotrIndex < dwVectorSize; dwVecotrIndex++)
					{
						ParseStructValue(TempSeri);
						strTempText += m_strXmlDepthText[m_dwDepth + 1];
					}

					AppendTabString(strTempText);
					strTempText += (boost::format("</%1%>\r\n") % Info.strName.c_str()).str();
					strCurDepthText += strTempText;
				}
				else
				{
					assert(false);	//列表成员数据只允许是基本变量和结构体，不允许再次包含列表
				}
				
			}
			break;
		case XmlFieldTypeMap:
			{
				strTempText += (boost::format("<%1% type=\"%2%\" childtype=\"%3%\" childtype2=\"%4%\">\r\n") % Info.strName.c_str() % Info.dwType
					% Info.dwChildType % Info.dwChildType2).str();

				DWORD dwMapSize = 0;
				TempSeri.Serialization(dwMapSize);
				for (DWORD dwMapIndex = 0; dwMapIndex < dwMapSize; dwMapIndex++)
				{
					ParseMapInfo(TempSeri, Info);
					strTempText += m_strXmlDepthText[m_dwDepth + 1];
				}
				AppendTabString(strTempText);
				strTempText += (boost::format("</%1%>\r\n") % Info.strName.c_str()).str();
				strCurDepthText += strTempText;
			}
			break;
		default:
			{
				assert(FALSE);
			}
			break;
		}
	}

	GlobalSeri.m_dwDataLen = dwCurDataOffset + Head.dwSectionLen;
	m_dwDepth--;
	return TRUE;
}

BOOL	CXmlTranslate::ParseMapInfo(CSerialization &GlobalSeri, XmlSerializationInfo &Info)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth], strTempText;
	strCurDepthText.clear();

	AppendTabString(strTempText);
	strTempText += "<";
	strTempText += CHILD_NAME;
	strTempText += ">\r\n";
	if (Info.dwChildType < XmlFieldTypeStruct)
	{
		ParseBaseValue(GlobalSeri, Info.dwChildType, CHILD_KEY_NAME);
		strTempText += m_strXmlDepthText[m_dwDepth + 1];
	}
	else if (XmlFieldTypeStruct == Info.dwChildType)
	{
		ParseStructValue(GlobalSeri, CHILD_KEY_NAME);
		strTempText += m_strXmlDepthText[m_dwDepth + 1];
	}
	else
	{
		assert(false);
	}
	if (Info.dwChildType2 < XmlFieldTypeStruct)
	{
		ParseBaseValue(GlobalSeri, Info.dwChildType2, CHILD_VALUE_NAME);
		strTempText += m_strXmlDepthText[m_dwDepth + 1];
	}
	else if (XmlFieldTypeStruct == Info.dwChildType2)
	{
		ParseStructValue(GlobalSeri, CHILD_VALUE_NAME);
		strTempText += m_strXmlDepthText[m_dwDepth + 1];
	}
	else
	{
		assert(false);
	}
	AppendTabString(strTempText);
	strTempText += "<";
	strTempText += "</";
	strTempText += CHILD_NAME;
	strTempText += ">\r\n";

	strCurDepthText = strTempText;
	m_dwDepth--;
	return TRUE;
}

BOOL	CXmlTranslate::ParseFieldInfo(char *pBuffer, DWORD dwLen, XmlSerializationInfoArray &InfoArray)
{
	CSerialization tempSeri(pBuffer, dwLen);
	tempSeri.SetSerializationType(enum_Serialization_Type_Read);
	DWORD dwType = XmlFieldTypeNone, dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;;
	XmlInnerSerializationVecotr(InfoArray, tempSeri, dwType, dwChildType, dwChildType2);
	return TRUE;
}

BOOL	CXmlTranslate::ParseBaseValue(CSerialization &TempSeri, DWORD dwChildType, const char *pstrChildName)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth];
	strCurDepthText.clear();


	std::string strTempText, strFormatText = (boost::format("<%1%>%2%</%1%>\r\n") % pstrChildName % "%1%").str();
	AppendTabString(strTempText);
	switch (dwChildType)
	{
	case XmlFieldTypeBool:
		{
			bool bValue =false;
			TempSeri.Serialization(bValue);
			strTempText += (boost::format(strFormatText) % (bValue ? "1" : "0")).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeChar:
		{
			char cValue = 0;
			TempSeri.Serialization(cValue);
			strTempText += (boost::format(strFormatText) % static_cast<int>(cValue)).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeShort:
		{
			short sValue = 0;
			TempSeri.Serialization(sValue);
			strTempText += (boost::format(strFormatText) % sValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeInt:
		{
			int nValue = 0;
			TempSeri.Serialization(nValue);
			strTempText += (boost::format(strFormatText) % nValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeLong:
		{
			long lValue = 0;
			TempSeri.Serialization(lValue);
			strTempText += (boost::format(strFormatText) % lValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeFloat:
		{
			float fValue = 0.0;
			TempSeri.Serialization(fValue);
			strTempText += (boost::format(strFormatText) % fValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeDouble:
		{
			double dValue = 0.0;
			TempSeri.Serialization(dValue);
			strTempText += (boost::format(strFormatText) % dValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeString:
		{
			std::string str;
			TempSeri.Serialization(str);
			strTempText += (boost::format(strFormatText) % str.c_str()).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeUChar:
		{
			unsigned char ucValue = 0;
			TempSeri.Serialization(ucValue);
			strTempText += (boost::format(strFormatText) % static_cast<unsigned int>(ucValue)).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeUShort:
		{
			unsigned short usValue = 0;
			TempSeri.Serialization(usValue);
			strTempText += (boost::format(strFormatText) % usValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeUInt:
		{
			unsigned int uiValue = 0;
			TempSeri.Serialization(uiValue);
			strTempText += (boost::format(strFormatText) % uiValue).str();
			strCurDepthText += strTempText;
		}
		break;
	case XmlFieldTypeULong:
		{
			ULONG ulValue = 0;
			TempSeri.Serialization(ulValue);
			strTempText += (boost::format(strFormatText) % ulValue).str();
			strCurDepthText += strTempText;
		}
		break;
	default:
		{
			assert(false);
		}
		break;
	}
	
	m_dwDepth--;
	return TRUE;
}

BOOL	CXmlTranslate::ParseStructValue(CSerialization &TempSeri, const char *pstrChildName)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth];
	strCurDepthText.clear();

	std::string strTempText;
	AppendTabString(strTempText);
	strTempText += (boost::format("<%||>\r\n") % pstrChildName).str();
	ParseOneField(TempSeri);
	strTempText += m_strXmlDepthText[m_dwDepth + 1];
	AppendTabString(strTempText);
	strTempText += (boost::format("</%||>\r\n") % pstrChildName).str();
	strCurDepthText += strTempText;

	m_dwDepth--;
	return TRUE;
}

BOOL	CXmlTranslate::AppendTabString(std::string &strText)
{
	for (DWORD dwIndex = 0; dwIndex < m_dwDepth; dwIndex++)
	{
		strText += TAB_STRING;
	}
	return TRUE;
}

BOOL	CXmlTranslate::FromXml(char *pBuffer, DWORD dwLen, std::string &strData)
{
	CMarkup xml;
	xml.Load("c:\\1.xml");
	
	if (!xml.FindElem(_T("root")))
	{
		return FALSE;
	}
	memset(g_p->buf, 0xcd, _countof(g_p->buf));
	CSerialization GlobalSeri(g_p->buf, _countof(g_p->buf));
	GlobalSeri.SetSerializationType(enum_Serialization_Type_Write);
	ParseXmlStructValue(xml, GlobalSeri);

	strData.append(GlobalSeri.GetData(), GlobalSeri.GetDataLen());
	return  TRUE;
}

BOOL	CXmlTranslate::ParseXmlStructValue(CMarkup &xml, CSerialization &GlobalSeri)
{
	char *pCurOffsetBegin = GlobalSeri.GetData() + GlobalSeri.GetDataLen();
	DWORD dwCurOffset = GlobalSeri.GetDataLen();

	XmlSerializationHead Head;
	Head.Serialization(GlobalSeri);

	XmlSerializationInfoArray XmlInfoArray;
	xml.IntoElem();
	while (xml.FindElem())
	{
		std::string strTagName = xml.GetTagName();
		std::string strType = xml.GetAttrib(ATTRIBUTE_TYPE);
		std::string strChildType, strChildType2, strValue;
		DWORD dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;

		if (strTagName.empty() || strType.empty())
		{
			return FALSE;
		}
		DWORD dwType = atoi(strType.c_str());
		if (0 == dwType || dwType >= XmlFieldTypeMax)
		{
			return FALSE;
		}

		if (dwType >= XmlFieldTypeBool && dwType < XmlFiendTypeBaseMax)
		{
			strValue = xml.GetData();
			XmlSerializationInfo Info;
			Info.strName = strTagName;
			Info.dwType = dwType;
			Info.dwOffset = GlobalSeri.GetDataLen() - dwCurOffset;
			ParseXmlBaseValue(GlobalSeri, dwType, strValue);
			Info.dwLen = GlobalSeri.GetDataLen() - Info.dwOffset;
			XmlInfoArray.push_back(Info);
		}
		else if (XmlFieldTypeStruct == dwType)
		{
			XmlSerializationInfo Info;
			Info.strName = strTagName;
			Info.dwType = dwType;
			Info.dwOffset = GlobalSeri.GetDataLen() - dwCurOffset;
			ParseXmlStructValue(xml, GlobalSeri);
			Info.dwLen = GlobalSeri.GetDataLen() - Info.dwOffset;
			XmlInfoArray.push_back(Info);
		}
		else if (XmlFieldTypeVector == dwType)
		{
			XmlSerializationInfo Info;
			Info.strName = strTagName;
			Info.dwType = dwType;
			Info.dwOffset = GlobalSeri.GetDataLen() - dwCurOffset;

			DWORD dwVectorSize = 0;
			DWORD dwVectorSizeOffset = GlobalSeri.GetDataLen();
			GlobalSeri.Serialization(dwVectorSize);
			strChildType = xml.GetAttrib(CHILD_TYPE);
			dwChildType = atoi(strChildType.c_str());
			if (dwChildType >= XmlFieldTypeBool && dwChildType < XmlFiendTypeBaseMax)
			{
				xml.IntoElem();
				while (xml.FindElem())
				{
					dwVectorSize++;
					strValue = xml.GetData();
					ParseXmlBaseValue(GlobalSeri, dwChildType, strValue);
				}
				xml.OutOfElem();
			}
			else if (XmlFieldTypeStruct == dwChildType)
			{
				xml.IntoElem();
				while (xml.FindElem())
				{
					dwVectorSize++;
					ParseXmlStructValue(xml, GlobalSeri);
				}
				xml.OutOfElem();
			}
			memcpy(GlobalSeri.GetData() + dwVectorSizeOffset, &dwVectorSize, sizeof(DWORD));
			Info.dwLen = GlobalSeri.GetDataLen() - Info.dwOffset;
			XmlInfoArray.push_back(Info);
		}
		else if (XmlFieldTypeMap == dwType)
		{
			XmlSerializationInfo Info;
			Info.strName = strTagName;
			Info.dwType = dwType;
			Info.dwOffset = GlobalSeri.GetDataLen() - dwCurOffset;

			DWORD dwVectorSize = 0;
			DWORD dwVectorSizeOffset = GlobalSeri.GetDataLen();
			GlobalSeri.Serialization(dwVectorSize);
			strChildType = xml.GetAttrib(CHILD_TYPE);
			dwChildType = atoi(strChildType.c_str());
			strChildType2 = xml.GetAttrib(CHILD_TYPE2);
			dwChildType2 = atoi(strChildType2.c_str());

			xml.IntoElem();
			while (xml.FindElem())
			{
				if (!xml.FindElem(CHILD_KEY_NAME))
				{
					assert(false);
					continue;
				}
				if (dwChildType >= XmlFieldTypeBool && dwChildType < XmlFiendTypeBaseMax)
				{
					strValue = xml.GetData();
					ParseXmlBaseValue(GlobalSeri, dwChildType, strValue);
				}
				else if (XmlFieldTypeStruct == dwChildType)
				{
					ParseXmlStructValue(xml, GlobalSeri);
				}
				

				if (!xml.FindElem(CHILD_VALUE_NAME))
				{
					assert(false);
					continue;
				}
				if (dwChildType2 >= XmlFieldTypeBool && dwChildType2 < XmlFiendTypeBaseMax)
				{
					strValue = xml.GetData();
					ParseXmlBaseValue(GlobalSeri, dwChildType2, strValue);
				}
				else if (XmlFieldTypeStruct == dwChildType2)
				{
					ParseXmlStructValue(xml, GlobalSeri);
				}

				dwVectorSize++;
			}
			xml.OutOfElem();

			memcpy(GlobalSeri.GetData() + dwVectorSizeOffset, &dwVectorSize, sizeof(DWORD));
			Info.dwLen = GlobalSeri.GetDataLen() - Info.dwOffset;
			XmlInfoArray.push_back(Info);
		}
		else
		{
			assert(false);
		}
	}
	DWORD dwDataLen = GlobalSeri.GetDataLen() - dwCurOffset - sizeof(Head);
	DWORD dwType = XmlFieldTypeNone, dwChildType = XmlFieldTypeNone, dwChildType2 = XmlFieldTypeNone;;
	XmlInnerSerializationVecotr(XmlInfoArray, GlobalSeri, dwType, dwChildType, dwChildType2);

	Head.dwSectionLen = GlobalSeri.GetDataLen() - dwCurOffset;
	Head.dwDataLen = dwDataLen;
	memcpy(GlobalSeri.GetData() + dwCurOffset, &Head, sizeof(Head));

	xml.OutOfElem();
	return TRUE;
}

BOOL	CXmlTranslate::ParseXmlBaseValue(CSerialization &GlobalSeri, DWORD dwType, const std::string &strValue)
{
	switch (dwType)
	{
	case XmlFieldTypeBool:
		{
			bool bValue = false;
			if (0 == atoi(strValue.c_str()))
			{
				bValue = false;
			}
			else
			{
				bValue = true;
			}
			GlobalSeri.Serialization(bValue);
		}
		break;
	case XmlFieldTypeChar:
		{
			char cValue = static_cast<char>(atoi(strValue.c_str()));
			GlobalSeri.Serialization(cValue);
		}
		break;
	case XmlFieldTypeShort:
		{
			short sValue = static_cast<short>(atoi(strValue.c_str()));
			GlobalSeri.Serialization(sValue);
		}
		break;
	case XmlFieldTypeInt:
		{
			int nValue = atoi(strValue.c_str());
			GlobalSeri.Serialization(nValue);
		}
		break;
	case XmlFieldTypeLong:
		{
			long lValue = atol(strValue.c_str());
			GlobalSeri.Serialization(lValue);
		}
		break;
	case XmlFieldTypeFloat:
		{
			float fValue = static_cast<float>(atof(strValue.c_str()));
			GlobalSeri.Serialization(fValue);
		}
		break;
	case XmlFieldTypeDouble:
		{
			double dValue = atof(strValue.c_str());
			GlobalSeri.Serialization(dValue);
		}
		break;
	case XmlFieldTypeString:
		{
			GlobalSeri.Serialization(const_cast<std::string&>(strValue));
		}
		break;
	case XmlFieldTypeUChar:
		{
			unsigned char ucValue = 0;
			char *pStop = NULL;
			ucValue = static_cast<unsigned char>(strtoul(strValue.c_str(), &pStop, 10));
			GlobalSeri.Serialization(ucValue);
		}
		break;
	case XmlFieldTypeUShort:
		{
			unsigned short usValue = 0;
			char *pStop = NULL;
			usValue = static_cast<unsigned short>(strtoul(strValue.c_str(), &pStop, 10));
			GlobalSeri.Serialization(usValue);
		}
		break;
	case XmlFieldTypeUInt:
		{
			unsigned int uiValue = 0;
			char *pStop = NULL;
			uiValue = static_cast<unsigned int>(strtoul(strValue.c_str(), &pStop, 10));
			GlobalSeri.Serialization(uiValue);
		}
		break;
	case XmlFieldTypeULong:
		{
			unsigned long ulValue = 0;
			char *pStop = NULL;
			ulValue = strtoul(strValue.c_str(), &pStop, 10);
			GlobalSeri.Serialization(ulValue);
		}
		break;
	default:
		{
			assert(false);
			return FALSE;
		}
		break;
	}
	return TRUE;
}

BOOL	CXmlTranslate::NodeToXml(ConfigStructNode *pNodeStruct, std::string &strXml)
{
	m_dwDepth = 0;
	m_strXmlDepthText[m_dwDepth] = "<?xml version=\"1.0\" encoding=\"gb2312\" standalone=\"yes\" ?>\r\n";
	m_strXmlDepthText[m_dwDepth] += "<root>\r\n";

	ParseStructNode(pNodeStruct);

	m_strXmlDepthText[m_dwDepth] += m_strXmlDepthText[m_dwDepth + 1];
	m_strXmlDepthText[m_dwDepth] += "</root>";

	strXml = m_strXmlDepthText[0];

	return TRUE;
}

BOOL	CXmlTranslate::ParseStructNode(ConfigStructNode *pNodeStruct)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth], strTempText;
	strCurDepthText.clear();

	for (ConfigNameNodeArray::iterator itor = pNodeStruct->m_ConfigNameNodeArray.begin(); itor != pNodeStruct->m_ConfigNameNodeArray.end();++itor)
	{
		const DWORD &dwType = itor->second->m_dwType;
		const std::string &strName = itor->first;

		strTempText.clear();
		if (IsNormalFileType(dwType))
		{
			ConfigNormalNode *pNodeBaseValue = (ConfigNormalNode*)(itor->second.get());
			CSerialization TempSeri((char*)pNodeBaseValue->m_strValue.data(), pNodeBaseValue->m_strValue.size());
			ParseBaseValue(TempSeri, dwType, strName.c_str());
			strCurDepthText += m_strXmlDepthText[m_dwDepth + 1];
		}
		else if (XmlFieldTypeStruct == dwType)
		{
			ConfigStructNode *pChildStructNode = (ConfigStructNode*)(itor->second.get());
			AppendTabString(strTempText);
			strTempText += (boost::format("<%1% type=\"%2%\">\r\n") % strName % dwType).str();
			ParseStructNode(pChildStructNode);
			strTempText += m_strXmlDepthText[m_dwDepth + 1];
			AppendTabString(strTempText);
			strTempText += (boost::format("</%1%>\r\n") % strName).str();
		}
		else if (XmlFieldTypeVector == dwType)
		{

		}
	}

	m_dwDepth--;
	return TRUE;
}

BOOL	CXmlTranslate::NodeToStream(ConfigNodeBase *pNodeBase, std::string &strData)
{
	m_dwDepth = 0;

	DWORD dwType = pNodeBase->m_dwType;
	if (IsNormalFileType(dwType))
	{
		
	}
	else
	{

	}
	strData = m_strXmlDepthText[m_dwDepth + 1];
	return TRUE;
}

BOOL	CXmlTranslate::NormalNodeToStream(ConfigNormalNode *pNodeNormal)
{
	m_dwDepth++;
	std::string &strCurDepthText = m_strXmlDepthText[m_dwDepth], strTempText;
	strCurDepthText.clear();



	m_dwDepth--;
	return TRUE;
}