// TestArchive.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "Serialization.h"
#include "SafeSerialization.h"
#include <boost/format.hpp>
#include <list>
#include "XmlSerialization.h"
#include "XmlTranslate.h"




struct TKSnsClientHeader
{
	// 消息ID,见TK_SNS_MESSAGE_ID
	DWORD	dwMessageID;

	// 消息的类型,见TK_SNS_MESSAGE_TYPE
	DWORD	dwMessageType;

	// 客户端协议版本号,见"客户端协议版本号定义"部分
	DWORD	dwProtocolVersion;

	// 成功或失败
	BOOL	bSuccess;

	// 错误码(根据具体协议的不同,对错误码的解释不同,不是所有失败都有错误码,dwErrorCode默认值为0)
	DWORD	dwErrorCode;

	TKSnsClientHeader()
	{
		dwMessageID = 0;
		dwMessageType = 0;
		dwProtocolVersion = 0;
		bSuccess = FALSE;
		dwErrorCode = 0;
	}
	BOOL Serialization(CSerialization& aSerialization)
	{
		try
		{
			// 消息ID
			aSerialization.Serialization(dwMessageID);
			// 消息的类型
			aSerialization.Serialization(dwMessageType);
			// 客户端协议版本号
			aSerialization.Serialization(dwProtocolVersion);
			// 成功或失败
			aSerialization.Serialization(bSuccess);
			// 错误码
			aSerialization.Serialization(dwErrorCode);
		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}
};

struct TKSnsClientTLV
{
	static	BOOL bUserSafe;
	DWORD	dwID;			// 属性ID
	string	strKey;
	string	strValue;		// 属性值

	TKSnsClientTLV()
	{
		dwID = 0;
		strValue = "";
		strKey="";
	}
	
	BOOL Serialization(CSerialization& aSerialization)
	{
		try
		{
			if (bUserSafe)
			{
				DEF_SS_VALUE(aSerialization);
				SS_VALUE(dwID);
				SS_VALUE(strKey);
				SS_VALUE(strValue);
			}
			else
			{
				// 属性ID
				aSerialization.Serialization(dwID);
				aSerialization.Serialization(strKey);
				// 属性值
				aSerialization.Serialization(strValue);
			}
			
		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}
};

struct TKSnsClientTLV2
{
	static	BOOL bUserSafe;
	DWORD	dwID;			// 属性ID
	BOOL	bEnable;
	string	strValue;		// 属性值

	TKSnsClientTLV2()
	{
		dwID = 0;
		strValue = "";
		bEnable = FALSE;
	}

