#pragma once
#include <string>
#include "UPNPProtocol.h"
#include "UPNPDefine.h"

class UPNPDevInfo
{
public:
	UPNPDevInfo();
	~UPNPDevInfo();
public:
	void setDevInfo(const char *descURL, const char *st, const char *usn, unsigned int scope_id);
	void sendGetDeviceDescriptionDocument(const std::string url);
private:
	void parseST(const std::string &st);
	std::string getUUIDFromUSN(const std::string &usn);
	EType getType(const std::string &type);
private:
	std::string mDescURL;
	std::string mST;
	std::string mUSN;
	std::string mUUID;
	ETarget mETarget;		//Ŀ������
	EType mEType;			//����
	int mVersion;			//�汾��
	UPNPDDDRoot mUPNPDDDRoot;
};

