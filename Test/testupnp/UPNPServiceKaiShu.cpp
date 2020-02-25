#include "UPNPServiceKaiShu.h"

UPNPServiceKaiShu::UPNPServiceKaiShu()
	: UPNPServiceBase(ETypeKaiShu)
{
}

UPNPServiceKaiShu::~UPNPServiceKaiShu()
{
}

bool UPNPServiceKaiShu::X_kaishustory_Login(const std::string& userid, const std::string& token)
{
	std::vector<SoapArgument> arguments =
	{
		{ "userid", userid },
		{ "token", token },
	};
	std::string result;
	int stateCode = soapPostSubmit("X_kaishustory_Login", arguments, result);

	return 200 == stateCode;
}
