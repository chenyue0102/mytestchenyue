#pragma once

#define CONFIG_BUFFER_LEN		(1024 * 5)
class CConfigManager
{
public:
	CConfigManager(void);
	~CConfigManager(void);
public:
	BOOL	GetItem(const char *pstrToken, DWORD &dwOffset, DWORD &dwLen);
public:
	char		*m_pBuffer;
	DWORD		m_dwBufLen;
	DWORD		m_dwDataLen;
};

