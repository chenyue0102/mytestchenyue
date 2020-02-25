#pragma once
#include "UPNPServiceBase.h"
class UPNPServiceKaiShu : public UPNPServiceBase
{
public:
	UPNPServiceKaiShu();
	~UPNPServiceKaiShu();
public:
	bool X_kaishustory_Login(const std::string& userid, const std::string& token);
};

