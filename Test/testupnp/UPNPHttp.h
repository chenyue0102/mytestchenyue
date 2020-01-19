/*
����http���󣬶�����
*/
#pragma once
#include <string>

class UPNPHttp
{
public:
	UPNPHttp();
	~UPNPHttp();
public:
	//���������URL host �� port
	void setHttpInfo(const std::string &host, unsigned short port, unsigned int scope_id);
	//���ÿ���url path
	void setControlURLPath(const std::string &path);
	//����soap����
	int soapPostSubmit(const std::string &action, const std::string &body, const std::string &httpVersion, std::string &result);
private:
	//������ip
	std::string mHost;
	//�������˿�
	unsigned short mPort;
	unsigned int mScopeId;
	//����action��url
	std::string mControlURL;
};

