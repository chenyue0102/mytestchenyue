#pragma once
#include <string>
#include <vector>

namespace WMIHelper
{
enum class WmiQueryError 
{
	None,
	BadQueryFailure,
	PropertyExtractionFailure,
	ComInitializationFailure,
	SecurityInitializationFailure,
	IWbemLocatorFailure,
	IWbemServiceConnectionFailure,
	BlanketProxySetFailure,
};

struct WmiQueryResult
{
	std::vector<std::wstring> ResultList;
	WmiQueryError Error = WmiQueryError::None;
	std::wstring ErrorDescription;
};
WmiQueryResult getWmiQueryResult(std::wstring wmiQuery, std::wstring propNameOfResultObject, bool allowEmptyItems = false);
};