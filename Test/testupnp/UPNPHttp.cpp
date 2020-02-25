#include "UPNPHttp.h"
#include <assert.h>
#include <memory>
#include <sstream>
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
	/*mControlURL = "http://" + mHost;
	if (80 != mPort)
	{
		mControlURL += ":" + std::to_string(mPort);
	}
	mControlURL += '/' + path;*/
	mControlURL = path;
}

void UPNPHttp::setRegURLPath(const std::string & path)
{
	/*mRegURL = "http://" + mHost;
	if (80 != mPort)
	{
		mRegURL += ":" + std::to_string(mPort);
	}
	mRegURL += '/' + path;*/
	mRegURL = path;
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
			//assert(false);
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

int UPNPHttp::sendAndReceive(const std::string & data, std::string & result)
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
		int curOffset = 0;
		int sendLen = 0;
		while (curOffset < data.size() && (sendLen = send(socket, data.data() + curOffset, data.size() - curOffset, 0)) > 0)
		{
			curOffset += sendLen;
		}
		if (sendLen <= 0)
		{
			assert(false);
			break;
		}
				
		/*int size = 0;
		std::shared_ptr<void> pResult(getHTTPResponse(socket, &size, &stateCode), &free);
		if (!pResult)
		{
			assert(false);
			break;
		}
		const char *p = reinterpret_cast<const char*>(pResult.get());
		result.append(p, size);*/
	} while (false);
	if (!ISINVALID(socket))
	{
		closesocket(socket);
		socket = INVALID_SOCKET;
	}
	return stateCode;
}

int UPNPHttp::regCallback(const std::string &event,  const std::string & callbackURL, int timeout)
{
	std::stringstream ss;
	ss << "SUBSCRIBE /" << mRegURL << " HTTP/1.1\r\n"
		<< "HOST:" << mHost << ":" << mPort << "\r\n"
		<< "User-Agent: MSWindows/10.0.18363, UPnP/1.1, MiniUPnPc/2.1\r\n"
		<< "CALLBACK:<" << callbackURL << ">\r\n"
		<< "NT:upnp:event" /*<< event*/ << "\r\n"
		<< "TIMEOUT:Second-3600" /*<< timeout */ << "\r\n"
		<< "\r\n";
	std::string data = ss.str();
	std::string result;
	int stateCode = sendAndReceive(data, result);
	return 0;
}
