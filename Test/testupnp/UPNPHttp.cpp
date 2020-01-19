#include "UPNPHttp.h"
#include <assert.h>
#include <memory>
#ifdef _WIN32
#include <winsock2.h>
#else
#error include socket header
#endif
extern "C"
{
#include "connecthostport.h"
#include "minisoap.h"
extern void * getHTTPResponse(SOCKET s, int * size, int * status_code);
}
#include "connecthostport.h"
#include "UPNPDefine.h"


UPNPHttp::UPNPHttp()
	: mPort(0)
	, mScopeId(0)
{
}


UPNPHttp::~UPNPHttp()
{
}

void UPNPHttp::setHttpInfo(const std::string & host, unsigned short port, unsigned int scope_id)
{
	mHost = host;
	mPort = port;
	mScopeId = scope_id;
}

void UPNPHttp::setControlURLPath(const std::string &path)
{
	mControlURL = "http://" + mHost;
	if (80 != mPort)
	{
		mControlURL += ":" + std::to_string(mPort);
	}
	mControlURL += '/' + path;
}

int UPNPHttp::soapPostSubmit(const std::string & action, const std::string & body, const std::string & httpVersion, std::string &result)
{
	int stateCode = 0;
	SOCKET socket = INVALID_SOCKET;


	do
	{
		socket = connecthostport(mHost.c_str(), mPort, mScopeId);
		if (ISINVALID(socket))
		{
			assert(false);
			break;
		}
		if (::soapPostSubmit(socket, mControlURL.c_str(), mHost.c_str(), mPort, action.c_str(), body.c_str(), httpVersion.c_str()) <= 0)
		{
			assert(false);
			break;
		}
		int size = 0;
		std::shared_ptr<void> pResult(getHTTPResponse(socket, &size, &stateCode), &free);
		if (!pResult)
		{
			assert(false);
			break;
		}
		const char *p = reinterpret_cast<const char*>(pResult.get());
		result.append(p, size);
	} while (false);
	if (!ISINVALID(socket))
	{
		closesocket(socket);
		socket = INVALID_SOCKET;
	}
	return stateCode;
}
