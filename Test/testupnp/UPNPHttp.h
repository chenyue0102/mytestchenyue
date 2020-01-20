/*
发送http请求，短链接
*/
#pragma once
#include <string>

class UPNPHttp
{
public:
	UPNPHttp();
	~UPNPHttp();
public:
	//设置请求的URL host 与 port
	void setHttpInfo(const std::string &host, unsigned short port, unsigned int scope_id);
	//设置控制url path
	void setControlURLPath(const std::string &path);
	void setRegURLPath(const std::string &path);
	//发送soap请求
	int soapPostSubmit(const std::string &action, const std::string &body, const std::string &httpVersion, std::string &result);
	int sendAndReceive(const std::string &data, std::string &result);
	int regCallback(const std::string &event, const std::string & callbackURL, int timeout);
private:
	//服务器ip
	std::string mHost;
	//服务器端口
	unsigned short mPort;
	unsigned int mScopeId;
	//发送action的url
	std::string mControlURL;
	std::string mRegURL;
};