	BOOL Serialization(CSerialization& aSerialization)
	{
		try
		{
			if (bUserSafe)
			{
				DEF_SS_VALUE(aSerialization);
				SS_VALUE(dwID);
				SS_VALUE(bEnable);
				SS_VALUE(strValue);
			}
			else
			{
				// 属性ID
				aSerialization.Serialization(dwID);
				// 属性值
				aSerialization.Serialization(strValue);
			}

		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}
};
BOOL TKSnsClientTLV2::bUserSafe = FALSE;
BOOL TKSnsClientTLV::bUserSafe = FALSE;
struct TKSnsClientPropertySet2
{
	static BOOL bUserSafe;
	DWORD dwTempValue;
	vector<TKSnsClientTLV2>	SnsClientTLVArray;	// 属性数组
	DWORD		dwKey;
	TKSnsClientTLV			OneTlv;
	DWORD		dwEnable;
	std::map<DWORD,std::string> UserIDName;
	list<TKSnsClientTLV>	List;
	BOOL Serialization(CSerialization& aSerialization)
	{
		try
		{
			if (bUserSafe)
			{
				DEF_SS_VALUE(aSerialization);
				SS_VALUE(dwTempValue);
				SS_VECTOR_VALUE(SnsClientTLVArray);
				SS_VALUE(dwKey);
				SS_VALUE(OneTlv);
				SS_VALUE(dwEnable);
				SS_VECTOR_VALUE(UserIDName);
				SS_VECTOR_VALUE(List);
			}
			else
			{
				DWORD dwPropertyCount = SnsClientTLVArray.size();
				// 属性个数
				aSerialization.Serialization(dwPropertyCount);
				// 属性数组
				for (DWORD dwIndex = 0; dwIndex < dwPropertyCount; ++dwIndex)
				{
					if (aSerialization.GetSerializationType() == enum_Serialization_Type_Read)	// 读
					{
						TKSnsClientTLV2 stSnsClientTLV;
						if (!stSnsClientTLV.Serialization(aSerialization))
							return FALSE;

						SnsClientTLVArray.push_back(stSnsClientTLV);
					}
					else if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
					{
						if (!SnsClientTLVArray[dwIndex].Serialization(aSerialization))
							return FALSE;
					}
				}
				OneTlv.Serialization(aSerialization);
			}
		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}
};
BOOL TKSnsClientPropertySet2::bUserSafe = FALSE;
struct TKSnsClientPropertySet
{
	static BOOL bUserSafe;
	TKSnsClientHeader		Header;
	vector<TKSnsClientTLV>	SnsClientTLVArray;	// 属性数组
	TKSnsClientTLV			OneTlv;
	DWORD		dwEnable;
	std::map<DWORD,std::string> UserIDName;
	std::set<DWORD> aaaa;
	BOOL Serialization(CSerialization& aSerialization)
	{
		try
		{
			if (bUserSafe)
			{
				DEF_SS_VALUE(aSerialization);
				SS_VALUE(Header);
				SS_VECTOR_VALUE(SnsClientTLVArray);
				SS_VALUE(OneTlv);
				SS_VALUE(dwEnable);
				SS_VECTOR_VALUE(UserIDName);
				SS_VECTOR_VALUE(aaaa);
			}
			else
			{
				Header.Serialization(aSerialization);
				DWORD dwPropertyCount = SnsClientTLVArray.size();
				// 属性个数
				aSerialization.Serialization(dwPropertyCount);
				// 属性数组
				for (DWORD dwIndex = 0; dwIndex < dwPropertyCount; ++dwIndex)
				{
					if (aSerialization.GetSerializationType() == enum_Serialization_Type_Read)	// 读
					{
						TKSnsClientTLV stSnsClientTLV;
						if (!stSnsClientTLV.Serialization(aSerialization))
							return FALSE;

						SnsClientTLVArray.push_back(stSnsClientTLV);
					}
					else if (aSerialization.GetSerializationType() == enum_Serialization_Type_Write)	// 写
					{
						if (!SnsClientTLVArray[dwIndex].Serialization(aSerialization))
							return FALSE;
					}
				}
				OneTlv.Serialization(aSerialization);
			}
		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}
};
BOOL TKSnsClientPropertySet::bUserSafe = FALSE;

void Test(BOOL bUserSafe, DWORD &dwLen, DWORD &dwTime)
{
	DWORD dwTickCount = GetTickCount();
	//for (int a = 0; a < 1000; a++)
	//{
		TKSnsClientPropertySet Head;
		TKSnsClientPropertySet::bUserSafe =  bUserSafe;
		Head.Header.dwMessageID = 123456;
		Head.Header.dwMessageType=  5678;
		Head.Header.dwProtocolVersion = 100;
		TKSnsClientTLV OneTlv;
		TKSnsClientTLV2::bUserSafe = bUserSafe;
		TKSnsClientTLV::bUserSafe = bUserSafe;
		for (int nIndex = 50; nIndex < 100; nIndex++)
		{
			OneTlv.dwID = 50;
			OneTlv.strValue = (boost::format("Name%||") % nIndex).str();
			OneTlv.strKey = (boost::format("Key%||") % nIndex).str();
			Head.SnsClientTLVArray.push_back(OneTlv);
		}
		Head.dwEnable = 5000;
		Head.OneTlv.dwID = 999999;
		Head.OneTlv.strValue = "我是神";
		Head.UserIDName[100] = "陈月";
		Head.UserIDName[200] = "老大";
		CSerialization s(g_p->buf, _countof(g_p->buf));
		s.SetSerializationType(enum_Serialization_Type_Write);
		Head.Serialization(s);
		std::string strTemp;
		strTemp.append(s.GetData(), s.GetDataLen());
		dwLen = s.GetDataLen();
		CSerialization sRead((char*)strTemp.data(), strTemp.size());
		sRead.SetSerializationType(enum_Serialization_Type_Read);
		TKSnsClientPropertySet2 Headread;
		TKSnsClientPropertySet2::bUserSafe = bUserSafe;
		Headread.Serialization(sRead);
	//}
	dwTime = GetTickCount() - dwTickCount;
}

int g_k = 0;
template <typename T>
void TestS(T &a)
{
	g_k += a;
}
void TestS(int a)
{
	g_k += a;
}

#define GETNAME(Type,TypeName) \
void GetName(Type &t, std::string &strName)\
{\
	strName=TypeName;\
}\

GETNAME(int,"int")

struct BookInfo
{
	DWORD	dwBookID;
	std::string	strBookName;
	BOOL Serialization(CSerialization& aSerialization)
	{
		DEF_XML_SS_VALUE(aSerialization,"BookInfo");
		XML_SS_VALUE(dwBookID);
		XML_SS_VALUE(strBookName);
		return TRUE;
	}
};

struct TestXml
{
	DWORD	dwUserID;
	std::string strName;
	BookInfo	Boook;
	vector<std::string> BookNames;
	vector<BookInfo>	BookInfos;
	BOOL Serialization(CSerialization& aSerialization)
	{
		DEF_XML_SS_VALUE(aSerialization,"TestXml");
		XML_SS_VALUE(dwUserID);
		XML_SS_VALUE(strName);
		XML_SS_VALUE(Boook);
		XML_SS_VECTOR_VALUE(BookNames);
		XML_SS_VECTOR_VALUE(BookInfos);
		return TRUE;
	}
};

struct InsideStruct
{
	std::string strInside;
	DWORD		dwInside;
	InsideStruct()
	{
		/*strInside = "inside text";
		dwInside = 2222222;*/
	}
	BOOL Serialization(CSerialization& aSerialization)
	{
		DEF_XML_SS_VALUE(aSerialization,"InsideStruct");
		XML_SS_VALUE(strInside);
		XML_SS_VALUE(dwInside);
		return TRUE;
	}
};
struct TestD
{
	bool bChange;
	char cChar;
	short sShort;
	int		nValue;
	long	lValue;
	float	fValue;
	double	dValue;
	std::string strText;
	unsigned char ucValue;
	unsigned short usValue;
	unsigned int uiValue;
	unsigned long ulValue;
	InsideStruct InsideValue;
	std::vector<std::string> StringArray;
	std::vector<InsideStruct> InsideArray;
	std::map<string, InsideStruct> InsideMapArray;
	TestD()
	{
		/*bChange = false;
		cChar=56;
		sShort = -1270;
		nValue = -1223456;
		lValue = -234567;
		fValue = 101.123;
		dValue = 200.456;
		strText="hello, world";
		ucValue=250;
		usValue = 20000;
		uiValue = 1223456;
		ulValue = 234567;
		StringArray.push_back("c++");
		StringArray.push_back("高等数学");
		InsideStruct is;
		is.dwInside = 3333;
		is.strInside = "inside3333";
		InsideArray.push_back(is);
		is.dwInside = 4444;
		is.strInside = "inside4444";
		InsideArray.push_back(is);

		InsideMapArray["mapinside5"].dwInside =5555;
		InsideMapArray["mapinside5"].strInside ="mapinside5555";
		InsideMapArray["mapinside6"].dwInside =6666;
		InsideMapArray["mapinside6"].strInside ="mapinside6666";*/
	}
	BOOL Serialization(CSerialization& aSerialization)
	{
		DEF_XML_SS_VALUE(aSerialization,"TestD");
		XML_SS_VALUE(bChange);
		XML_SS_VALUE(cChar);
		XML_SS_VALUE(sShort);
		XML_SS_VALUE(nValue);
		XML_SS_VALUE(lValue);
		XML_SS_VALUE(fValue);
		XML_SS_VALUE(dValue);
		XML_SS_VALUE(strText);
		XML_SS_VALUE(ucValue);
		XML_SS_VALUE(usValue);
		XML_SS_VALUE(uiValue);
		XML_SS_VALUE(ulValue);
		XML_SS_VALUE(InsideValue);
		XML_SS_VECTOR_VALUE(StringArray);
		XML_SS_VECTOR_VALUE(InsideArray);
		XML_SS_VECTOR_VALUE(InsideMapArray);
		return TRUE;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	/*TestXml txml;
	txml.dwUserID = 1234;
	txml.strName = "陈月";
	txml.Boook.dwBookID = 10086;
	txml.Boook.strBookName = "生命科学";
	txml.BookNames.push_back("c++");
	txml.BookNames.push_back("高等数学");
	BookInfo OneBookInfo;
	OneBookInfo.dwBookID = 1111;
	OneBookInfo.strBookName = "1111";
	txml.BookInfos.push_back(OneBookInfo);
	OneBookInfo.dwBookID = 2222;
	OneBookInfo.strBookName = "2222";
	txml.BookInfos.push_back(OneBookInfo);
	CSerialization s(g_p->buf, _countof(g_p->buf));
	s.SetSerializationType(enum_Serialization_Type_Write);
	txml.Serialization(s);

	
	std::string strfff;*/
	TestD testd;
	testd.bChange = true;
	CSerialization s(g_p->buf, _countof(g_p->buf));
	s.SetSerializationType(enum_Serialization_Type_Write);
	testd.Serialization(s);
	CXmlTranslate xmltrans;
	std::string strXmlString;
	//xmltrans.ToXml(s.GetData(), s.GetDataLen(), strXmlString);
	//HANDLE hFile = CreateFile("C:\\1.xml", GENERIC_WRITE,0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWriteBytes = 0;
	//WriteFile(hFile, strXmlString.data(), strXmlString.size(), &dwWriteBytes, NULL);
	//CloseHandle(hFile);
	
	std::string strData;
	xmltrans.FromXml(NULL, 0,strData);

	CSerialization xxser((char*)strData.data(), strData.size());
	TestD ReadSeri;
	xxser.SetSerializationType(enum_Serialization_Type_Read);
	ReadSeri.Serialization(xxser);
	return 0;
	int k = 0;
	std::string strName;
	GetName(k,strName);
	vector<int>::iterator ff;
	std::map<DWORD, DWORD>::value_type fer;
	TestS(k);
	//TestS(ff);
	DWORD dwLen = 0, dwTime = 0;
	Test(TRUE, dwLen, dwTime);
	printf("FALSE dwLen=%d dwTime=%d\n",dwLen, dwTime);

	DWORD dwLen2 = 0, dwTime2 = 0;
	Test(TRUE, dwLen2, dwTime2);
	printf("TRUE dwLen=%d dwTime=%d\n",dwLen2, dwTime2);

	float f = (float)dwLen2 / dwLen;
	float f2 = (float)dwTime2 /dwTime;
	printf("Len=%f Time=%f\n",f,f2);
	return 0;
}

