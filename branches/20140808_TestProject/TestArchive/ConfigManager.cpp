#include "StdAfx.h"
#include "ConfigManager.h"


CConfigManager::CConfigManager(void)
	: m_pBuffer(NULL)
	, m_dwDataLen(0)
	, m_dwBufLen(CONFIG_BUFFER_LEN)
{
}


CConfigManager::~CConfigManager(void)
{
}

BOOL	CConfigManager::GetItem(const char *pstrToken, DWORD &dwOffset, DWORD &dwLen)
{
	typedef boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string > atokenizer;
	boost::char_separator<char> sep(pstrToken, "", boost::keep_empty_tokens);
	atokenizer tok(strText, ".");
	std::list<std::string> ItemNameArray;
	ItemNameArray ItemNames;
	for (atokenizer::iterator itor = tok.begin(); itor != tok.end(); ++itor)
	{
		ItemNames.push_back(*itor);
	}

	XmlSerializationHead Head;
	CSerialization TempSeri(m_pBuffer, m_dwDataLen);

	DWORD dwHeadOffset = TempSeri.GetDataLen();
	Head.Serialization(TempSeri);
	DWORD dwInfoOffset = dwHeadOffset + Head.dwDataLen + sizeof(Head);

	XmlSerializationInfoArray Xml
	XmlInnerSerializationVecotr(m_SerializationInfoArray, m_Serialization, dwType, dwChildType, dwChildType2);
	
	return TRUE;
}