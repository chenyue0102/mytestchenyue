// TestVIP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

typedef unsigned long DWORD;
void GetNodeInfo(TiXmlElement* pAttribute, DWORD &dwID, DWORD &dwStaffID,
	std::string &strNickName, DWORD &dwLevel, std::string &strActionName, 
	DWORD &dwDataTime, std::string &strData)
{
	const char *pstrContentType = pAttribute->Attribute("id");
	dwID = atoi(pstrContentType);
	
	pstrContentType = pAttribute->Attribute("staff_id");
	dwStaffID = atoi(pstrContentType);
	
	pstrContentType = pAttribute->Attribute("nickname");
	strNickName = pstrContentType;
	
	pstrContentType = pAttribute->Attribute("level");
	dwLevel = atoi(pstrContentType);
	
	pstrContentType = pAttribute->Attribute("actionname");
	strActionName = pstrContentType;
	
	pstrContentType = pAttribute->Attribute("data_time");
	dwDataTime = atoi(pstrContentType);

	pstrContentType = pAttribute->Attribute("date");
	strData = pstrContentType;
}

void OutputNodeInfo(TiXmlElement* pAttribute)
{
	if (NULL == pAttribute)
	{
		return;
	}
	DWORD dwID = 0, dwStaffID = 0, dwLevel = 0, dwDataTime = 0;
	std::string strNickName, strActionName, strData;
	GetNodeInfo(pAttribute, dwID, dwStaffID, strNickName, dwLevel, strActionName, dwDataTime, strData);
	printf("ID=%u StaffID=%u NickName=%s Level=%u ActionName=%s DataTime=%u Data=%s\n", dwID, dwStaffID, strNickName.c_str(),
		dwLevel, strActionName.c_str(), dwDataTime, strData.c_str());
}

void OutputEnter(TiXmlNode *pNode)
{
	DWORD dwLastID = 0;
	TiXmlNode *pNodeLast = NULL;
	while (NULL != pNode)
	{
		DWORD dwID = 0, dwStaffID = 0, dwLevel = 0, dwDataTime = 0;
		std::string strNickName, strActionName, strData;
		TiXmlElement* pAttribute = pNode->ToElement();
		GetNodeInfo(pAttribute, dwID, dwStaffID, strNickName, dwLevel, strActionName, dwDataTime, strData);
		TiXmlElement *pLastAttribute = NULL;
		if (NULL != pNodeLast)
		{
			pLastAttribute = pNodeLast->ToElement();
		}
		if (0 == dwLastID)
		{
			if (strActionName == "登陆")
			{
				dwLastID = dwStaffID;
			}
			else
			{
				OutputNodeInfo(pAttribute);
			}
		}
		else
		{
			if (dwStaffID == dwLastID)
			{
				if (strActionName == "退出")
				{
					dwLastID = 0;
				}
				else
				{
					OutputNodeInfo(pAttribute);
					dwLastID = 0;
				}
			}
			else
			{
				OutputNodeInfo(pAttribute);
				dwLastID = 0;
				if (strActionName == "登陆")
				{
					dwLastID = dwStaffID;
				}
				else
				{
					OutputNodeInfo(pAttribute);
				}
			}
		}
		pNodeLast = pNode;
		pNode = pNode->NextSibling();
	}
}

void OutputRest(TiXmlNode *pNode)
{
	const char *pstrBegin = "进入休息";
	const char *pstrEnd = "进入工作";
	DWORD dwLastStaffID = 0;
	std::string strLastActionName;
	while (NULL != pNode)
	{
		DWORD dwID = 0, dwStaffID = 0, dwLevel = 0, dwDataTime = 0;
		std::string strNickName, strActionName, strData;
		TiXmlElement* pAttribute = pNode->ToElement();
		GetNodeInfo(pAttribute, dwID, dwStaffID, strNickName, dwLevel, strActionName, dwDataTime, strData);
		pNode = pNode->NextSibling();
		if (dwLastStaffID != dwStaffID)
		{
			if (strActionName == pstrBegin)
			{
				dwLastStaffID = dwStaffID;
				strLastActionName = strActionName;
			}
			else
			{
				dwLastStaffID = 0;
				strLastActionName.clear();
			}
		}
		else
		{
			if (strActionName == pstrEnd)
			{
				if (strLastActionName != pstrBegin)
				{
					OutputNodeInfo(pAttribute);
				}
				strLastActionName.clear();
			}
			else if (strActionName == "退出")
			{
				strLastActionName.clear();
			}
			else if (strActionName == "登陆")
			{
				assert(strLastActionName.empty());
			}
			else
			{
				if (!strLastActionName.empty())
				{
					OutputNodeInfo(pAttribute);
				}
				strLastActionName = strActionName;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char szBuffer[512] = { 0 };
	char szUrl[512] = "http://jj.cn.%7a%68";
	DWORD dwSize = _countof(szBuffer);
	UrlUnescapeA(szUrl, szBuffer, &dwSize, URL_DONT_UNESCAPE_EXTRA_INFO);
	TiXmlDocument doc;
	doc.LoadFile("C:\\Users\\chenyue\\Desktop\\进入休息进入工作.xml");
	TiXmlNode* pNode = NULL;
	
	do 
	{
		pNode = doc.FirstChild("DATAPACKET");
		if (NULL == pNode)
		{
			assert(false);
			break;
		}
		pNode = pNode->FirstChild("DATA");
		pNode = pNode->FirstChild("pk");
		pNode = pNode->FirstChild("R");
	} while (false);
	
	//OutputEnter(pNode);
	OutputRest(pNode);
	return 0;
}

